This module is a minimum port of the Drupal module, intended just to allow
Node Export to work.


UUID
===========

This module provides an API for adding universally unique identifiers (UUID) to
Drupal objects, most notably entities.

FEATURES
--------

 * Automatic UUID generation:
   UUIDs will be generated for all core entities. An API is provided for other
   modules to enable support for custom entities.
 * UUID API for entities, properties and fields:
   With this unified API you can load entities with entity_uuid_load() so that
   all supported properties and fields are made with UUID references. You can
   also save entities formatted this way with entity_uuid_save() (depends on
   Entity API).
 * Export entities to use as default/demo content:



Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules

- Visit admin/build/modules to enable the Node export module in the Node export
   package.


License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainers
-------------------

- Luke McCormick (https://github.com/cellear/)

Credits
-------

This module is based on the Drupal module Node UUID

Project page: https://www.drupal.org/project/uuid.

Drupal Maintainer: Dave Hall (skwashd) (https://www.drupal.org/u/skwashd)
