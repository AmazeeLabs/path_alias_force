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
  $sources = db_select('url_alias', 'u')
    ->fields('u', array('source'))
    ->condition('u.forced', 0)
    ->groupBy('u.source')
    ->execute()
    ->fetchCol();
  $operations = array();
  while ($sources) {
    $operations[] = array('_path_alias_force_batch_create_op', array(array_splice($sources, 0, 100)));
  }
  $batch = array(
    'title' => t('Recreating forced path aliases...'),
    'progress_message' => t('Completed @percentage%.'),
    'operations' => $operations,
  );
  batch_set($batch);
  batch_process();
}
