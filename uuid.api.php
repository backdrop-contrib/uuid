<?php

/**
 * @file
 * Hooks provided by the UUID module.
 */

/**
 * Defines one or more UUID generators exposed by a module.
 *
 * @return
 *   An associative array with the key being the machine name for the
 *   implementation and the values being an array with the following keys:
 *     - title: The human readable name for the generator.
 *     - callback: The function to be called for generating the UUID.
 *
 * @see uuid_get_info()
 */
function hook_uuid_info() {
  $generators = array();
  $generators['my_module'] = array(
    'title' => t('My module UUID generator'),
    'callback' => 'my_module_generate_uuid',
  );
  return $generators;
}

/**
 * Ensures all records have a UUID assigned to them.
 *
 * When called this hook should ensure all records it is responsible for
 * have a UUID and if not create one.
 *
 * @see entity_uuid_sync()
 */
function hook_uuid_sync() {
  // Do what you need to do to generate missing UUIDs for you implementation.
}
