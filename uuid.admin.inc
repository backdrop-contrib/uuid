<?php

/**
 * @file
 * Administration functions for the uuid module.
 */

/**
 * Menu callback: options for UUID.
 */
function uuid_admin_form() {
  $form = array();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );

  $options = array();
  $generators = uuid_get_info();
  foreach ($generators as $name => $info) {
    $options[$name] = $info['title'];
  }

  $form['settings']['uuid_generator'] = array(
    '#type' => 'select',
    '#title' => t('UUID Generator'),
    '#default_value' => variable_get('uuid_generator', 'php'),
    '#description' => t('The method used to generate the UUID'),
    '#options' => $options,
  );

  $form['sync'] = array(
    '#type' => 'fieldset',
    '#title' => t('Synchronization'),
  );

  $form['sync']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create missing UUIDs'),
    '#submit' => array('uuid_admin_sync_submit'),
  );

  return system_settings_form($form);
}

/**
 * Submit handler for the UUID sync.
 */
function uuid_admin_sync_submit() {
  uuid_sync_all();
  drupal_set_message(t('Generated missing UUIDs.'));
}
