<?php

/**
 * @file
 * Create form to store, update value.
 */

 /**
  * callback function to render form.
  */
function custom_form_with_db_table_form($form, &$form_state, $argument) {

  $data = array();
  if (is_numeric($argument)) {
    $data = custom_form_with_db_table_fetch($argument);
  }
  
  if ($argument == 'new' || !empty($data)) {
    $form['name'] =  array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => !empty($data['name']) ? $data['name'] : '',
      '#size' => 60,
      '#maxlength' => 60,
      '#required' => TRUE,
    );
    $form['email_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#default_value' => !empty($data['email_id']) ? $data['email_id'] : '',
      '#size' => 60,
      '#maxlength' => 60,
      '#required' => TRUE,
    );
    $form['phone_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone Number'),
      '#default_value' => !empty($data['phone_number']) ? $data['phone_number'] : '',
      '#size' => 60,
      '#maxlength' => 30,
      '#required' => TRUE,
    );
    $form['address'] = array(
      '#type' => 'textarea',
      '#title' => t('Address'),
      '#default_value' => !empty($data['address']) ? $data['address'] : '',
      '#maxlength' => 250,
      '#required' => TRUE,
    );
    $form['gender'] = array(
      '#type' => 'select',
      '#title' => t('Gender'),
      '#options' => array(
        'male' => t('Male'),
        'female' => t('Female'),
        'other' => t('other'),
      ),
      '#default_value' => !empty($data['gender']) ? $data['gender'] : '',
    );
    if ($argument == 'new') {
      $form['save'] = array(
        '#type' => 'submit', 
        '#value' => t('Save')
      );
    }
    else if (!empty($data)) {
      $form['id'] = array(
        '#type' => 'hidden',
        '#value' => $argument,
      );
      $form['update'] = array(
        '#type' => 'submit', 
        '#value' => t('Update')
      );
    }
  }
  return $form;
}

/**
 * Validate function for custom_form_with_db_table_form.
 */
function custom_form_with_db_table_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['op'] ==  'Save' || $values['op'] ==  'Update') {
    if (!valid_email_address($values['email_id'])) {
       form_set_error('email_id', t('The email address appears to be invalid.'));
    }
  }
}

/**
 * Submit function for custom_form_with_db_table_form.
 */
function custom_form_with_db_table_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['op'] ==  'Save' || $values['op'] = 'Update') {
    $fields = array();
    $fields['name'] = isset($values['name']) ? $values['name'] : '';
    $fields['email_id'] = isset($values['email_id']) ? $values['email_id'] : '';
    $fields['phone_number'] = isset($values['phone_number']) ? $values['phone_number'] : '';
    $fields['address'] = isset($values['address']) ? $values['address'] : '';
    $fields['gender'] = isset($values['gender']) ? $values['gender'] : '';
    if ($values['op'] ==  'Save') {
      // insert into table
      custom_form_with_db_table_insert($fields);
    }
    else if ($values['op'] = 'Update') {
      // update into table
      $id = isset($values['id']) ? $values['id'] : '';
      custom_form_with_db_table_update($fields, $id);
    }
  }
}
