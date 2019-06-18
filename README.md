This module provides an API for adding universally unique identifiers (UUID) to
Backdrop objects, most notably entities.

FEATURES
--------

* Automatic UUID generation:
  UUIDs will be generated for all core entities. An API is provided for other
  modules, to enable support for custom entities.
  See https://www.drupal.org/node/2387671
* UUID API for entities, properties and fields:
  With this unified API you can load entities with `entity_uuid_load()`, so that
  all supported properties and fields are made with UUID references. You can
  also save entities formatted this way with `entity_uuid_save()` (depends on
  Entity API).
<!--- Commented out, till this applies to Backdrop:
      - no Features module, because we have Configuration Management instead.
      - Deploy module not ported to Backdrop yet.

* Export entities to use as default/demo content:
  The integration with Features module provides the ability to export UUID
  enabled entities with intact dependencies and references to other entities.
  This functionality depends on the Deploy module and is probably the most
  robust way for installation profiles and distributions to provide demo
  content.
--->
* Services integration:
  The integration with the
  [Services module](https://github.com/backdrop-contrib/services) alters all
  UUID enabled entity resources (nodes, users, taxonomies etc) to be based on
  UUIDs instead. This way it becomes easier to share and integrate content
  between sites. This functionality is used by the Deploy module.
* More integrations:
  The UUID module integrates with Views (in Backdrop CMS core), Token (also in
  core), [Rules](https://github.com/backdrop-contrib/rules), and provides some
  [CTools](https://github.com/backdrop-contrib/ctools) plugins.

<!--- Commented out, till these modules get ported over to Backdrop.

UUID extension modules include:

- [UUID Extras](https://www.drupal.org/project/uuid_extras): adds UUID support
  to the top 100 contrib modules.
- [UUID Link](http://drupal.org/project/uuid_link): embed links to entities
  using UUID so links work across environments.
- [UUID Entity Autocomplete](http://drupal.org/project/uuid_entity_autocomplete):
  Autocomplete lookup for entities that returns UUID.
- [Context UUID](http://drupal.org/project/context_uuid): Context condition
  using UUIDs.
--->

Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules

Important
---------

There is currently no direct upgrade path from Drupal 6. See the UPGRADE.txt
file in this directory for details.

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainers
-------------------

- [Luke McCormick](https://github.com/cellear) (@cellear)
- [Greg Netsas](https://github.com/klonos) (@klonos)

Credits
-------

This module is based on the Drupal module
[Universally Unique IDentifier](https://www.drupal.org/project/uuid).

Drupal Maintainers:
- [Dave Hall]((https://www.drupal.org/u/skwashd)) / @skwashd
- [Dick Olsson (dixon_)](https://www.drupal.org/u/dixon_) / @dickolsson
- [Henrique Recidive (recidive)](https://www.drupal.org/u/recidive) / @recidive

Supporting organizations:
- [Drupal Deploy](https://www.drupal.org/drupal-deploy): Drupal 7 port and
  maintenance
- [Dave Hall Consulting](https://www.drupal.org/dave-hall-consulting): Drupal 7
  port and maintenance
- [Four Kitchens](https://www.drupal.org/four-kitchens): Contributed to Drupal 7
  port
