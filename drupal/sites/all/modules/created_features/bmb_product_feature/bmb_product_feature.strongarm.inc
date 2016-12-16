<?php
/**
 * @file
 * bmb_product_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bmb_product_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__bmb_product';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'domain' => array(
          'weight' => '14',
        ),
        'domain_path' => array(
          'weight' => '16',
        ),
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '15',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__bmb_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_bmb_product';
  $strongarm->value = array();
  $export['menu_options_bmb_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_bmb_product';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_bmb_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_bmb_product';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_bmb_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_bmb_product';
  $strongarm->value = '1';
  $export['node_preview_bmb_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_bmb_product';
  $strongarm->value = 0;
  $export['node_submitted_bmb_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_bmb_product_pattern';
  $strongarm->value = 'product/[node:title]-[node:field_bp_upc]';
  $export['pathauto_node_bmb_product_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_bmb_product_allergens_pattern';
  $strongarm->value = 'products/allergens/[term:name]';
  $export['pathauto_taxonomy_term_bmb_product_allergens_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_bmb_product_attributes_pattern';
  $strongarm->value = 'products/attributes/[term:name]';
  $export['pathauto_taxonomy_term_bmb_product_attributes_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_bmb_product_category_pattern';
  $strongarm->value = 'products/category/[term:name]';
  $export['pathauto_taxonomy_term_bmb_product_category_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_bmb_product_certificates_pattern';
  $strongarm->value = 'products/certifications/[term:name]';
  $export['pathauto_taxonomy_term_bmb_product_certificates_pattern'] = $strongarm;

  return $export;
}
