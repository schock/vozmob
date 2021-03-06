<?php
// $Id$

/**
 * Render SMS Registration settings form.
 */
function sms_registration_settings() {
  $form['sms_registration_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Registration address'),
    '#description' => t('Enter the e-mail address used to receive site registrations.'),
    '#default_value' => variable_get('sms_registration_address', ''),
  );
  $form['sms_registration_username'] = array(
    '#type' => 'textfield',
    '#title' => t('User name prefix'),
    '#description' => t('Enter a user name prefix on randomly generated user names.'),
    '#default_value' => variable_get('sms_registration_username', 'Drupal-'),
  );
  $form['sms_registration_role'] = array(
    '#type' => 'select',
    '#title' => t('Default role'),
    '#description' => t('Select a default role granted to users registering via SMS.'),
    '#options' => user_roles(TRUE),
    '#default_value' => variable_get('sms_registration_role', NULL),
  );
  return system_settings_form($form);
}
