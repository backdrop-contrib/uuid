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
 * Implements hook_entity_load_by_uuid().
 */
function node_entity_load_by_uuid(&$entities, $entity_type) {
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
 * Implements hook_entity_load_by_uuid().
 */
function comment_entity_load_by_uuid(&$entities, $entity_type) {
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
 * Implements hook_entity_presave_by_uuid().
 */
function user_entity_presave_by_uuid(&$entity, $entity_type) {
  // Transform all UUID properties to local IDs, if they exist.
  switch ($entity_type) {
    case 'node':
      $ids = entity_get_id_by_uuid('user', array($entity->uid, $entity->revision_uid));
      $entity->uid = $ids[$entity->uid];
      $entity->revision_uid = $ids[$entity->revision_uid];
      break;

    case 'comment':
      $ids = entity_get_id_by_uuid('user', array($entity->uid, $entity->u_uid));
      $entity->uid = $ids[$entity->uid];
      $entity->u_uid = $ids[$entity->u_uid];
      break;

    case 'file':
      $uuids = entity_get_id_by_uuid('user', array($entity->uid));
      $entity->uid = $ids[$entity->uid];
      break;
  }
}

/**
 * Implements hook_entity_presave_by_uuid().
 */
function node_entity_presave_by_uuid(&$entity, $entity_type) {
  // Transform all UUID properties to local IDs, if they exist.
  switch ($entity_type) {
    case 'node':
      $ids = entity_get_id_by_uuid('node', array($entity->tnid));
      $entity->tnid = $ids[$entity->tnid];
      break;
  }
}

/**
 * Implements hook_entity_presave_by_uuid().
 */
function comment_entity_presave_by_uuid(&$entity, $entity_type) {
  // Transform all UUID properties to local IDs, if they exist.
  switch ($entity_type) {
    case 'node':
      $ids = entity_get_id_by_uuid('user', array($entity->last_comment_uid));
      $entity->last_comment_uid = $ids[$entity->last_comment_uid];
      break;

    case 'comment':
      $ids = entity_get_id_by_uuid('node', array($entity->nid));
      $entity->nid = $ids[$entity->nid];
      break;
  }
}
