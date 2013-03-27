<?php
/**
 * @file
 * Admin forms for system_status 
 */

/**
 * Page callback: System settings settings.
 *
 * @see system_status_menu()
 */
function system_status_form($form, &$form_state) {

  $form['system_status_public_allow_public'] = array(
    '#description' => t('Allow calls from ip-adresses as defined below. Please note that they should be comma separated.'),
    '#type' => 'checkbox',
    '#title' => t('Allow public calls'),
    '#default_value' => variable_get('system_status_public_allow_public', '1'),
  );

  $form['system_status_public_allow_ips'] = array(
    '#type' => 'textfield',
    '#title' => t('Comma seperated list of allowed IP addresses'),
    '#default_value' => variable_get('system_status_public_allow_ips', '127.0.0.1,::1'),
    '#states' => array(
      'visible' => array(
        ':input[name="system_status_public_allow_public"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['system_status_service_allow_drupalstatus'] = array(
    '#description' => t('Allow calls from the servers at http://www.drupalstatus.org and all of their ip ranges.'),
    '#type' => 'checkbox',
    '#title' => t('Allow calls from DrupalStatus.org'),
    '#default_value' => variable_get('system_status_service_allow_drupalstatus', '0'),
  );

  $form['system_status_do_match_core'] = array(
    '#description' => t('Scan for core modules.'),
    '#type' => 'checkbox',
    '#title' => t('Enable core modules'),
    '#default_value' => variable_get('system_status_do_match_core', '1'),
  );

  $form['system_status_do_match_contrib'] = array(
    '#description' => t('Scan for contrib modules.'),
    '#type' => 'checkbox',
    '#title' => t('Enable contrib modules'),
    '#default_value' => variable_get('system_status_do_match_contrib', '1'),
  );

  $form['system_status_match_contrib_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Where are your contrib modules stored ?'),
    '#default_value' => variable_get('system_status_match_contrib_mode', 0),
    '#options' => array(
      0 => 'sites/*/modules/',
      1 => 'sites/*/modules/contrib/',
      2 => 'Other'),
    '#states' => array(
      'visible' => array(
        ':input[name="system_status_do_match_contrib"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['system_status_preg_match_contrib'] = array(
    '#type' => 'textfield',
    '#title' => t('Regular expression to match contrib modules'),
    '#default_value' => variable_get('system_status_preg_match_contrib', '{^sites\/([A-z,\.,\-]+)\/modules\/contrib\/*}'),
    '#states' => array(
      'visible' => array(
        ':input[name="system_status_match_contrib_mode"]' => array('value' => 2),
      ),
    ),
  );

  $form['system_status_do_match_custom'] = array(
    '#description' => t('Scan for custom modules using a regular expression.'),
    '#type' => 'checkbox',
    '#title' => t('Enable custom modules'),
    '#default_value' => variable_get('system_status_do_match_custom', '0'),
    '#states' => array(
      'visible' => array(
        ':input[name="system_status_match_contrib_mode"]' => array('value' => 2),
      ),
    ),
  );

  $form['system_status_preg_match_custom'] = array(
    '#type' => 'textfield',
    '#title' => t('Regular expression to match custom modules'),
    '#default_value' => variable_get('system_status_preg_match_custom', '{^sites\/([A-z,\.,\-]+)\/modules\/custom\/*}'),
    '#states' => array(
      'visible' => array(
        ':input[name="system_status_do_match_custom"]' => array('visible' => TRUE),
      ),
    ),
  );

  return system_settings_form($form);
}
