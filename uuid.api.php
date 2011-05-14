<?php
/**
 * @file
 *   Hooks provided by the UUID module.
 */

/**
 * Defines one or more UUID generators exposed by a module.
 *
 * @return
 *   An associative array with the key being the machine name for the
 *   implementation and the values being an array with the following keys:
 *     - callback: The function to be called for generating the UUID.
 *     - title: The human readable name for the generator.
 *
 * @see uuid_info()
 */
function hook_uuid_info() {
  $generators = array();
  $generators['my_module'] = array(
    'callback' => 'my_module_generate_uuid',
    'title' => t('My module UUID generator'),
  );
  return $generators;
}

/**
 * Ensures all records have a UUID assigned to them.
 *
 * When called this hook should ensure all records it is responsible for
 * have a UUID and if not create one.  The uuid_sync() helper function is
 * available to make this easy to implement.
 *
 * @see uuid_sync()
 */
function hook_uuid_sync() {
  uuid_sync('my_table', 'id');
}

/**
 * Find an entity using the UUID assigned to it.
 *
 * This is not a hook, but provides a simple way to expose UUID lookups from
 * within a module.
 *
 * @param
 *   $uuid The UUID to use for the lookup.
 *
 * @return
 *   The id field value for the entity or FALSE if not found.
 *
 * @see uuid_find()
 */
function uuid_TYPE_find($uuid) {
  return uuid_find($uuid, 'my_table', 'id');
}
