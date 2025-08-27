#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 44
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 27
#define ALIAS_COUNT 0
#define TOKEN_COUNT 14
#define EXTERNAL_TOKEN_COUNT 1
#define FIELD_COUNT 4
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 10

enum {
  sym_open_brace = 1,
  anon_sym_RBRACE = 2,
  anon_sym_DOT = 3,
  sym_open_go = 4,
  sym_close_go = 5,
  sym_open_builtin = 6,
  anon_sym_AT = 7,
  anon_sym_DOLLAR = 8,
  sym_identifier = 9,
  sym_numeric_index = 10,
  anon_sym_COLON = 11,
  aux_sym_format_spec_token1 = 12,
  sym_literal_text = 13,
  sym_template = 14,
  sym__template_content = 15,
  sym_property = 16,
  sym_close_brace = 17,
  sym_go_property = 18,
  sym_builtin_property = 19,
  sym_close_builtin = 20,
  sym_hint_symbol = 21,
  sym__property_name = 22,
  sym_dotted_name = 23,
  sym_format_spec = 24,
  aux_sym_template_repeat1 = 25,
  aux_sym_dotted_name_repeat1 = 26,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_open_brace] = "open_brace",
  [anon_sym_RBRACE] = "}",
  [anon_sym_DOT] = ".",
  [sym_open_go] = "open_go",
  [sym_close_go] = "close_go",
  [sym_open_builtin] = "open_builtin",
  [anon_sym_AT] = "@",
  [anon_sym_DOLLAR] = "$",
  [sym_identifier] = "identifier",
  [sym_numeric_index] = "numeric_index",
  [anon_sym_COLON] = ":",
  [aux_sym_format_spec_token1] = "identifier",
  [sym_literal_text] = "literal_text",
  [sym_template] = "template",
  [sym__template_content] = "_template_content",
  [sym_property] = "property",
  [sym_close_brace] = "close_brace",
  [sym_go_property] = "go_property",
  [sym_builtin_property] = "builtin_property",
  [sym_close_builtin] = "close_builtin",
  [sym_hint_symbol] = "hint_symbol",
  [sym__property_name] = "_property_name",
  [sym_dotted_name] = "dotted_name",
  [sym_format_spec] = "format_spec",
  [aux_sym_template_repeat1] = "template_repeat1",
  [aux_sym_dotted_name_repeat1] = "dotted_name_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_open_brace] = sym_open_brace,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_open_go] = sym_open_go,
  [sym_close_go] = sym_close_go,
  [sym_open_builtin] = sym_open_builtin,
  [anon_sym_AT] = anon_sym_AT,
  [anon_sym_DOLLAR] = anon_sym_DOLLAR,
  [sym_identifier] = sym_identifier,
  [sym_numeric_index] = sym_numeric_index,
  [anon_sym_COLON] = anon_sym_COLON,
  [aux_sym_format_spec_token1] = sym_identifier,
  [sym_literal_text] = sym_literal_text,
  [sym_template] = sym_template,
  [sym__template_content] = sym__template_content,
  [sym_property] = sym_property,
  [sym_close_brace] = sym_close_brace,
  [sym_go_property] = sym_go_property,
  [sym_builtin_property] = sym_builtin_property,
  [sym_close_builtin] = sym_close_builtin,
  [sym_hint_symbol] = sym_hint_symbol,
  [sym__property_name] = sym__property_name,
  [sym_dotted_name] = sym_dotted_name,
  [sym_format_spec] = sym_format_spec,
  [aux_sym_template_repeat1] = aux_sym_template_repeat1,
  [aux_sym_dotted_name_repeat1] = aux_sym_dotted_name_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_open_brace] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [sym_open_go] = {
    .visible = true,
    .named = true,
  },
  [sym_close_go] = {
    .visible = true,
    .named = true,
  },
  [sym_open_builtin] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_AT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOLLAR] = {
    .visible = true,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_numeric_index] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_format_spec_token1] = {
    .visible = true,
    .named = true,
  },
  [sym_literal_text] = {
    .visible = true,
    .named = true,
  },
  [sym_template] = {
    .visible = true,
    .named = true,
  },
  [sym__template_content] = {
    .visible = false,
    .named = true,
  },
  [sym_property] = {
    .visible = true,
    .named = true,
  },
  [sym_close_brace] = {
    .visible = true,
    .named = true,
  },
  [sym_go_property] = {
    .visible = true,
    .named = true,
  },
  [sym_builtin_property] = {
    .visible = true,
    .named = true,
  },
  [sym_close_builtin] = {
    .visible = true,
    .named = true,
  },
  [sym_hint_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym__property_name] = {
    .visible = false,
    .named = true,
  },
  [sym_dotted_name] = {
    .visible = true,
    .named = true,
  },
  [sym_format_spec] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_template_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_dotted_name_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_format = 1,
  field_format_string = 2,
  field_hint = 3,
  field_name = 4,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_format] = "format",
  [field_format_string] = "format_string",
  [field_hint] = "hint",
  [field_name] = "name",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 1},
  [4] = {.index = 3, .length = 1},
  [5] = {.index = 4, .length = 2},
  [6] = {.index = 6, .length = 2},
  [7] = {.index = 8, .length = 2},
  [8] = {.index = 10, .length = 1},
  [9] = {.index = 11, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_format_string, 1},
  [1] =
    {field_hint, 1},
  [2] =
    {field_name, 1},
  [3] =
    {field_format, 1},
  [4] =
    {field_hint, 1},
    {field_name, 2},
  [6] =
    {field_format, 2},
    {field_hint, 1},
  [8] =
    {field_format, 2},
    {field_name, 1},
  [10] =
    {field_name, 2},
  [11] =
    {field_format, 3},
    {field_hint, 1},
    {field_name, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(11);
      if (lookahead == '\n') SKIP(0)
      if (lookahead == '\r') SKIP(8)
      if (lookahead == '$') ADVANCE(21);
      if (lookahead == '.') ADVANCE(15);
      if (lookahead == ':') ADVANCE(24);
      if (lookahead == '@') ADVANCE(19);
      if (lookahead == '{') ADVANCE(12);
      if (lookahead == '}') ADVANCE(14);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(22);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(2)
      END_STATE();
    case 2:
      if (lookahead == '\n') SKIP(2)
      if (lookahead == '\r') SKIP(1)
      if (lookahead == '$') ADVANCE(20);
      if (lookahead == ':') ADVANCE(24);
      if (lookahead == '@') ADVANCE(19);
      if (lookahead == '}') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(22);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(4)
      END_STATE();
    case 4:
      if (lookahead == '\n') SKIP(4)
      if (lookahead == '\r') SKIP(3)
      if (lookahead == '}') ADVANCE(7);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(22);
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(25);
      if (lookahead == '\r') ADVANCE(26);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(27);
      END_STATE();
    case 6:
      if (lookahead == '{') ADVANCE(18);
      END_STATE();
    case 7:
      if (lookahead == '}') ADVANCE(17);
      END_STATE();
    case 8:
      if (eof) ADVANCE(11);
      if (lookahead == '\n') SKIP(0)
      END_STATE();
    case 9:
      if (eof) ADVANCE(11);
      if (lookahead == '\n') SKIP(10)
      END_STATE();
    case 10:
      if (eof) ADVANCE(11);
      if (lookahead == '\n') SKIP(10)
      if (lookahead == '\r') SKIP(9)
      if (lookahead == '$') ADVANCE(6);
      if (lookahead == ':') ADVANCE(24);
      if (lookahead == '{') ADVANCE(12);
      if (lookahead == '}') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(22);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym_open_brace);
      if (lookahead == '{') ADVANCE(16);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      if (lookahead == '}') ADVANCE(17);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(sym_open_go);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(sym_close_go);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(sym_open_builtin);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_DOLLAR);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_DOLLAR);
      if (lookahead == '{') ADVANCE(18);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(22);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(sym_numeric_index);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(aux_sym_format_spec_token1);
      if (lookahead == '\n') ADVANCE(25);
      if (lookahead == '\r') ADVANCE(26);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(27);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(aux_sym_format_spec_token1);
      if (lookahead == '\n') ADVANCE(25);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(27);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(aux_sym_format_spec_token1);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(27);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 10, .external_lex_state = 1},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 10, .external_lex_state = 1},
  [4] = {.lex_state = 10, .external_lex_state = 1},
  [5] = {.lex_state = 10},
  [6] = {.lex_state = 10},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 10, .external_lex_state = 1},
  [9] = {.lex_state = 10, .external_lex_state = 1},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 10, .external_lex_state = 1},
  [12] = {.lex_state = 10, .external_lex_state = 1},
  [13] = {.lex_state = 10, .external_lex_state = 1},
  [14] = {.lex_state = 10, .external_lex_state = 1},
  [15] = {.lex_state = 4},
  [16] = {.lex_state = 10, .external_lex_state = 1},
  [17] = {.lex_state = 10, .external_lex_state = 1},
  [18] = {.lex_state = 10, .external_lex_state = 1},
  [19] = {.lex_state = 10, .external_lex_state = 1},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 10, .external_lex_state = 1},
  [22] = {.lex_state = 10, .external_lex_state = 1},
  [23] = {.lex_state = 10, .external_lex_state = 1},
  [24] = {.lex_state = 10, .external_lex_state = 1},
  [25] = {.lex_state = 10, .external_lex_state = 1},
  [26] = {.lex_state = 10, .external_lex_state = 1},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 10},
  [29] = {.lex_state = 10},
  [30] = {.lex_state = 10},
  [31] = {.lex_state = 10},
  [32] = {.lex_state = 10},
  [33] = {.lex_state = 10},
  [34] = {.lex_state = 10},
  [35] = {.lex_state = 10},
  [36] = {.lex_state = 10},
  [37] = {.lex_state = 10},
  [38] = {.lex_state = 4},
  [39] = {.lex_state = 10},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 5},
};

