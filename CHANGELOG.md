# Changelog

All notable changes to tree-sitter-mtlog will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.0] - 2025-08-26

### Added
- Initial release of tree-sitter-mtlog parser
- Complete grammar for mtlog message template syntax
- External scanner for context-aware literal text parsing
- Support for all property types:
  - Basic properties: `{Name}`, `{Name:Format}`
  - Go template properties: `{{.Name}}`
  - Built-in properties: `${Name}`
  - Capture hints: `@` and `$`
  - Dotted OTEL names: `{http.method}`
  - Numeric indices: `{0}`, `{1}`
- Syntax highlighting queries (highlights.scm)
- Text object queries for structural navigation (textobjects.scm)
- Comprehensive test suite with 24 tests (100% passing)
- GitHub Actions CI/CD pipeline
- Performance: 9354 bytes/ms average parsing speed
- Full documentation (README.md, LICENSE, CLAUDE.md)
- Node.js bindings for npm distribution

### Performance
- 100 character templates parse in ~0.01ms (target was <1ms)
- 1000 character templates parse in ~0.11ms (target was <5ms)
- 93x faster than 100-char target
- 46x faster than 1000-char target

[Unreleased]: https://github.com/willibrandon/tree-sitter-mtlog/compare/v0.1.0...HEAD
[0.1.0]: https://github.com/willibrandon/tree-sitter-mtlog/releases/tag/v0.1.0