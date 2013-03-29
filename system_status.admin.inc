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
    '#type' => 'checkbox',
    '#title' => t('Allow public calls'),
    '#description' => t('Allow calls from ip-adresses as defined below. Please note that they should be comma separated.'),
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
    '#type' => 'checkbox',
    '#title' => t('Allow calls from DrupalStatus.org'),
    '#description' => t('Allow calls from the servers at http://www.drupalstatus.org and all of their ip ranges.'),
    '#default_value' => variable_get('system_status_service_allow_drupalstatus', '0'),
  );

  $form['system_status_need_protect_token'] = array(
    '#type' => 'checkbox',
    '#title' => t('Protect all calls using a unique token'),
    '#description' => t('Require that a code is passed to the url to view the JSON ouput. You need the following private key to open the page: @token',
      array("@token" => variable_get('system_status_token','Error-no-token'))),
    '#default_value' => variable_get('system_status_need_protect_token', 0),
    '#states' => array(
      'disabled' => array(
        ':input[name="system_status_service_allow_drupalstatus"]' => array('checked' => TRUE),
      ),
      'checked' => array(
        array(':input[name="system_status_need_protect_token"]' => array('checked' => TRUE)),
        array(':input[name="system_status_service_allow_drupalstatus"]' => array('checked' => TRUE)),
      ),
     ),
  );

  $form['system_status_need_encryption'] = array(
    '#type' => 'checkbox',
    '#title' => t('Protect all calls using encryption'),
    '#description' => t('Selecting this option will encrypt all output, rendering the data useless for hackers during a man-in-the-middle attack. You need the following private key to decode the message: @encrypt_token ',
      array("@encrypt_token" => variable_get("system_status_encrypt_token", 'Error-no-token'))),
    '#default_value' => variable_get('system_status_need_encryption', 0),
    '#states' => array(
      'disabled' => array(
        ':input[name="system_status_service_allow_drupalstatus"]' => array('checked' => TRUE),
      ),
      'checked' => array(
        array(':input[name="system_status_need_encryption"]' => array('checked' => TRUE)),
        array(':input[name="system_status_service_allow_drupalstatus"]' => array('checked' => TRUE)),
      ),
     ),
  );

  $form['system_status_do_match_core'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable core modules'),
    '#description' => t('Scan for core modules.'),
    '#default_value' => variable_get('system_status_do_match_core', '1'),
  );

  $form['system_status_do_match_contrib'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable contrib modules'),
    '#description' => t('Scan for contrib modules.'),
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
