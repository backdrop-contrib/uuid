<?php

/**
 * @defgroup uuid UUID handling
 * @{
 * Functions for the UUID handling.
 */

/**
 * Generates an universally unique identifier.
 *
 * @return
 *   An UUID, made up of 32 hex digits and 4 hyphens.
 */
function uuid_generate() {
  $callback = &drupal_static(__FUNCTION__);
  if (empty($callback)) {
    $generator = variable_get('uuid_generator', 'php');
    $info = uuid_get_info();
    $callback = $info[$generator]['callback'];
  }
  return $callback();
}

/**
 * Generate all missing UUIDs.
 */
function uuid_sync_all() {
  module_invoke_all('uuid_sync');
}

/**
 * Check that a string appears to be in the format of a UUID.
 *
 * @param $uuid
 *  The string to test.
 *
 * @return
 *   TRUE if the string is well formed.
 */
function uuid_is_valid($uuid) {
  return preg_match("/^[0-9a-f]{8}-([0-9a-f]{4}-){3}[0-9a-f]{12}$/", $uuid);
}

/**
 * Fetches information about the available UUID implementations.
 */
function uuid_get_info() {
  $info = &drupal_static(__FUNCTION__);
  if (empty($info)) {
    $info = module_invoke_all('uuid_info');
  }
  return $info;
}

/**
 * Implements hook_uuid_info().
 */
function uuid_uuid_info() {
  $info = array();
  // PECL and OSSP are 2 incompatiable implementations in PHP that use the same namespace.
  if (function_exists('uuid_create') && !function_exists('uuid_make')) {
    $info['pecl'] = array(
      'title' => t('PECL Extension'),
      'callback' => 'uuid_pecl',
    );
  }
  if (Database::getConnection()->databaseType() == 'mysql') {
    $info['mysql'] = array(
      'title' => t('MySQL'),
      'callback' => 'uuid_mysql',
    );
  }
  if (function_exists('com_create_guid')) {
    $info['com'] = array(
      'title' => t('Windows COM'),
      'callback' => 'uuid_com',
    );
  }
  $info['php'] = array(
    'title' => t('PHP fallback'),
    'callback' => 'uuid_php',
  );
  return $info;
}

/**
 * @} End of "UUID handling"
 */

/**
 * @defgroup uuid_generators UUID generators
 * @{
 * Different UUID generators.
 */

/**
 * Generates a UUID using the Windows internal GUID generator.
 *
 * @see http://php.net/com_create_guid
 */
function uuid_com() {
  // Remove {} wrapper and make lower case to keep result consistent.
  return drupal_strtolower(trim(com_create_guid(), '{}'));
}

/**
 * Generates a UUID using MySQL's implementation.
 *
 * @see http://dev.mysql.com/doc/refman/5.0/en/miscellaneous-functions.html#function_uuid
 */
function uuid_mysql() {
  return db_query('SELECT UUID()')->fetchField();
}

/**
 * Generates a UUID using the PECL extension.
 *
 * @see http://pecl.php.net/package/uuid
 */
function uuid_pecl() {
  return uuid_create(UUID_TYPE_DEFAULT);
}

/**
 * Generates a UUID v4 using PHP code.
 *
 * @see http://php.net/uniqid#65879
 */
function uuid_php() {
  // The field names refer to RFC 4122 section 4.1.2.
  return sprintf('%04x%04x-%04x-%03x4-%04x-%04x%04x%04x',
    // 32 bits for "time_low".
    mt_rand(0, 65535), mt_rand(0, 65535),
    // 16 bits for "time_mid".
    mt_rand(0, 65535),
    // 12 bits before the 0100 of (version) 4 for "time_hi_and_version".
    mt_rand(0, 4095),
    bindec(substr_replace(sprintf('%016b', mt_rand(0, 65535)), '01', 6, 2)),
    // 8 bits, the last two of which (positions 6 and 7) are 01, for "clk_seq_hi_res"
    // (hence, the 2nd hex digit after the 3rd hyphen can only be 1, 5, 9 or d)
    // 8 bits for "clk_seq_low" 48 bits for "node".
    mt_rand(0, 65535), mt_rand(0, 65535), mt_rand(0, 65535)
  );
}

/**
 * @} End of "UUID generators"
 */
