<?php

/**
 * @file
 * Implementation of UUID hooks for all core modules.
 */

/**
 * Implements hook_entity_load_by_uuid().
 */
function user_entity_load_by_uuid(&$entities, $entity_type) {
  foreach ($entities as $entity) {
    // Deal with user properties on different entities.
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
 * Implements hook_entity_load_by_uuid().
 */
function node_entity_load_by_uuid(&$entities, $entity_type) {
  foreach ($entities as $entity) {
    switch ($entity_type) {
      // Deal with node properties on different entities.
      case 'node':
        $uuids = entity_get_uuid_by_id('node', array($entity->tnid));
        $entity->tnid = $uuids[$entity->tnid];
        break;
    }
  }
}

/**
 * Implements hook_entity_load_by_uuid().
 */
function comment_entity_load_by_uuid(&$entities, $entity_type) {
  foreach ($entities as $entity) {
    switch ($entity_type) {
      // Deal with properties on different entities.
      case 'comment':
        $uuids = entity_get_uuid_by_id('node', array($entity->nid));
        $entity->nid = $uuids[$entity->nid];
        break;
    }
  }
}
