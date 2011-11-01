<?php
/**
 * @file
 * uuid_services_example.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function uuid_services_example_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass;
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'uuid_services_example';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'api';
  $endpoint->authentication = array();
  $endpoint->server_settings = '';
  $endpoint->resources = array(
    'uuid_entity' => array(
      'operations' => array(
        'update' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 1;
  $export['uuid_services_example'] = $endpoint;

  return $export;
}
