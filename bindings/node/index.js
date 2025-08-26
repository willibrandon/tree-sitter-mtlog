try {
  module.exports = require('../../build/Release/tree_sitter_mtlog_binding');
} catch (error) {
  if (error.code !== 'MODULE_NOT_FOUND') {
    throw error;
  }
  module.exports = require('../../build/Debug/tree_sitter_mtlog_binding');
}