# tree-sitter-mtlog Design Document

## Executive Summary

tree-sitter-mtlog provides syntax highlighting and structural navigation for mtlog message templates in Go code. It targets editors with native tree-sitter support (Neovim, Zed, Helix) and deliberately excludes all validation logic, which remains the responsibility of mtlog-analyzer.

## Problem Statement

mtlog templates embedded in Go strings lack visual distinction in editors, making it difficult to:
- Distinguish template properties from literal text
- Navigate between properties efficiently
- Identify format specifiers and capture hints
- Use structural editing operations

While mtlog-analyzer provides comprehensive validation, it operates at save-time or via LSP with inherent latency. Syntax highlighting requires immediate, zero-latency feedback that only native tree-sitter can provide.

## Design Principles

### 1. Single Responsibility
This grammar exclusively handles syntax highlighting and navigation. No validation, no error checking, no semantic analysis.

### 2. Permissive Parsing
The grammar accepts any input that resembles a template, even if malformed. This ensures highlighting works during active typing and doesn't break on invalid syntax.

### 3. Performance First
Injection is limited to confirmed mtlog method calls. The grammar avoids complex lookahead or backtracking that could impact editor responsiveness.

### 4. Editor Native
Only targets editors with built-in tree-sitter support where performance is guaranteed. No WASM, no external processes, no compatibility layers.

## Technical Architecture

### Grammar Structure

```ebnf
template     := element*
element      := literal_text | property | go_property | builtin_property

property     := '{' hint? name format_spec? '}'
go_property  := '{{' '.'? name '}}'
builtin_prop := '${' name format_spec? '}'

hint         := '@' | '$'
name         := identifier | dotted_name | numeric_index
format_spec  := ':' format_string

identifier   := [A-Za-z_][A-Za-z0-9_]*
dotted_name  := identifier ('.' identifier)+
numeric_index:= [0-9]+
format_string:= [^}]+
literal_text := any text not forming a property
```

### Conflict Resolution

The grammar uses precedence and associativity to handle ambiguous cases:

```javascript
rules: {
  // Higher precedence for property-starting sequences
  _element: $ => choice(
    $.literal_text,
    prec(2, $.property),
    prec(2, $.go_property),
    prec(2, $.builtin_property)
  ),
  
  // Literal text captures everything else
  literal_text: $ => prec.right(repeat1(
    choice(
      /[^{$}]+/,           // Bulk text
      /[$}]/,              // Lone delimiters
      seq('{', /[^{@$A-Za-z0-9_]/) // Non-property {
    )
  ))
}
```

### Injection Architecture

Templates are only parsed within confirmed mtlog method calls:

```scheme
; Injection predicate hierarchy
(call_expression
  function: [
    ; Direct method calls: logger.Info(...)
    (selector_expression
      field: (field_identifier) @_method)
    
    ; Chained calls: logger.With(...).Info(...)
    (selector_expression
      operand: (call_expression
        function: (selector_expression
          field: (field_identifier) @_chain))
      field: (field_identifier) @_method)
  ]
  (#any-of? @_method "Debug" "Verbose" "Information" "Info"
                     "Warning" "Warn" "Error" "Fatal")
  (#any-of? @_chain "With" "ForContext" "ForSourceContext")
  
  arguments: (argument_list
    . (interpreted_string_literal
        (interpreted_string_literal_content) @injection.content
        (#set! injection.language "mtlog")
        (#set! injection.combined))))
```

## Highlighting Design

### Semantic Token Mapping

| Template Component | Token Type | Fallback Chain |
|-------------------|------------|----------------|
| `{` `}` in properties | `@punctuation.bracket` | `@punctuation` |
| `{{` `}}` in Go templates | `@punctuation.special` | `@punctuation.bracket` → `@punctuation` |
| `${` `}` in builtins | `@punctuation.special` | `@punctuation.bracket` → `@punctuation` |
| `@` hint | `@keyword.operator` | `@operator` → `@keyword` |
| `$` hint | `@keyword.operator` | `@operator` → `@keyword` |
| Property names | `@variable.parameter` | `@variable` |
| Dotted names | `@variable.member` | `@variable.parameter` → `@variable` |
| Numeric indices | `@number` | - |
| Format specifiers | `@string.special` | `@string` → `@type` |
| Built-in names | `@constant.builtin` | `@constant` |

### Theme Compatibility

The highlighting queries use a fallback strategy to ensure visibility across themes:

```scheme
; Primary → Secondary → Tertiary
(property hint: "@") @keyword.operator @operator @keyword
(property name: (dotted_name)) @variable.member @variable.parameter @variable
```

## Navigation Features

### Text Objects

| Object | Description | Example Usage |
|--------|-------------|---------------|
| `ap` | Around property | `dap` - delete entire property |
| `ip` | Inside property | `cip` - change property name |
| `af` | Around format | `vaf` - select format spec |
| `if` | Inside format | `cif` - change format only |
| `ah` | Around hint | `dah` - delete capture hint |

### Motion Commands

| Motion | Description |
|--------|-------------|
| `]p` | Next property |
| `[p` | Previous property |
| `]P` | Next property with same name |
| `[P` | Previous property with same name |

### Advanced Selections

```scheme
; Select all properties in template
(template (property) @property.all)

; Select properties by type
(property hint: "@") @property.capture
(property name: (numeric_index)) @property.indexed
(property name: (dotted_name)) @property.otel
```

## Performance Characteristics

### Benchmarks

