<?php

/**
 * @file
 * Functions to check sites for security updates
 */

/**
 * Implementation of hook_drush_command().
 *
 * @return $items associative array describing your command(s).
 */
function checksecurity_drush_command() {
  $items = array();

  // The 'check-security-updates' command
  $items['check-security-updates'] = array(
   'description' => "Checks for available security updates.",
    'examples' => array(
      'drush csu' => 'Check the site for available security updates.',
    ),
    'aliases' => array('csu'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function checksecurity_drush_help($section) {
  switch ($section) {
    case 'drush:check-security-updates':
      return dt("This command will check your site for available security updates.");
    // The 'title' meta item is used to name a group of
    // commands in `drush help`.  If a title is not defined,
    // the default is "All commands in ___", with the
    // specific name of the commandfile (e.g. sandwich).
    // Command files with less than four commands will
    // be placed in the "Other commands" section, _unless_
    // they define a title.  It is therefore preferable
    // to not define a title unless the file defines a lot
    // of commands.
    case 'meta:checksecurity:title':
      return dt("Check Security commands");
    // The 'summary' meta item is displayed in `drush help --filter`,
    // and is used to give a general idea what the commands in this
    // command file do, and what they have in common.
    case 'meta:checksecurity:summary':
      return dt("Checks for available security updates.");
  }
}

/**
 * Drush command callback
 *
 *
 * @see drush_invoke()
 * @see drush.api.php
 */
function drush_checksecurity_check_security_updates() {
  $site_list = sitealias_sitealias_print_complete();
  $sites = $site_list['values'];
  foreach ($sites as $site) {
    if ($site == '@none' || $site == '@self') {
      continue;
    }
    drush_print("Checking: " . $site);
    // commandline options for update-code command
    $options = array('--pipe','--security-only');
    $result_record = drush_invoke_process($site, 'pm-updatecode', $options);
    if($result_record) {
      drush_print($result_record['output']);
    }
  }
}
