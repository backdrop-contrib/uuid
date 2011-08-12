<?php

/**
 * @file
 * Implementation of UUID hooks for all core modules.
 */

/**
 * Implements hook_entity_uuid_load().
 */
function user_entity_uuid_load(&$entities, $entity_type) {
  foreach ($entities as $entity) {
    // Transform all local ID properties to UUIDs.
    switch ($entity_type) {
      case 'node':
        $uuids = entity_get_uuid_by_id('user', array($entity->uid, $entity->revision_uid));
        $entity->uid = $uuids[$entity->uid];
        $entity->revision_uid = $uuids[$entity->revision_uid];
        break;

      case 'comment':
        $uuids = entity_get_uuid_by_id('user', array($entity->uid, $entity->u_uid));
        $entity->uid = $uuids[$entity->uid];
        $entity->u_uid = $uuids[$entity->u_uid];
        break;

      case 'file':
        $uuids = entity_get_uuid_by_id('user', array($entity->uid));
        $entity->uid = $uuids[$entity->uid];
        break;
    }
  }
}

/**
 * Implements hook_entity_uuid_load().
 */
function node_entity_uuid_load(&$entities, $entity_type) {
  foreach ($entities as $entity) {
    // Transform all local ID properties to UUIDs.
    switch ($entity_type) {
      case 'node':
        if (!empty($entity->tnid)) {
          $uuids = entity_get_uuid_by_id('node', array($entity->tnid));
          $entity->tnid = $uuids[$entity->tnid];
        }
        break;
    }
  }
}

/**
 * Implements hook_entity_uuid_load().
 */
function comment_entity_uuid_load(&$entities, $entity_type) {
  foreach ($entities as $entity) {
    // Transform all local ID properties to UUIDs.
    switch ($entity_type) {
      case 'node':
        $uuids = entity_get_uuid_by_id('user', array($entity->last_comment_uid));
        $entity->last_comment_uid = $uuids[$entity->last_comment_uid];
        break;

      case 'comment':
        $uuids = entity_get_uuid_by_id('node', array($entity->nid));
        $entity->nid = $uuids[$entity->nid];
        break;
    }
  }
}

/**
 * Implements hook_entity_uuid_load().
 */
function field_entity_uuid_load(&$entities, $entity_type) {
  foreach ($entities as $i => $entity) {
    list(,, $bundle_name) = entity_extract_ids($entity_type, $entity);
    $instances = field_info_instances($entity_type, $bundle_name);

    foreach ($instances as $field_name => $instance) {
      $field = field_info_field($field_name);
      foreach ($entity->{$field_name} as $langcode => &$items) {
        // Invoke 'hook_field_uuid_load'. We can't use module_invoke() since
        // that is not passing by reference.
        $function = $field['module'] . '_field_uuid_load';
        if (function_exists($function)) {
          $function($entity_type, $entity, $field, $instance, $langcode, $entities[$i]->{$field_name}[$langcode]);
        }
      }
    }
  }
}

/**
 * Implements hook_field_uuid_load().
 */
function taxonomy_field_uuid_load($entity_type, $entity, $field, $instance, $langcode, &$items) {
  foreach ($items as $i => $item) {
    $items[$i]['tid'] = reset(entity_get_uuid_by_id($entity_type, array($item['tid'])));
  }
}

/**
 * Implements hook_entity_uuid_presave().
 */
function user_entity_uuid_presave(&$entity, $entity_type) {
  // Transform all UUID properties to local IDs, if they exist. Otherwise try
  // sane defaults.
  switch ($entity_type) {
    case 'node':
      $ids = entity_get_id_by_uuid('user', array($entity->uid, $entity->revision_uid));
      if (!isset($ids[$entity->uid])) {
         throw new Exception(t("Node entity can't be saved without existing user reference."));
      }
      $entity->uid = $ids[$entity->uid];
      $entity->revision_uid = isset($ids[$entity->revision_uid]) ? $ids[$entity->revision_uid] : $ids[$entity->uid];
      break;

    case 'comment':
      $ids = entity_get_id_by_uuid('user', array($entity->uid, $entity->u_uid));
      if (!isset($ids[$entity->uid])) {
         throw new Exception(t("Comment entity can't be saved without existing user reference."));
      }
      $entity->uid = $ids[$entity->uid];
      $entity->u_uid = isset($ids[$entity->u_uid]) ? $ids[$entity->u_uid] : $ids[$entity->uid];
      break;

    case 'file':
      $ids = entity_get_id_by_uuid('user', array($entity->uid));
      if (!isset($ids[$entity->uid])) {
         throw new Exception(t("File entity can't be saved without existing user reference."));
      }
      $entity->uid = $ids[$entity->uid];
      break;
  }
}

/**
 * Implements hook_entity_uuid_presave().
 */
function node_entity_uuid_presave(&$entity, $entity_type) {
  // Transform all UUID properties to local IDs, if they exist.
  switch ($entity_type) {
    case 'node':
      $ids = entity_get_id_by_uuid('node', array($entity->tnid));
      $entity->tnid = isset($ids[$entity->tnid]) ? $ids[$entity->tnid] : NULL;
      break;
  }
}

/**
 * Implements hook_entity_uuid_presave().
 */
function comment_entity_uuid_presave(&$entity, $entity_type) {
  // Transform all UUID properties to local IDs, if they exist.
  switch ($entity_type) {
    case 'node':
      $ids = entity_get_id_by_uuid('user', array($entity->last_comment_uid));
      $entity->last_comment_uid = isset($ids[$entity->last_comment_uid]) ? $ids[$entity->last_comment_uid] : 0;
      break;

    case 'comment':
      $ids = entity_get_id_by_uuid('node', array($entity->nid));
      if (!isset($ids[$entity->nid])) {
        throw new Exception(t("Comment entity can't be saved without existing node reference."));
      }
      $entity->nid = $ids[$entity->nid];
      break;
  }
}
