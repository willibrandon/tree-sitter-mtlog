; Highlights for mtlog templates
; Following tree-sitter standard capture names
; https://tree-sitter.github.io/tree-sitter/syntax-highlighting#standard-capture-names

; Punctuation - Property delimiters
(open_brace) @punctuation.bracket
(close_brace) @punctuation.bracket

; Special punctuation for Go templates
(open_go) @punctuation.special
(close_go) @punctuation.special

; Special punctuation for built-in properties
(open_builtin) @punctuation.special
(close_builtin) @punctuation.special

; Capture hints - @ for complex types, $ for scalar
(property hint: (hint_symbol) @keyword.operator)

; Property names
(property name: (identifier) @variable.parameter)
(property name: (numeric_index) @number)

; Go template properties
(go_property name: (identifier) @variable.parameter)
(go_property name: (numeric_index) @number)
(go_property "." @punctuation.delimiter)

; Built-in properties (like ${Timestamp}, ${Level})
(builtin_property name: (identifier) @constant.builtin)

; Dotted names (OTEL properties like http.method, service.name)
(property name: (dotted_name) @variable.member)
(go_property name: (dotted_name) @variable.member)
(builtin_property name: (dotted_name) @variable.member)

; Dots in dotted names
(dotted_name "." @punctuation.delimiter)

; Format specifiers
(format_spec ":" @punctuation.delimiter)
(format_spec format_string: (_) @string.special)

; Literal text (no highlighting needed, but included for completeness)
; (literal_text) @none