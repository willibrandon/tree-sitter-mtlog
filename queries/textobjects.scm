; Text objects for structural navigation in mtlog templates
; These enable vim-style movements and operations

; Entire property including delimiters (ap - around property)
(property) @property.outer
(go_property) @property.outer
(builtin_property) @property.outer

; Just the property name (ip - inside property)
(property name: (_) @property.inner)
(go_property name: (_) @property.inner)
(builtin_property name: (_) @property.inner)

; Format specifier (af - around format, if - inside format)
(format_spec) @format.outer
(format_spec format_string: (_) @format.inner)

; Capture hints (ah - around hint)
(property hint: (hint_symbol) @hint.outer)

; All properties in template (for bulk operations)
(template (property) @property.all)
(template (go_property) @property.all)
(template (builtin_property) @property.all)

; Properties with capture hints (both @ and $ variants)
(property hint: (hint_symbol) @property.hint)

; Properties with numeric indices
(property name: (numeric_index) @property.indexed)
(go_property name: (numeric_index) @property.indexed)

; Properties with dotted names (OTEL properties)
(property name: (dotted_name) @property.otel)
(go_property name: (dotted_name) @property.otel)
(builtin_property name: (dotted_name) @property.otel)
