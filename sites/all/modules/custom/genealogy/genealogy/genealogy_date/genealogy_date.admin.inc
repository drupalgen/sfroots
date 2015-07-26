<?php
/**
 * @file
 * The administrative interface for the genealogy date field
 */

/**
 * Page callback for 'admin/config/genealogy/date'
 */
function genealogy_date_admin_settings($form, &$form_state) {
  $form['date_order'] = array(
    '#type' => 'select',
    '#title' => t('Set Order of Date components'),
    '#options' => array('0' => t('DD MMM YYYY'), '1' => t('MMM DD YYYY')),
    '#default_value' => variable_get('genealogy_date_date_order', '0'),
    '#description' => t('Order that components of a date should be entered.  Defaults to DD MMM YYYY.'),
  );
  
  $form['before_acronyms'] = array(
    '#type' => 'textarea',
    '#title' => t('Set "Before" acronyms'),
    '#default_value' => _genealogy_date_admin_settings_get_before_acronyms($form_state),
    '#description' => t('Set Acronyms and words that are acceptable to use for "Before" (Default is "BEF") when specifying a date such as "Bef 1890"')
  );

  $form['after_acronyms'] = array(
    '#type' => 'textarea',
    '#title' => t('Set "After" acronyms'),
    '#default_value' => _genealogy_date_admin_settings_get_after_acronyms($form_state),
    '#description' => t('Set Acronyms and words that are acceptable to use for "After" (Default is "AFT") when specifying a date such as "Aft 1890"')
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('genealogy_date_admin_settings_submit'),
    '#validate' => array('genealogy_date_admin_settings_validate'),
  );

  return $form;
}

function genealogy_date_admin_settings_validate($form, &$form_state) {
  dsm($form);
  dsm($form_state);
}


function genealogy_date_admin_settings_submit($form, &$form_state) {
  variable_set('genealogy_date_date_order', $form_state['values']['date_order']);

  $before_acronyms = explode("\n", $form_state['values']['before_acronyms']);
  foreach ($before_acronyms as $before_acronym) {
    if(strlen(trim($before_acronym)) > 0) {
      $bef[] = trim($before_acronym);
    }
  }
  variable_set('genealogy_date_before_acronyms', $bef);

  $after_acronyms = explode("\n", $form_state['values']['after_acronyms']);
  foreach ($after_acronyms as $after_acronym) {
    if(strlen(trim($after_acronym)) > 0) {
      $aft[] = trim($after_acronym);
    }
  }
  variable_set('genealogy_date_after_acronyms', $aft);
}

function _genealogy_date_admin_settings_get_before_acronyms($form_state) {
  return _genealogy_date_admin_settings_get_acronyms($form_state, 'before');
}

function _genealogy_date_admin_settings_get_after_acronyms($form_state) {
  return _genealogy_date_admin_settings_get_acronyms($form_state, 'after');
}

function _genealogy_date_admin_settings_get_acronyms($acronyms, $set) {
  $output = NULL;
  if(isset($form_state['values']) && isset($form_state['values'][$set . '_acronyms'])) {
    return $form_state['values'][$set . '_acronyms'];
  }
  else {
    $default_acronyms = variable_get('genealogy_date_' . $set . '_acronyms', NULL);
    foreach ($default_acronyms as $default_acronym) {
      $output .= $default_acronym . "\n";
    }
  }
  return $output;
}
?>