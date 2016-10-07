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
function bmb_product_settings_form($form, &$form_state) {
  
  drupal_add_css(drupal_get_path('module', 'bmb_product') . '/assets/bmb-product-settings.css');
  
  // returns site name and domain id of active sites
  // exclude domains not requiring input based on domain specific settings
  $domain_raw = domain_domains();
  $domain_info = array();
  foreach($domain_raw as $domain_temp){
    $this_domain_id = $domain_temp['domain_id'];
    if(variable_get('bmb_product_domain_include_' . $this_domain_id, 0) == 0) {
      continue;
    }
    // 0 = PIM ; 1 = BMBWS
    $import_method = variable_get('bmb_product_domain_method_' . $this_domain_id, NULL);
    if(!is_null($import_method)) {
      $domain_info[$import_method][] = $domain_temp;
    } 
  }
  
  $form['bmb_product_info'] = array(
    '#markup' => '<p>Provides a means to update BMB sites using the PIM or BMBWS feed.</p><p>If your site does not appear here check the <a href="/admin/structure/domain">domain specific settings.</a></p>',
  );
  
  /* PIM FORM SETTING */
  $form['pim'] = array(
    '#type' => 'fieldset',
    '#title' => t('PIM Import Settings'),
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE, 
  );
  
  $form['pim']['bmb_product_pim_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable Import via Cron (Master On/Off)',
    '#default_value' => variable_get('bmb_product_pim_enabled', FALSE),
  );
  
  $form['pim']['bmb_products_pim_message'] = array(
      '#markup' => '<div id="bmbws-info">--> PIM sites will update via cron. Run manually only when required.</div>',
    );
  
  foreach($domain_info[0] as $domain_pim){
    $pim_site = '';
    $pim_site .= '<div class="bmbws-wrapper clearfix"><div class="bmb-div bmbws-sitename"><strong>' . $domain_pim['sitename'] . '</strong></div>';
    $pim_id = variable_get('bmb_product_pim_siteid_' . $domain_pim['domain_id'], '');
    if(empty($pim_id)) {
      $pim_site .= '<div class="bmb-alert">';
      $pim_site .= '<span class="alert">-->' . $domain_pim['sitename'] . ' is missing PIM brand ID. <a href="/admin/structure/domain/view/' . $domain_pim['domain_id'] . '/edit">Go to site page to enter.</a></span>';
    } else {
      $pim_site .= '<div class="bmb-div bmbws-url">';
      $pim_site .= '<span class="">PIM site ID - ' . $pim_id . '</span';
      $pim_site .= '<a href="/bmb-product/bmbws/' . $domain_pim['domain_id'] . '">';
    }
    $pim_site .= '</div>';
    if(!empty($pim_id)) {
      $pim_site .= '<div class="bmb-div bmbws-button"><button type="button" class="btn btn-default" mg="edit-bmb-products-bmbws-' . $domain_pim['domain_id'] . '">Run ' . $domain_pim['sitename'] . ' Now!!!</button></a></div>';
    }
    $pim_site .='</div>';
    
    $form['pim']['bmb_products_pim_' . $domain_pim['domain_id']] = array(
      '#markup' => $pim_site,
    );  
  }
  
  /* BMBWS FORM SETTING */
  $form['bmbws'] = array(
    '#type' => 'fieldset',
    '#title' => t('BMBWS Import Settings'),
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE, 
  );
  
  $form['bmbws']['bmb_product_bmbws_info'] = array(
    '#markup' => '<div id="bmbws-info"><strong>--></strong> BMBWS process must be run locally to create the file to import. <a href="/bmb_update_nodes/update_sites.php">Go to BMBWS Import Tool</a></div>',
  );
  
  foreach($domain_info[1] as $domain){
    $bmbws_site = '';
    $bmbws_site .= '<div class="bmbws-wrapper clearfix"><div class="bmb-div bmbws-sitename"><strong>' . $domain['sitename'] . '</strong></div>';
    $bmbws_site .= '<div class="bmb-div bmbws-url">';
    $domain_url = variable_get('bmb_product_bmbws_url_' . $domain['domain_id'], '');
    if(empty($domain_url)) {
      $bmbws_site .= '<span class="alert">-->' . $domain['sitename'] . ' is missing feed URL. <a href="/admin/structure/domain/view/' . $domain['domain_id'] . '/edit">Go to site page to enter.</a></span>';
    } else {
      $bmbws_site .= '<a href="' . $domain_url . '" target="_blank">File to import</a>';
      $bmbws_site .= '<a href="/bmb-product/bmbws/' . $domain['domain_id'] . '">';
    }
    $bmbws_site .= '</div>';
    if(!empty($domain_url)) {
      $bmbws_site .= '<div class="bmb-div bmbws-button"><button type="button" class="btn btn-default" mg="edit-bmb-products-bmbws-' . $domain['domain_id'] . '">Run ' . $domain['sitename'] . ' Now!!!</button></a></div>';
    }
    
    $bmbws_site .= '</div>';
    $form['bmbws']['bmb_products_bmbws_' . $domain['domain_id']] = array(
      '#markup' => $bmbws_site,
    );
  }
  
  /* DOMAIN INFORMATION */
  $form['config_info']= array(
    '#type' => 'fieldset',
    '#title' => t('Domain Info'),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE,
  );
  
  $str = '<ul id="bmb-products-domain-list">';
  foreach($domain_raw as $domain_2){
    $str .= '<li>' . $domain_2['sitename'] . ' - ' . $domain_2['domain_id'] . '</li>';
  }
  $str .= '</ul>';
  $form['config_info']['bmb_products_domain_info']= array(
    '#markup' => $str,
  );

  return system_settings_form($form);
}

