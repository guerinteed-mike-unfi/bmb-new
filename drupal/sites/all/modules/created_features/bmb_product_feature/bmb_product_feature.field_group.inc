<?php
/**
 * @file
 * bmb_product_feature.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function bmb_product_feature_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_bm_pim_information|node|bmb_product|form';
  $field_group->group_name = 'group_bm_pim_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bmb_product';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PIM Information',
    'weight' => '13',
    'children' => array(
      0 => 'field_bp_pim_nid',
      1 => 'field_bp_pim_creation_date',
      2 => 'field_bp_pim_change_date',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'PIM Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-bm-pim-information field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_bm_pim_information|node|bmb_product|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_bp_nutrition_panel|node|bmb_product|form';
  $field_group->group_name = 'group_bp_nutrition_panel';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bmb_product';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Nutrition Panel',
    'weight' => '12',
    'children' => array(
      0 => 'field_bp_serving_size',
      1 => 'field_bp_servings_per_container',
      2 => 'field_bp_calories',
      3 => 'field_bp_calories_from_fat',
      4 => 'field_bp_total_fat',
      5 => 'field_bp_pdv_total_fat',
      6 => 'field_bp_saturated_fat',
      7 => 'field_bp_trans_fat',
      8 => 'field_bp_cholesterol',
      9 => 'field_bp_pdv_saturated_fat',
      10 => 'field_bp_pdv_cholesterol',
      11 => 'field_bp_sodium',
      12 => 'field_bp_pdv_sodium',
      13 => 'field_bp_carbohydrates',
      14 => 'field_bp_pdv_carbohydrates',
      15 => 'field_bp_fiber',
      16 => 'field_bp_pdv_fiber',
      17 => 'field_bp_sugars',
      18 => 'field_bp_protein',
      19 => 'field_bp_vitamin_a',
      20 => 'field_bp_vitamin_c',
      21 => 'field_bp_calcium',
      22 => 'field_bp_iron',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-bp-nutrition-panel field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_bp_nutrition_panel|node|bmb_product|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Nutrition Panel');
  t('PIM Information');

  return $field_groups;
}
