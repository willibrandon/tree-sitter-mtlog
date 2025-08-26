# tree-sitter-mtlog

Tree-sitter grammar for [mtlog](https://github.com/willibrandon/mtlog) message templates, providing syntax highlighting and structural navigation for editors with native tree-sitter support.

## Features

- 🎨 **Syntax Highlighting** - Distinguishes properties, literals, and format specifiers
- 🚀 **Zero-latency** - Native tree-sitter performance (<1ms for typical templates)
- 🎯 **Smart Navigation** - Structural text objects for properties and formats
- 🔍 **Template Types** - Supports `{Property}`, `{{.GoTemplate}}`, `${Builtin}`
- 📝 **Format Specifiers** - Recognizes `:F2`, `:yyyy-MM-dd`, etc.
- 🏷️ **Capture Hints** - `@` for complex types, `$` for scalars
- 🌐 **OTEL Properties** - Dotted names like `{http.method}`

## Installation

### Neovim

Using [nvim-treesitter](https://github.com/nvim-treesitter/nvim-treesitter):

```lua
-- Add to your treesitter config
require'nvim-treesitter.configs'.setup {
  ensure_installed = { "mtlog", "go" },
  highlight = { enable = true },
  textobjects = {
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
}
```

### Zed

Add to your `languages.toml`:

```toml
[[languages]]
name = "mtlog"
scope = "source.mtlog"
injection-regex = "mtlog"
file-types = []

[[grammars]]
name = "mtlog"
source = { git = "https://github.com/willibrandon/tree-sitter-mtlog" }
```

### Helix

Install via the runtime directory:

```bash
hx --grammar fetch mtlog
hx --grammar build mtlog
```

## Template Syntax

### Basic Properties
```go
logger.Info("User {UserId} logged in")
logger.Error("Failed to process {Count} items")
```

### Format Specifiers
```go
logger.Info("Price: {Amount:F2} USD")
logger.Info("Date: {Timestamp:yyyy-MM-dd HH:mm:ss}")
```

### Capture Hints
```go
logger.Info("Order {@Order} created")     // @ = capture complex type
logger.Info("Error: {$Error}")            // $ = force scalar
```

### Go Templates
```go
logger.Info("User {{.UserId}} from {{.Location}}")
```

### Built-in Properties
```go
formatter.Format("${Timestamp} [${Level}] ${Message}")
```

### OTEL Properties
```go
logger.Info("HTTP {http.method} to {http.url} returned {http.status_code}")
```

## Development

### Setup
```bash
npm install
npm run build
```

### Testing
```bash
npm test                    # Run all tests
npm run test:update        # Update test expectations
npm run parse <file>       # Parse a file
npm run highlight <file>   # Test highlighting

# Test highlight samples
npx tree-sitter parse test/highlight/*.mtlog
```

### Benchmarking
```bash
npm run benchmark          # Show parsing speed from test suite
```


## Design Philosophy

This grammar focuses exclusively on **syntax highlighting and navigation**. It deliberately excludes:

- ❌ Validation (handled by [mtlog-analyzer](https://github.com/willibrandon/mtlog/tree/main/cmd/mtlog-analyzer))
- ❌ Type checking
- ❌ Cross-references
- ❌ Diagnostics

The grammar is **permissive by design**, accepting malformed templates to maintain highlighting during active typing.

## Performance

The parser is optimized for zero-latency editor responsiveness:

| Metric | Target | Actual | Result |
|--------|---------|---------|--------|
| Average parsing speed | >100 bytes/ms | **6779 bytes/ms** | ✅ 67x faster |
| 100-char template | <1ms | **0.015ms** | ✅ 67x faster |
| 1000-char template | <5ms | **0.15ms** | ✅ 33x faster |
| Test suite | 100% pass | **24/24** | ✅ All passing |

## Contributing

Contributions are welcome! Please ensure:

1. All tests pass: `npm test`
2. Performance benchmarks are maintained
3. Changes align with the single-responsibility principle (syntax only)

## License

[MIT](./LICENSE)

## Related Projects

- [mtlog](https://github.com/willibrandon/mtlog) - High-performance structured logging library