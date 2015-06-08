<?php

/**
 * Admin form callback.
 */
function path_alias_force_admin_form($form, &$form_state) {
  $form['force_und'] = array(
    '#type' => 'checkbox',
    '#title' => t('Also force the Language Neutral (und) alias'),
    '#description' => t('By default, Drupal has two strategies for creating path aliases:<br/>
1. Path can have only one Language Neutral (und) alias.<br/>
2. Path can have aliases for languages, but cannot have Language Neutral (und) alias.<br/>
(By the way, this module extends the second behavior, forcing aliases for all existing languages.)<br/>
By enabling this checkbox, the module will also force the Language Neutral (und) alias on the second behavior.'),
    '#default_value' => variable_get('path_alias_force_force_und'),
  );
  $form['recreate'] = array(
    '#type' => 'submit',
    '#value' => t('Recreate all forced aliases'),
  );
  return $form;
}

/**
 * Admin form submit callback.
 */
function path_alias_force_admin_form_submit(&$form, &$form_state) {
  variable_set('path_alias_force_force_und', $form_state['values']['force_und']);
  _path_alias_force_remove_forced_aliases();
  $path_ids = db_select('url_alias', 'u')
    ->fields('u', array('pid'))
    ->condition('u.language', LANGUAGE_NONE, '<>')
    ->groupBy('u.source')
    ->execute()
    ->fetchCol();
  $operations = array();
  while($path_ids){
    $operations[] = array('_path_alias_force_batch_create_op', array(array_splice($path_ids, 0, 100)));
  }
  $batch = array(
    'title' => t('Recreating forced path aliases...'),
    'progress_message' => t('Completed @percentage%.'),
    'operations' => $operations,
  );
  batch_set($batch);
  batch_process();
}
