# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

tree-sitter-mtlog is a Tree-sitter grammar for the mtlog (Message Template Logging) library. It provides syntax highlighting and structural navigation for mtlog message templates in Go code, targeting editors with native tree-sitter support (Neovim, Zed, Helix).

## Core Development Commands

### Initial Setup
```bash
# Install tree-sitter CLI if not present
npm install -g tree-sitter-cli

# Initialize npm project
npm init -y
npm install --save-dev tree-sitter-cli

# Create required directories
mkdir -p test/corpus queries src
```

### Build Commands
```bash
# Generate parser from grammar
tree-sitter generate

# Compile parser
node-gyp rebuild

# Full build
tree-sitter generate && node-gyp rebuild
```

### Testing Commands
```bash
# Run all corpus tests
tree-sitter test

# Run specific test file
tree-sitter test test/corpus/properties.txt

# Run tests with filter
tree-sitter test -f "Simple property"

# Update test output
tree-sitter test --update

# Parse and highlight sample files
tree-sitter parse examples/simple.mtlog
tree-sitter highlight examples/simple.mtlog

# Debug parsing
tree-sitter parse --debug test.mtlog
tree-sitter parse --debug-graph test.mtlog
```

## Architecture

### Grammar Design Principles
1. **Single Responsibility**: Only syntax highlighting and navigation - NO validation
2. **Permissive Parsing**: Accept any template-like input for real-time typing support
3. **Performance First**: Optimized for zero-latency editor responsiveness
4. **Editor Native**: Target only editors with built-in tree-sitter support

### Key Components

#### Template Syntax Support
- Basic properties: `{UserId}`, `{Amount:F2}`
- Go template properties: `{{.Property}}`
- Built-in properties: `${Timestamp}`
- Capture hints: `@` (capture complex types), `$` (force scalar)
- Format specifiers: `:F2`, `:P1`, `:HH:mm:ss`
- Dotted names (OTEL): `{http.method}`, `{service.name}`
- Numeric indexing: `{0}`, `{1}`

#### File Structure (to be created)
- `grammar.js` - Main grammar definition
- `queries/highlights.scm` - Syntax highlighting queries
- `queries/injections.scm` - Injection into Go strings
- `queries/textobjects.scm` - Structural navigation
- `test/corpus/` - Test files for all syntax variations

#### Injection Architecture
Templates are only parsed within confirmed mtlog method calls:
- Direct calls: `logger.Info(...)`, `logger.Error(...)`
- Chained calls: `logger.With(...).Info(...)`
- Method names: Debug, Verbose, Information, Info, Warning, Warn, Error, Fatal

### Performance Targets
- Parse time (100 char): <1ms
- Parse time (1000 char): <5ms
- Injection check: <0.1ms per string
- Memory per file: <100KB
- Incremental reparse: <0.5ms

## Key Design Decisions

### Why `${...}` for Built-ins in Output Templates
mtlog uses `${...}` for built-in template elements to prevent ambiguity with user properties:
- `${Message}`, `${Timestamp}`, `${Level}` - Built-in elements
- `{UserId}`, `{OrderId}` - User properties from log events

### Grammar Conflict Resolution
Use precedence and associativity to handle ambiguous cases:
- Higher precedence for property-starting sequences
- Literal text captures everything else with right associativity

### Error Recovery Strategy
The grammar gracefully handles malformed input:
- `{UserId` → parsed as literal text
- `{}` → property with no name
- `{:F2}` → property with only format

## Testing Strategy

### Test Corpus Categories
- `syntax/` - Basic property syntaxes
- `features/` - Capturing, formatting, dotted names
- `edge_cases/` - Malformed but parseable input
- `performance/` - Large templates for benchmarking

### Test Development Process
1. Start with simple cases (single property)
2. Add complexity gradually (formats, hints)
3. Include edge cases (empty, malformed)
4. Test boundaries (start/end of string)
5. Verify error recovery

## Editor Integration Points

### Neovim
- Parser installation via nvim-treesitter
- Custom text objects: `ap` (around property), `ip` (inside property)
- Motion commands: `]p` (next property), `[p` (previous property)

### Zed
- Configuration via languages/mtlog/config.toml
- Injection via regex pattern matching

## Non-Goals (Out of Scope)

1. **Validation**: No checking if properties match arguments
2. **Format Verification**: Any string after `:` is accepted
3. **Type Checking**: No verification of capture hints
4. **Cross-Reference**: No linking between properties
5. **Diagnostics**: No error messages or warnings
6. **Quick Fixes**: No code modifications

These responsibilities belong to mtlog-analyzer, NOT this grammar.

## Maintenance Considerations

### When to Update Grammar
- New template delimiter syntax added
- New capture hint characters added
- Fundamental syntax changes (breaking)

### Before Releases
1. Run full test corpus
2. Benchmark against performance targets
3. Test in Neovim with real mtlog code
4. Test in Zed with real mtlog code
5. Verify no regressions in edge cases