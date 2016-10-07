<?php

/**
 * @file
 * import prodess helper functions for bmb-product module
 */

function bmb_product_bmbws($method = NULL, $domain_id = NULL){
  if(empty($method) || empty($domain_id)) {
    drupal_set_message('Missing parameters. Unable to run import.', 'error');
    drupal_goto('/admin/config/bmb-product/settings');
  }
  
  switch($method) {
    case 'bmbws':
      bmb_product_bmbws_import($domain_id);
      break;
    case 'pim':
      bmb_product_pim_import($domain_id);
      break;
    default:
      drupal_set_message('Second parameter unknown. Unsupported import method.', 'error');
      drupal_goto('/admin/config/bmb-product/settings');
  }
  
}

function bmb_product_bmbws_import($domain_id) {
  print('bmbws');
}

function bmb_product_pim_import($domain_id) {
  print('pim');
}