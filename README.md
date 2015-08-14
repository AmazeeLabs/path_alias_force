# Path alias force

A drupal module that ensures that all not LANGUAGE_NONE aliases do exist in all languages.

Assume this module as the language fallback for path aliases.

Let's say you have a site with EN and DE languages. You created a node in EN language, and set the "pages/my-node" alias to it. While you didn't translated your node to the DE language, it's path will be "node/1" at the DE pages. This module prevent such behavior always creating aliases in all languages for any existing aliases, so URLs are always nice.

## Before installation

If you use the [Pathauto](https://www.drupal.org/project/pathauto) module, be sure to install the [Pathauto persist](https://www.drupal.org/project/pathauto_persist) module before this module installation to prevent Pathauto's settings loss.

This module also supports (by not requires) the [Language fallback](https://www.drupal.org/project/language_fallback) module, but only starting from 7.x-2.x version.

The module requires PHP >= 5.3 version.

## After installation

Aliases should be manually recreated at:

- module installation/enabling
- language settings change

The module tries to detect these events and warn user with a message. However, this is not always possible because there are no language hooks in Drupal 7.

## Hidden options

### path_alias_force_force_und

There is the "path_alias_force_force_und" option that does not present on the admin UI.

```bash
drush vset path_alias_force_force_und 1   # to enable
drush vdel path_alias_force_force_und     # to disable
# don't forget to recreate aliases after enabling/disabling
```

By default, Drupal has two strategies for creating path aliases:

1. Path can have only one Language Neutral (und) alias.
1. Path can have aliases for languages, but cannot have Language Neutral (und) alias.


By enabling this option, the module will also force the Language Neutral (und) alias on the second behavior.

That option changes the default workflow, so some unexpected things may happen. Please only enable this option if you really need to.
