# tree-sitter-mtlog Implementation Guide

## Prerequisites

Before implementing, ensure you have:
- Node.js 14+ and npm installed
- C/C++ compiler (for node-gyp)
- tree-sitter CLI: `npm install -g tree-sitter-cli`
- Basic understanding of parser theory and JavaScript

## Project Setup

### Initial Structure

```bash
mkdir tree-sitter-mtlog
cd tree-sitter-mtlog
npm init -y

# Install tree-sitter as a dev dependency
npm install --save-dev tree-sitter-cli

# Create initial structure
mkdir -p test/corpus queries src
touch grammar.js binding.gyp .gitignore
```

### Package Configuration

```json
// package.json additions
{
  "main": "bindings/node",
  "scripts": {
    "test": "tree-sitter test",
    "generate": "tree-sitter generate",
    "build": "tree-sitter generate && node-gyp rebuild",
    "parse": "tree-sitter parse",
    "highlight": "tree-sitter highlight"
  },
  "tree-sitter": [
    {
      "scope": "source.mtlog",
      "injection-regex": "^mtlog$",
      "file-types": []
    }
  ]
}
```

### Binding Configuration

```python
# binding.gyp
{
  "targets": [
    {
      "target_name": "tree_sitter_mtlog_binding",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "src"
      ],
      "sources": [
        "bindings/node/binding.cc",
        "src/parser.c"
      ],
      "cflags_c": [
        "-std=c99"
      ]
    }
  ]
}
```

## Grammar Development

### Core Grammar Structure

The grammar.js file defines how templates are parsed. Key tree-sitter concepts:

```javascript
module.exports = grammar({
  name: 'mtlog',
  
  // Conflict resolution
  conflicts: $ => [
    // Define any ambiguous parse scenarios
  ],
  
  // External scanner for complex lexing (if needed)
  externals: $ => [
    // Define tokens requiring custom C scanner
  ],
  
  // Inline rules for performance
  inline: $ => [
    // Rules to inline into parent rules
  ],
  
  rules: {
    // Entry point - must be first rule
    template: $ => repeat($._element),
    
    // ... rest of rules
  }
});
```

### Implementing Property Rules

Use tree-sitter's built-in functions effectively:

```javascript
// Use field() to name components for queries
property: $ => seq(
  '{',
  field('hint', optional(choice('@', '$'))),
  field('name', $._property_name),
  field('format', optional(seq(':', $.format_string))),
  '}'
),

// Use prec() for precedence
_element: $ => choice(
  prec(-1, $.literal_text),  // Lower precedence
  prec(1, $.property),        // Higher precedence
  prec(1, $.go_property),
  prec(1, $.builtin_property)
),

// Use token() for atomic tokens
format_string: $ => token(prec(-1, /[^}]+/)),

// Use repeat1() vs repeat()
literal_text: $ => repeat1(  // Must match at least once
  choice(
    /[^{$}]+/,
    /[$}]/
  )
)
```

### Handling Ambiguity

Tree-sitter requires unambiguous grammars. Handle potential conflicts:

```javascript
// Use token.immediate() for no-whitespace tokens
closing_brace: $ => token.immediate('}'),

// Use prec.left/right for associativity
literal_text: $ => prec.right(repeat1(
  // Right associative - consume as much as possible
  choice(/[^{$}]+/, /[$}]/)
)),

// Declare conflicts explicitly
conflicts: $ => [
  [$.property, $.literal_text],
  [$.go_property, $.literal_text]
]
```

## Testing Framework

### Corpus Test Format

Tree-sitter uses a specific test format in test/corpus/\*.txt:

```
==================
Simple property
==================
User {UserId} logged in
---

(template
  (literal_text)
  (property
    name: (identifier))
  (literal_text))

==================
Property with format
==================
Price: {Amount:F2}
---

(template
  (literal_text)
  (property
    name: (identifier)
    format: (format_string)))
```

### Test Development Strategy

1. **Start with simple cases**: Single property, no format
2. **Add complexity gradually**: Formats, hints, dotted names
3. **Include edge cases**: Empty properties, malformed input
4. **Test boundaries**: Properties at start/end of string
5. **Verify error recovery**: Unclosed brackets, invalid syntax

### Running Tests

```bash
# Run all tests
tree-sitter test

# Run specific test file
tree-sitter test test/corpus/properties.txt

# Test with filter
tree-sitter test -f "Simple property"

# Update test output
tree-sitter test --update
```

## Query Development

### Highlights Query

Create queries/highlights.scm following tree-sitter conventions:

```scheme
; Use standard capture names from tree-sitter docs
; https://tree-sitter.github.io/tree-sitter/syntax-highlighting#standard-capture-names

; Punctuation
(property "{" @punctuation.bracket)
(property "}" @punctuation.bracket)

; Special punctuation for Go templates
(go_property "{{" @punctuation.special)
(go_property "}}" @punctuation.special)

; Variables
(property name: (identifier) @variable.parameter)
(property name: (dotted_name) @variable.member)

; Operators
(property hint: "@" @operator)
(property hint: "$" @operator)

; Types
(property format: (format_string) @type)

; Numbers
(property name: (numeric_index) @number)

; Constants
(builtin_property name: (identifier) @constant.builtin)
```

### Text Objects Query

Create queries/textobjects.scm for structural navigation:

