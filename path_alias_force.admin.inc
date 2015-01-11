<?php

/**
 * Admin form callback.
 */
function path_alias_force_admin_form($form, &$form_state) {
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
