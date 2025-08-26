#include <tree_sitter/parser.h>
#include <stdbool.h>
#include <stdint.h>

enum TokenType { LITERAL_TEXT };

static inline bool is_ident_start(int32_t c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}
static inline bool is_digit(int32_t c) { return c >= '0' && c <= '9'; }

typedef struct {
  bool started; // have we seen any non-newline character yet?
} Scanner;

void *tree_sitter_mtlog_external_scanner_create() {
  Scanner *s = (Scanner *)calloc(1, sizeof(Scanner));
  s->started = false;
  return s;
}

void tree_sitter_mtlog_external_scanner_destroy(void *payload) {
  if (payload) free(payload);
}

unsigned tree_sitter_mtlog_external_scanner_serialize(void *p, char *b) {
  Scanner *s = (Scanner *)p;
  if (!s || !b) return 0;
  b[0] = s->started ? 1 : 0;
  return 1;
}

void tree_sitter_mtlog_external_scanner_deserialize(void *p, const char *b, unsigned l) {
  Scanner *s = (Scanner *)p;
  if (!s) return;
  if (b && l >= 1) {
    s->started = b[0] != 0;
  } else {
    s->started = false;
  }
}

bool tree_sitter_mtlog_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
  Scanner *state = (Scanner *)payload;
  if (!valid_symbols[LITERAL_TEXT]) return false;

  bool has_content = false;

  for (;;) {
    int32_t c = lexer->lookahead;

    if (c == 0) {
      if (has_content) { lexer->result_symbol = LITERAL_TEXT; return true; }
      return false;
    }

    switch (c) {
      case '\r':
      case '\n':
        // If we've collected content, emit it before newline; otherwise,
        // consume the newline and keep scanning within this token.
        if (has_content) {
          lexer->result_symbol = LITERAL_TEXT;
          return true;
        }
        lexer->advance(lexer, false); // consume newline/carriage return
        continue;

      case '{': {
        state->started = true;
        if (!has_content) {
          // At BOF: peek ahead to determine if this starts a valid construct.
          // Only advance when we intend to emit literal_text; otherwise, defer to grammar.
          lexer->mark_end(lexer);             // potential end before '{'
          lexer->advance(lexer, false);       // consume '{' for inspection
          int32_t n = lexer->lookahead;

          // If it's a Go-template opener '{{', let grammar handle it (with recovery if unclosed)
          if (n == '{') {
            return false;
          }

          // Single-brace: check if this could be a valid property and if it closes on this line
          bool maybe_property = (n == '}' || n == ':' || n == '@' || n == '$' || is_ident_start(n) || is_digit(n));

          if (maybe_property) {
            bool saw_close = false;
            while (lexer->lookahead && lexer->lookahead != '\n' && lexer->lookahead != '\r') {
              if (lexer->lookahead == '}') { saw_close = true; break; }
              lexer->advance(lexer, false);
            }
            if (saw_close) {
              // Well-formed property ahead → let grammar parse it
              return false;
            }
          }

          // Not a valid property on this line → treat as literal
          has_content = true;
          continue;
        }

        // We're in the middle of literal text. Decide whether to stop before
        // this '{' (if it begins a valid construct that closes on this line),
        // or to consume it as literal (for invalid/unclosed cases).
        lexer->mark_end(lexer); // potential end before '{'

        // Peek next char
        lexer->advance(lexer, false); // consume '{' for inspection
        int32_t n = lexer->lookahead;

        if (n == '{') {
          // Go-template candidate: look for a matching '}}' before newline/EOF
          bool saw_close = false;
          int32_t prev = 0;
          while (lexer->lookahead && lexer->lookahead != '\n') {
            if (prev == '}' && lexer->lookahead == '}') { saw_close = true; break; }
            prev = lexer->lookahead;
            lexer->advance(lexer, false);
          }

          if (saw_close) {
            // End literal before the '{{'
            lexer->result_symbol = LITERAL_TEXT;
            return true;
          }

          // Unclosed '{{' → end literal before '{{' to let grammar recover
          lexer->result_symbol = LITERAL_TEXT;
          return true;
        }

        // Single-brace property candidate
        bool maybe_property = (n == '}' || n == ':' || n == '@' || n == '$' || is_ident_start(n) || is_digit(n));
        if (maybe_property) {
          // Look for a closing '}' before newline/EOF
          bool saw_close = false;
          while (lexer->lookahead && lexer->lookahead != '\n') {
            if (lexer->lookahead == '}') { saw_close = true; break; }
            lexer->advance(lexer, false);
          }

          if (saw_close) {
            // End literal before '{'
            lexer->result_symbol = LITERAL_TEXT;
            return true;
          }

          // Unclosed '{' ... treat the rest of the line as literal
          lexer->mark_end(lexer);
          has_content = true;
          continue;
        }

        // Definitely not a property — consume as literal
        has_content = true;
        continue;
      }

      case '$': {
        state->started = true;
        if (!has_content) {
          // At BOF: check if a well-formed builtin follows; else treat as literal
          lexer->advance(lexer, false); // consume '$'
          if (lexer->lookahead == '{') {
            bool saw_close = false;
            while (lexer->lookahead && lexer->lookahead != '\n' && lexer->lookahead != '\r') {
              if (lexer->lookahead == '}') { saw_close = true; break; }
              lexer->advance(lexer, false);
            }
            if (saw_close) {
              return false; // real builtin
            }
            // Unclosed ${ → literal
            has_content = true;
            continue;
          }
          // Lone '$' → literal
          has_content = true;
          continue;
        }

        // In the middle of literal text; check for '${...}' with closing '}'
        lexer->mark_end(lexer); // end before '$'
        lexer->advance(lexer, false); // consume '$' for inspection
        if (lexer->lookahead == '{') {
          // Look for a closing '}' before newline/EOF
          bool saw_close = false;
          while (lexer->lookahead && lexer->lookahead != '\n') {
            if (lexer->lookahead == '}') { saw_close = true; break; }
            lexer->advance(lexer, false);
          }

          if (saw_close) {
            lexer->result_symbol = LITERAL_TEXT;
            return true;
          }

          // Unclosed '${' ... treat the rest of the line as literal
          lexer->mark_end(lexer);
          has_content = true;
          continue;
        }

        // Lone '$' — treat as literal
        has_content = true;
        continue;
      }

      default:
        state->started = true;
        lexer->advance(lexer, false);
        lexer->mark_end(lexer);
        has_content = true;
        break;
    }
  }
}
