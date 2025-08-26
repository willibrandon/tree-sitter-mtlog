module.exports = grammar({
  name: 'mtlog',

  // No conflicts needed - we handle ambiguity with precedence
  conflicts: $ => [],

  // Rules to inline for performance
  inline: $ => [
    $._element,
    $._property_name
  ],

  rules: {
    // Entry point - a template is a sequence of elements
    template: $ => repeat($._element),

    // An element can be literal text or any type of property
    _element: $ => choice(
      $.literal_text,
      prec(2, $.property),
      prec(2, $.go_property),
      prec(2, $.builtin_property)
    ),

    // Basic property: {Name} or {@Name} or {$Name} or {Name:Format}
    property: $ => seq(
      '{',
      field('hint', optional(choice('@', '$'))),
      field('name', $._property_name),
      field('format', optional($.format_spec)),
      '}'
    ),

    // Go template property: {{.Name}} or {{Name}}
    go_property: $ => seq(
      '{{',
      optional('.'),
      field('name', $._property_name),
      '}}'
    ),

    // Built-in property: ${Name} or ${Name:Format}
    builtin_property: $ => seq(
      '${',
      field('name', $._property_name),
      field('format', optional($.format_spec)),
      '}'
    ),

    // Property name can be identifier, dotted name, or numeric index
    _property_name: $ => choice(
      $.identifier,
      $.dotted_name,
      $.numeric_index
    ),

    // Simple identifier: letters, digits, underscore
    identifier: $ => /[A-Za-z_][A-Za-z0-9_]*/,

    // Dotted name for OTEL properties: http.method, service.name
    dotted_name: $ => seq(
      $.identifier,
      repeat1(seq('.', $.identifier))
    ),

    // Numeric index for positional properties: {0}, {1}
    numeric_index: $ => /[0-9]+/,

    // Format specifier: :F2, :HH:mm:ss, :P1, etc
    format_spec: $ => seq(
      ':',
      field('format_string', token(prec(-1, /[^}]+/)))
    ),

    // Literal text - anything that's not a property
    // Uses right associativity to consume as much as possible
    literal_text: $ => prec.right(repeat1(
      choice(
        // Match bulk text that doesn't contain property delimiters
        /[^{$}]+/,
        // Match lone $ or } that don't form properties
        /[$}]/,
        // Match { followed by something that doesn't start a property
        // This handles cases like "{ " or "{x" where x is not valid property start
        seq('{', 
          token.immediate(prec(1, /[^{@$A-Za-z0-9_]/))),
        // Match ${ followed by } (empty builtin property becomes literal)
        seq('$', token.immediate('{')),
        // Match {{ not followed by valid go template content
        seq('{', token.immediate('{'), 
          token.immediate(prec(1, /[^.A-Za-z_]/)))
      )
    ))
  }
});