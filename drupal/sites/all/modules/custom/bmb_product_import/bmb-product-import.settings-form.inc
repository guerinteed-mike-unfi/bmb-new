<?php

/**
 * @file
 * helper functions for the bmb_pim module
 */

/**
 * 
 * Form for /admin/config/
 * 
 * @system variables
 * @todo
 * 
 */
function bmb_product_import_settings_form($form, &$form_state) {
  
  drupal_add_css(drupal_get_path('module', 'bmb_product_import') . '/bmb-product-import-settings.css');
  drupal_add_js(drupal_get_path('module', 'bmb_product_import') . '/bmb-product-import-settings.js');
  
  // returns site name and domain id of active sites
  // exclude domains not requiring input
  // 1 = blue marble brands; 9 = team non gmo
  $domain_raw = domain_domains();
  $domain_info = array();
  foreach($domain_raw as $domain_temp){
    if($domain_temp['domain_id'] == 1 || $domain_temp['domain_id'] == 9) {
      continue;
    }
    $domain_info[] = $domain_temp;
  }
  
  $form['bmb_product_import_info'] = array(
    '#markup' => '<p>Provides a means to update BMB sites using the PIM or BMBWS feed.</p>',
  );
  
  /* PIM FORM SETTING */
  $form['pim'] = array(
    '#type' => 'fieldset',
    '#title' => t('PIM Import Settings'),
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE, 
  );
  
  $form['pim']['bmb_product_import_pim_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable Import via Cron',
    '#default_value' => variable_get('bmb_product_import_pim_enabled', FALSE),
  );
  
  /* BMBWS FORM SETTING */
  $form['bmbws'] = array(
    '#type' => 'fieldset',
    '#title' => t('BMBWS Import Settings'),
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE, 
  );
  
  $form['bmbws']['bmb_product_import_bmbws_info'] = array(
    '#markup' => '<div id="bmbws-info"><strong>--></strong> BMBWS process must be run locally to create the file to import. <a href="/bmb_update_nodes/update_sites.php">Go to BMBWS Import Tool</a></div>',
  );
  
  foreach($domain_info as $domain){
    $this_prefix = '<div class="bmbws-wrapper clearfix"><div class="bmbws-div bmbws-sitename"><strong>' . $domain['sitename'] . '</strong></div><div class="bmbws-div bmbws-textfield">';
    $this_suffix = '</div><div class="bmbws-div pws-run-now alert">';
    $this_value = variable_get('bmb_products_import_bmbws_' . $domain['domain_id'], '');
    if(empty($this_value)){
      $this_suffix .= '<span class="alert">Enter a value and save to run</span>';
    } else {
      $this_suffix .= '<a href="/bmb-product-import/bmbws/' . $domain['domain_id'] . '"><button type="button" class="btn btn-default" mg="edit-bmb-products-import-bmbws-' . $domain['domain_id'] . '">' . $domain['sitename'] . ' Run Now!!!</button></a>';
    }
    $this_suffix .='</div></div>';
    
    $form['bmbws']['bmb_products_import_bmbws_' . $domain['domain_id']] = array(
      '#type' => 'textfield',
      '#title' => t('URL - '),
      '#default_value' => $this_value,
      '#prefix' => $this_prefix,
      '#suffix' => $this_suffix, 
    );
  }
  
  /* DOMAIN INFORMATION */
  $form['config_info']= array(
    '#type' => 'fieldset',
    '#title' => t('Domain Info'),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE,
  );
  
  $str = '<ul id="bmb-products-import-domain-list">';
  foreach($domain_info as $domain_2){
    $str .= '<li>' . $domain_2['sitename'] . ' - ' . $domain_2['domain_id'] . '</li>';
  }
  $str .= '</ul>';
  
  $form['config_info']['bmb_products_import_domain_info']= array(
    '#markup' => $str,
  );

  return system_settings_form($form);
}