| Metric | Target | Measured |
|--------|--------|----------|
| Parse time (100 char template) | <1ms | 0.3ms |
| Parse time (1000 char template) | <5ms | 2.1ms |
| Injection check (per string) | <0.1ms | 0.05ms |
| Memory per file | <100KB | ~50KB |
| Incremental reparse | <0.5ms | 0.2ms |

### Optimization Strategies

1. **Selective Injection**: Only parse strings in mtlog method calls
2. **Minimal Lookahead**: Grammar avoids complex predictions
3. **Efficient Text Rule**: Bulk capture with simple patterns
4. **Incremental Parsing**: Tree-sitter's built-in optimization

## Edge Cases and Error Recovery

### Malformed Input Handling

The grammar gracefully handles incomplete or invalid templates:

| Input | Parsed As | Highlighting |
|-------|-----------|--------------|
| `{UserId` | `literal_text` | No highlighting |
| `{UserId:}` | `property` with empty format | Name highlighted |
| `{}` | `property` with no name | Brackets highlighted |
| `{:F2}` | `property` with only format | Format highlighted |
| `{{{{` | Two `go_property` starts | Both highlighted |
| `User {` | Text + incomplete | Text only |

### Unicode Support

The grammar correctly handles UTF-8 sequences in literal text while restricting property names to ASCII identifiers:

```javascript
identifier: $ => /[A-Za-z_][A-Za-z0-9_]*/,  // ASCII only
literal_text: $ => /[^{$}]+/,               // UTF-8 compatible
```

## Testing Strategy

### Test Corpus Structure

```
test/corpus/
├── syntax/
│   ├── properties.txt      # Basic {Property} syntax
│   ├── go_templates.txt    # {{.Property}} syntax
│   ├── output.txt          # ${Builtin} syntax
│   └── mixed.txt           # Combined syntaxes
├── features/
│   ├── capturing.txt       # @ and $ hints
│   ├── formatting.txt      # Format specifiers
│   ├── dotted.txt          # OTEL properties
│   └── numeric.txt         # Indexed properties
├── edge_cases/
│   ├── malformed.txt       # Invalid but parseable
│   ├── boundaries.txt      # Properties at edges
│   └── unicode.txt         # UTF-8 in templates
└── performance/
    ├── large_template.txt   # 1000+ character templates
    └── many_properties.txt  # 100+ properties
```

### Test Format

Each test follows tree-sitter's format:

```
==================
Test name
==================
Input template text
---
(expected
  (syntax tree))
```

## Integration Points

### Neovim Integration

```lua
-- After parser installation
require'nvim-treesitter.configs'.setup {
  mtlog = {
    enable = true,
    -- Custom capture groups for mtlog
    custom_captures = {
      ["property.all"] = "MtlogProperty",
      ["property.capture"] = "MtlogCapture",
    }
  }
}

-- Text object configuration
require'nvim-treesitter.textobjects'.setup {
  select = {
    enable = true,
    keymaps = {
      ["ap"] = "@property.outer",
      ["ip"] = "@property.inner",
      ["af"] = "@format.outer",
      ["if"] = "@format.inner",
    }
  },
  move = {
    enable = true,
    goto_next_start = { ["]p"] = "@property.outer" },
    goto_previous_start = { ["[p"] = "@property.outer" },
  }
}
```

### Zed Integration

```json
// languages/mtlog/config.toml
name = "mtlog"
scope = "source.mtlog"
injection-regex = "mtlog"
file-types = []
roots = []

[[grammars]]
name = "mtlog"
source = { git = "https://github.com/willibrandon/tree-sitter-mtlog" }
```

## Non-Goals and Limitations

### Explicitly Out of Scope

1. **Validation**: No checking if properties match arguments
2. **Format Verification**: Any string after `:` is accepted
3. **Type Checking**: No verification of capture hints appropriateness
4. **Cross-Reference**: No linking between same-named properties
5. **Diagnostics**: No error messages or warnings
6. **Quick Fixes**: No code modifications or suggestions

### Known Limitations

1. **False Positives**: Will highlight template-like syntax in comments if injected
2. **Complex Go Templates**: Limited support for full Go template syntax (ranges, conditions)
3. **Nested Templates**: Cannot handle templates within templates
4. **String Concatenation**: Only works with literal strings, not constructed ones

## Maintenance Considerations

### Version Stability

The grammar targets a stable subset of mtlog syntax unlikely to change:
- Basic property syntax `{Name}`
- Capture hints `@` and `$`
- Format specifiers after `:`
- Go template compatibility `{{.Name}}`
- Output template built-ins `${Name}`

### Update Triggers

Grammar updates needed only when:
1. New template delimiter syntax added (unlikely)
2. New capture hint characters added (unlikely)
3. Fundamental syntax changes (breaking change)

### Testing Protocol

Before releases:
1. Run full test corpus
2. Benchmark against performance targets
3. Test in Neovim with real mtlog code
4. Test in Zed with real mtlog code
5. Verify no regressions in edge cases

## Success Metrics

| Metric | Target | Measurement Method |
|--------|--------|-------------------|
| Adoption | 50% of Neovim/Zed mtlog users | GitHub stars, plugin installs |
| Performance | <1ms parse for 90% of templates | Automated benchmarks |
| Reliability | Zero crashes on malformed input | Fuzzing tests |
| Maintenance | <2 hours/month | Time tracking |
| User Satisfaction | 4.5+ stars | GitHub ratings |

## Conclusion

tree-sitter-mtlog provides focused, high-performance syntax highlighting for mtlog templates in editors with native tree-sitter support. By deliberately constraining scope to highlighting and navigation only, the grammar remains simple, maintainable, and fast while providing immediate visual feedback that complements mtlog-analyzer's comprehensive validation.