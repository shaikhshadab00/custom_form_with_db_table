<?php

/**
 * @file
 * Create Dasshbord for data entries.
 */

 function custom_form_with_db_table_dashboard_form () {
    $header = array(
        array('data' => t('ID'), 'field' => 'id', 'sort' => 'desc'),
        array('data' => t('Name'), 'field' => 'name', 'sort' => 'desc'),
        array('data' => t('Email Id')),
        array('data' => t('phone Number')),
        array('data' => t('gender')),
        array('data' => t('Edit')),
    );
  
    $query = db_select('custom_form_with_db_table', 'cfwdt')
                ->fields('cfwdt');
  
    $result = $query->orderBy("id", "DESC")
                ->extend('TableSort')
                ->orderByHeader($header)
                ->extend('PagerDefault')
                ->limit(20)
                ->execute()
                ->fetchAll();
  
    $rows = array();
    foreach($result as $res) {
        $rows[] = array(
          !empty($res->id) ? $res->id : '', 
          !empty($res->name) ? $res->name : '',
          !empty($res->email_id) ? $res->email_id : '', 
          !empty($res->phone_number) ? $res->phone_number : '', 
          !empty($res->gender) ? $res->gender : '',
          l(t('Edit'), 'custom_form_with_db_table/form/' . $res->id, array('query' => drupal_get_destination(), 'html' => true)),
        );
    }
  
    // If rows are not empty theme and display the rows.
    $output = '';
    if (!empty($rows)) {
      $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'sort-table')));
      $output .= theme('pager');
    }

    $form['link'] = array(
      '#markup' => l(t('Add'), 'custom_form_with_db_table/form/new', array('query' => drupal_get_destination(), 'html' => true)), 
    );
  
    $form['tabke'] = array(
        '#markup' => $output, 
    );
  
    return $form;
 }