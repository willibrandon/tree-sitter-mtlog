module.exports = grammar({
  name: 'mtlog',

  externals: $ => [$.literal_text],
  // Treat newlines as whitespace (not part of literal_text), but keep all other
  // characters under control of the external scanner so spaces remain in
  // literal_text where expected.
  extras: $ => [token(/\r?\n/)],

  rules: {
    template: $ => repeat($._template_content),

    _template_content: $ => choice(
      $.go_property,
      $.builtin_property,
      $.property,
      $.literal_text
    ),

    property: $ => seq(
      '{',
      optional(field('hint', $.hint_symbol)),
      optional(field('name', $._property_name)),
      optional(field('format', $.format_spec)),
      '}'
    ),

    // Go template property: require closing '}}'; rely on recovery when unclosed
    go_property: $ => seq(
      '{{',
      optional('.'),
      optional(field('name', $._property_name)),
      '}}'
    ),

    // Keep builtin properties strict (require closing '}')
    builtin_property: $ => seq(
      '${',
      optional(field('name', $._property_name)),
      optional(field('format', $.format_spec)),
      '}'
    ),

    // Hint as named aliases to literal values so fields print as strings
    // Named wrapper for hint to make queries possible; prints as (hint_symbol)
    hint_symbol: $ => choice('@', '$'),

    _property_name: $ => choice($.identifier, $.dotted_name, $.numeric_index),

    identifier: $ => /[A-Za-z_][A-Za-z0-9_]*/,
    dotted_name: $ => seq($.identifier, repeat1(seq('.', $.identifier))),
    numeric_index: $ => /[0-9]+/,

    // Make the whole format string a single token, exposed as (identifier)
    format_spec: $ => seq(
      ':',
      field('format_string', alias(token(/[^}]+/), $.identifier))
    ),
  },
});