```scheme
; Entire property including delimiters
(property) @property.outer
(go_property) @property.outer
(builtin_property) @property.outer

; Just the property name
(property name: (_) @property.inner)

; Format specifier
(property format: (format_string) @format.inner)

; All properties (for bulk operations)
(template (property) @property.all)
```

### Injection Query

Create queries/injections.scm for parsing templates in Go strings:

```scheme
; Target mtlog method calls only
((call_expression
  function: (selector_expression
    field: (field_identifier) @_method)
  arguments: (argument_list
    . (interpreted_string_literal
        (interpreted_string_literal_content) @injection.content)))
  (#any-of? @_method 
    "Debug" "Verbose" "Information" "Info"
    "Warning" "Warn" "Error" "Fatal")
  (#set! injection.language "mtlog")
  (#set! injection.combined))
```

## Performance Optimization

### Grammar Optimization

1. **Minimize backtracking**: Use `token()` for atomic matches
2. **Inline small rules**: Add frequently-used rules to `inline: $`
3. **Avoid deep recursion**: Use `repeat()` instead of recursive rules
4. **Optimize regex**: Compile complex patterns outside the grammar

### Testing Performance

```bash
# Generate parser with optimization stats
tree-sitter generate --log

# Parse large file with timing
time tree-sitter parse large_file.go

# Profile parser performance
tree-sitter parse --debug large_file.go
```

### Benchmarking Script

Create benchmark/bench.js:

```javascript
const Parser = require('tree-sitter');
const Mtlog = require('../');

const parser = new Parser();
parser.setLanguage(Mtlog);

const iterations = 1000;
const template = 'User {UserId} logged in from {IP:15} at {Timestamp:HH:mm:ss}';

console.time('parse');
for (let i = 0; i < iterations; i++) {
  parser.parse(template);
}
console.timeEnd('parse');
```

## Build Process

### Local Development

```bash
# Generate C code from grammar
tree-sitter generate

# Build parser
node-gyp rebuild

# Test parser works
tree-sitter parse examples/simple.mtlog

# Test highlighting
tree-sitter highlight examples/simple.mtlog
```

### Continuous Integration

Create .github/workflows/ci.yml:

```yaml
name: CI
on: [push, pull_request]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - uses: actions/setup-node@v3
        with:
          node-version: 18
      - run: npm install
      - run: npm run generate
      - run: npm test
      - run: npm run benchmark
```

## Integration Testing

### Neovim Integration Test

Create test/integration/nvim_test.lua:

```lua
-- Test that parser loads and highlights correctly
local parser = require'nvim-treesitter.parsers'.get_parser(0, 'mtlog')
local tree = parser:parse()[1]
local root = tree:root()

-- Verify tree structure
assert(root:type() == 'template')

-- Test queries load
local query = vim.treesitter.query.parse('mtlog', [[
  (property name: (identifier) @test)
]])
```

### Automated Integration Tests

```bash
#!/bin/bash
# test/integration/test.sh

# Test parser generation
tree-sitter generate || exit 1

# Test parsing
echo "User {UserId} logged in" | tree-sitter parse -x || exit 1

# Test highlighting  
tree-sitter highlight test/fixtures/example.mtlog || exit 1

# Test corpus
tree-sitter test || exit 1
```

## Debugging Techniques

### Parser Debugging

```bash
# Show parse tree
tree-sitter parse --debug test.mtlog

# Show parse steps
tree-sitter parse --debug-graph test.mtlog

# Generate DOT graph
tree-sitter parse --dot test.mtlog | dot -Tpng > parse.png
```

### Query Debugging

```scheme
; Test queries interactively
; queries/test.scm
(property 
  name: (identifier) @debug.name
  (#eq? @debug.name "UserId"))
```

### Common Issues and Solutions

1. **Shift/reduce conflicts**: Use precedence or refactor rules
2. **Infinite loops**: Check for left recursion
3. **Performance issues**: Profile with `--debug` flag
4. **Query not matching**: Use `tree-sitter query` to test patterns

## Publishing

### Pre-publish Checklist

1. All tests pass: `npm test`
2. Generated files current: `tree-sitter generate`
3. Benchmarks acceptable: `npm run benchmark`
4. Queries work in target editors
5. README complete with examples
6. LICENSE file present

### NPM Publishing

```bash
# Build all binaries
npm run build

# Test installation locally
npm pack
npm install -g tree-sitter-mtlog-*.tgz

# Publish
npm publish
```

### Integration with Editors

For Neovim:
1. Submit PR to nvim-treesitter/nvim-treesitter
2. Add to supported languages list
3. Include queries in runtime/queries/mtlog/

For Zed:
1. Create extension following Zed's documentation
2. Reference npm package in extension.toml
3. Submit to Zed extension registry

## Maintenance Guide

### Version Updates

When mtlog syntax changes:
1. Update grammar.js with new syntax
2. Add test cases to corpus
3. Update highlight queries if needed
4. Bump version following semver
5. Document changes in CHANGELOG

### Performance Monitoring

Track key metrics:
- Parse time for typical templates
- Memory usage for large files
- Query execution time
- Editor responsiveness with injection

### Community Support

- Answer issues about grammar behavior
- Direct validation questions to mtlog-analyzer
- Maintain clear scope boundaries in documentation

This guide provides the framework for implementing tree-sitter-mtlog while avoiding the complexity of validation logic. The focus remains on clean, performant syntax highlighting that enhances the developer experience without duplicating mtlog-analyzer's role.