enum {
  ts_external_token_literal_text = 0,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_literal_text] = sym_literal_text,
};

static const bool ts_external_scanner_states[2][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_literal_text] = true,
  },
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_open_brace] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [sym_open_go] = ACTIONS(1),
    [sym_close_go] = ACTIONS(1),
    [sym_open_builtin] = ACTIONS(1),
    [anon_sym_AT] = ACTIONS(1),
    [anon_sym_DOLLAR] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [sym_numeric_index] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [sym_literal_text] = ACTIONS(1),
  },
  [1] = {
    [sym_template] = STATE(40),
    [sym__template_content] = STATE(4),
    [sym_property] = STATE(4),
    [sym_go_property] = STATE(4),
    [sym_builtin_property] = STATE(4),
    [aux_sym_template_repeat1] = STATE(4),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym_open_brace] = ACTIONS(5),
    [sym_open_go] = ACTIONS(7),
    [sym_open_builtin] = ACTIONS(9),
    [sym_literal_text] = ACTIONS(11),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 9,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(19), 1,
      sym_numeric_index,
    ACTIONS(21), 1,
      anon_sym_COLON,
    STATE(5), 1,
      sym_hint_symbol,
    STATE(12), 1,
      sym_close_brace,
    STATE(37), 1,
      sym_format_spec,
    ACTIONS(15), 2,
      anon_sym_AT,
      anon_sym_DOLLAR,
    STATE(31), 2,
      sym__property_name,
      sym_dotted_name,
  [30] = 6,
    ACTIONS(23), 1,
      ts_builtin_sym_end,
    ACTIONS(25), 1,
      sym_open_brace,
    ACTIONS(28), 1,
      sym_open_go,
    ACTIONS(31), 1,
      sym_open_builtin,
    ACTIONS(34), 1,
      sym_literal_text,
    STATE(3), 5,
      sym__template_content,
      sym_property,
      sym_go_property,
      sym_builtin_property,
      aux_sym_template_repeat1,
  [53] = 6,
    ACTIONS(5), 1,
      sym_open_brace,
    ACTIONS(7), 1,
      sym_open_go,
    ACTIONS(9), 1,
      sym_open_builtin,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    ACTIONS(39), 1,
      sym_literal_text,
    STATE(3), 5,
      sym__template_content,
      sym_property,
      sym_go_property,
      sym_builtin_property,
      aux_sym_template_repeat1,
  [76] = 7,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(21), 1,
      anon_sym_COLON,
    ACTIONS(41), 1,
      sym_numeric_index,
    STATE(24), 1,
      sym_close_brace,
    STATE(33), 1,
      sym_format_spec,
    STATE(29), 2,
      sym__property_name,
      sym_dotted_name,
  [99] = 7,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(21), 1,
      anon_sym_COLON,
    ACTIONS(43), 1,
      anon_sym_RBRACE,
    ACTIONS(45), 1,
      sym_numeric_index,
    STATE(17), 1,
      sym_close_builtin,
    STATE(36), 1,
      sym_format_spec,
    STATE(30), 2,
      sym__property_name,
      sym_dotted_name,
  [122] = 4,
    ACTIONS(47), 1,
      anon_sym_RBRACE,
    ACTIONS(49), 1,
      anon_sym_DOT,
    STATE(20), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(51), 2,
      sym_close_go,
      anon_sym_COLON,
  [136] = 2,
    ACTIONS(55), 1,
      sym_open_brace,
    ACTIONS(53), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [146] = 2,
    ACTIONS(59), 1,
      sym_open_brace,
    ACTIONS(57), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [156] = 4,
    ACTIONS(49), 1,
      anon_sym_DOT,
    ACTIONS(61), 1,
      anon_sym_RBRACE,
    STATE(7), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(63), 2,
      sym_close_go,
      anon_sym_COLON,
  [170] = 2,
    ACTIONS(67), 1,
      sym_open_brace,
    ACTIONS(65), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [180] = 2,
    ACTIONS(71), 1,
      sym_open_brace,
    ACTIONS(69), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [190] = 2,
    ACTIONS(75), 1,
      sym_open_brace,
    ACTIONS(73), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [200] = 2,
    ACTIONS(79), 1,
      sym_open_brace,
    ACTIONS(77), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [210] = 4,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(81), 1,
      sym_close_go,
    ACTIONS(83), 1,
      sym_numeric_index,
    STATE(38), 2,
      sym__property_name,
      sym_dotted_name,
  [224] = 2,
    ACTIONS(87), 1,
      sym_open_brace,
    ACTIONS(85), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [234] = 2,
    ACTIONS(91), 1,
      sym_open_brace,
    ACTIONS(89), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [244] = 2,
    ACTIONS(95), 1,
      sym_open_brace,
    ACTIONS(93), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [254] = 2,
    ACTIONS(99), 1,
      sym_open_brace,
    ACTIONS(97), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [264] = 4,
    ACTIONS(101), 1,
      anon_sym_RBRACE,
    ACTIONS(103), 1,
      anon_sym_DOT,
    STATE(20), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(106), 2,
      sym_close_go,
      anon_sym_COLON,
  [278] = 2,
    ACTIONS(110), 1,
      sym_open_brace,
    ACTIONS(108), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [288] = 2,
    ACTIONS(114), 1,
      sym_open_brace,
    ACTIONS(112), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [298] = 2,
    ACTIONS(118), 1,
      sym_open_brace,
    ACTIONS(116), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [308] = 2,
    ACTIONS(122), 1,
      sym_open_brace,
    ACTIONS(120), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [318] = 2,
    ACTIONS(126), 1,
      sym_open_brace,
    ACTIONS(124), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [328] = 2,
    ACTIONS(130), 1,
      sym_open_brace,
    ACTIONS(128), 4,
      sym_literal_text,
      ts_builtin_sym_end,
      sym_open_go,
      sym_open_builtin,
  [338] = 2,
    ACTIONS(101), 1,
      anon_sym_RBRACE,
    ACTIONS(106), 3,
      anon_sym_DOT,
      sym_close_go,
      anon_sym_COLON,
  [347] = 1,
    ACTIONS(132), 4,
      anon_sym_RBRACE,
      sym_identifier,
      sym_numeric_index,
      anon_sym_COLON,
  [354] = 4,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    ACTIONS(21), 1,
      anon_sym_COLON,
    STATE(19), 1,
      sym_close_brace,
    STATE(35), 1,
      sym_format_spec,
  [367] = 4,
    ACTIONS(21), 1,
      anon_sym_COLON,
    ACTIONS(43), 1,
      anon_sym_RBRACE,
    STATE(23), 1,
      sym_close_builtin,
    STATE(34), 1,
      sym_format_spec,
  [380] = 4,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    ACTIONS(21), 1,
      anon_sym_COLON,
    STATE(26), 1,
      sym_close_brace,
    STATE(32), 1,
      sym_format_spec,
  [393] = 2,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    STATE(14), 1,
      sym_close_brace,
  [400] = 2,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    STATE(18), 1,
      sym_close_brace,
  [407] = 2,
    ACTIONS(43), 1,
      anon_sym_RBRACE,
    STATE(11), 1,
      sym_close_builtin,
  [414] = 2,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    STATE(9), 1,
      sym_close_brace,
  [421] = 2,
    ACTIONS(43), 1,
      anon_sym_RBRACE,
    STATE(22), 1,
      sym_close_builtin,
  [428] = 2,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    STATE(8), 1,
      sym_close_brace,
  [435] = 1,
    ACTIONS(134), 1,
      sym_close_go,
  [439] = 1,
    ACTIONS(136), 1,
      anon_sym_RBRACE,
  [443] = 1,
    ACTIONS(138), 1,
      ts_builtin_sym_end,
  [447] = 1,
    ACTIONS(140), 1,
      sym_identifier,
  [451] = 1,
    ACTIONS(142), 1,
      anon_sym_DOT,
  [455] = 1,
    ACTIONS(144), 1,
      aux_sym_format_spec_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 30,
  [SMALL_STATE(4)] = 53,
  [SMALL_STATE(5)] = 76,
  [SMALL_STATE(6)] = 99,
  [SMALL_STATE(7)] = 122,
  [SMALL_STATE(8)] = 136,
  [SMALL_STATE(9)] = 146,
  [SMALL_STATE(10)] = 156,
  [SMALL_STATE(11)] = 170,
  [SMALL_STATE(12)] = 180,
  [SMALL_STATE(13)] = 190,
  [SMALL_STATE(14)] = 200,
  [SMALL_STATE(15)] = 210,
  [SMALL_STATE(16)] = 224,
  [SMALL_STATE(17)] = 234,
  [SMALL_STATE(18)] = 244,
  [SMALL_STATE(19)] = 254,
  [SMALL_STATE(20)] = 264,
  [SMALL_STATE(21)] = 278,
  [SMALL_STATE(22)] = 288,
  [SMALL_STATE(23)] = 298,
  [SMALL_STATE(24)] = 308,
  [SMALL_STATE(25)] = 318,
  [SMALL_STATE(26)] = 328,
  [SMALL_STATE(27)] = 338,
  [SMALL_STATE(28)] = 347,
  [SMALL_STATE(29)] = 354,
  [SMALL_STATE(30)] = 367,
  [SMALL_STATE(31)] = 380,
  [SMALL_STATE(32)] = 393,
  [SMALL_STATE(33)] = 400,
  [SMALL_STATE(34)] = 407,
  [SMALL_STATE(35)] = 414,
  [SMALL_STATE(36)] = 421,
  [SMALL_STATE(37)] = 428,
  [SMALL_STATE(38)] = 435,
  [SMALL_STATE(39)] = 439,
  [SMALL_STATE(40)] = 443,
  [SMALL_STATE(41)] = 447,
  [SMALL_STATE(42)] = 451,
  [SMALL_STATE(43)] = 455,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_template, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_template_repeat1, 2),
  [25] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_template_repeat1, 2), SHIFT_REPEAT(2),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_template_repeat1, 2), SHIFT_REPEAT(42),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_template_repeat1, 2), SHIFT_REPEAT(6),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_template_repeat1, 2), SHIFT_REPEAT(3),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_template, 1),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [47] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dotted_name, 2),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [51] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dotted_name, 2),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 3, .production_id = 4),
  [55] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 3, .production_id = 4),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 5, .production_id = 9),
  [59] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 5, .production_id = 9),
  [61] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__property_name, 1),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__property_name, 1),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_property, 4, .production_id = 7),
  [67] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_property, 4, .production_id = 7),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 2),
  [71] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 2),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_go_property, 4, .production_id = 8),
  [75] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_go_property, 4, .production_id = 8),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 4, .production_id = 7),
  [79] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 4, .production_id = 7),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_close_builtin, 1),
  [87] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_close_builtin, 1),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_property, 2),
  [91] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_property, 2),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 4, .production_id = 6),
  [95] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 4, .production_id = 6),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 4, .production_id = 5),
  [99] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 4, .production_id = 5),
  [101] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_dotted_name_repeat1, 2),
  [103] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_dotted_name_repeat1, 2), SHIFT_REPEAT(41),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_dotted_name_repeat1, 2),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_close_brace, 1),
  [110] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_close_brace, 1),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_property, 3, .production_id = 4),
  [114] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_property, 3, .production_id = 4),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_builtin_property, 3, .production_id = 3),
  [118] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_builtin_property, 3, .production_id = 3),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 3, .production_id = 2),
  [122] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 3, .production_id = 2),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_go_property, 3),
  [126] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_go_property, 3),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property, 3, .production_id = 3),
  [130] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_property, 3, .production_id = 3),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_hint_symbol, 1),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_format_spec, 2, .production_id = 1),
  [138] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_mtlog_external_scanner_create(void);
void tree_sitter_mtlog_external_scanner_destroy(void *);
bool tree_sitter_mtlog_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_mtlog_external_scanner_serialize(void *, char *);
void tree_sitter_mtlog_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_mtlog(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_mtlog_external_scanner_create,
      tree_sitter_mtlog_external_scanner_destroy,
      tree_sitter_mtlog_external_scanner_scan,
      tree_sitter_mtlog_external_scanner_serialize,
      tree_sitter_mtlog_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
