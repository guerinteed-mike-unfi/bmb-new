<?php
/**
 * @file
 * bmb_product_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bmb_product_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function bmb_product_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function bmb_product_feature_node_info() {
  $items = array(
    'bmb_product' => array(
      'name' => t('BMB Product'),
      'base' => 'node_content',
      'description' => t('A Blue Marble Brands product.'),
      'has_title' => '1',
      'title_label' => t('Product Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
