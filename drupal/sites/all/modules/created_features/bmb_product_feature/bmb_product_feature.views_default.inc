<?php
/**
 * @file
 * bmb_product_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function bmb_product_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'global_active_categories';
  $view->description = 'Domain specific list of category terms that have active products ';
  $view->tag = 'BMB Product';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Global Active Categories';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Taxonomy term: Representative node */
  $handler->display->display_options['relationships']['tid_representative']['id'] = 'tid_representative';
  $handler->display->display_options['relationships']['tid_representative']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['tid_representative']['field'] = 'tid_representative';
  $handler->display->display_options['relationships']['tid_representative']['required'] = TRUE;
  $handler->display->display_options['relationships']['tid_representative']['subquery_sort'] = 'node.nid';
  $handler->display->display_options['relationships']['tid_representative']['subquery_view'] = '';
  $handler->display->display_options['relationships']['tid_representative']['subquery_namespace'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Sort criterion: Taxonomy term: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'bmb_product_category' => 'bmb_product_category',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'tid_representative';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bmb_product' => 'bmb_product',
  );
  /* Filter criterion: Domains: Domain ID */
  $handler->display->display_options['filters']['domain_id']['id'] = 'domain_id';
  $handler->display->display_options['filters']['domain_id']['table'] = 'domain';
  $handler->display->display_options['filters']['domain_id']['field'] = 'domain_id';
  $handler->display->display_options['filters']['domain_id']['relationship'] = 'tid_representative';
  $handler->display->display_options['filters']['domain_id']['value'] = array(
    '***CURRENT_DOMAIN***' => '***CURRENT_DOMAIN***',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['pane_category']['name'] = 'UNFI';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 'offset';
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 'more_link';
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 'fields_override';
  $export['global_active_categories'] = $view;

  $view = new view();
  $view->name = 'global_other_products_in_category';
  $view->description = 'Random selection of other items in the same product category; excluding current item';
  $view->tag = 'BMB Product';
  $view->base_table = 'node';
  $view->human_name = 'Global Other Products In Category';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Primary Image */
  $handler->display->display_options['fields']['field_bp_primary_image']['id'] = 'field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['table'] = 'field_data_field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['field'] = 'field_bp_primary_image';
  /* Field: Content: UPC */
  $handler->display->display_options['fields']['field_bp_upc']['id'] = 'field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['table'] = 'field_data_field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['field'] = 'field_bp_upc';
  /* Sort criterion: Global: Random */
  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['not'] = TRUE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = FALSE;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['node'] = TRUE;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['vocabularies'] = array(
    'bmb_product_category' => 'bmb_product_category',
  );
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bmb_product' => 'bmb_product',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['pane_description'] = 'Panel with all products in a domain, grouped by category ';
  $handler->display->display_options['pane_category']['name'] = 'UNFI';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $export['global_other_products_in_category'] = $view;

  $view = new view();
  $view->name = 'global_products_by_category';
  $view->description = 'View showing BMB products grouped by Category';
  $view->tag = 'BMB Product';
  $view->base_table = 'node';
  $view->human_name = 'Global Products by Category';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Products by Category';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_bp_product_category',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  /* Field: Content: Calcium */
  $handler->display->display_options['fields']['field_bp_calcium']['id'] = 'field_bp_calcium';
  $handler->display->display_options['fields']['field_bp_calcium']['table'] = 'field_data_field_bp_calcium';
  $handler->display->display_options['fields']['field_bp_calcium']['field'] = 'field_bp_calcium';
  $handler->display->display_options['fields']['field_bp_calcium']['label'] = '';
  $handler->display->display_options['fields']['field_bp_calcium']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_calcium']['element_default_classes'] = FALSE;
  /* Field: Content: Calories */
  $handler->display->display_options['fields']['field_bp_calories']['id'] = 'field_bp_calories';
  $handler->display->display_options['fields']['field_bp_calories']['table'] = 'field_data_field_bp_calories';
  $handler->display->display_options['fields']['field_bp_calories']['field'] = 'field_bp_calories';
  $handler->display->display_options['fields']['field_bp_calories']['label'] = '';
  $handler->display->display_options['fields']['field_bp_calories']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_calories']['element_default_classes'] = FALSE;
  /* Field: Content: Calories from Fat */
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['id'] = 'field_bp_calories_from_fat';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['table'] = 'field_data_field_bp_calories_from_fat';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['field'] = 'field_bp_calories_from_fat';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['element_default_classes'] = FALSE;
  /* Field: Content: Carbohydrates */
  $handler->display->display_options['fields']['field_bp_carbohydrates']['id'] = 'field_bp_carbohydrates';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['table'] = 'field_data_field_bp_carbohydrates';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['field'] = 'field_bp_carbohydrates';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['label'] = '';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_carbohydrates']['element_default_classes'] = FALSE;
  /* Field: Content: Cholesterol */
  $handler->display->display_options['fields']['field_bp_cholesterol']['id'] = 'field_bp_cholesterol';
  $handler->display->display_options['fields']['field_bp_cholesterol']['table'] = 'field_data_field_bp_cholesterol';
  $handler->display->display_options['fields']['field_bp_cholesterol']['field'] = 'field_bp_cholesterol';
  $handler->display->display_options['fields']['field_bp_cholesterol']['label'] = '';
  $handler->display->display_options['fields']['field_bp_cholesterol']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_cholesterol']['element_default_classes'] = FALSE;
  /* Field: Content: Country of Origin */
  $handler->display->display_options['fields']['field_bp_country_of_origin']['id'] = 'field_bp_country_of_origin';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['table'] = 'field_data_field_bp_country_of_origin';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['field'] = 'field_bp_country_of_origin';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['label'] = '';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_country_of_origin']['element_default_classes'] = FALSE;
  /* Field: Content: Fiber */
  $handler->display->display_options['fields']['field_bp_fiber']['id'] = 'field_bp_fiber';
  $handler->display->display_options['fields']['field_bp_fiber']['table'] = 'field_data_field_bp_fiber';
  $handler->display->display_options['fields']['field_bp_fiber']['field'] = 'field_bp_fiber';
  $handler->display->display_options['fields']['field_bp_fiber']['label'] = '';
  $handler->display->display_options['fields']['field_bp_fiber']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_fiber']['element_default_classes'] = FALSE;
  /* Field: Content: Ingredients */
  $handler->display->display_options['fields']['field_bp_ingredients']['id'] = 'field_bp_ingredients';
  $handler->display->display_options['fields']['field_bp_ingredients']['table'] = 'field_data_field_bp_ingredients';
  $handler->display->display_options['fields']['field_bp_ingredients']['field'] = 'field_bp_ingredients';
  $handler->display->display_options['fields']['field_bp_ingredients']['label'] = '';
  $handler->display->display_options['fields']['field_bp_ingredients']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_ingredients']['element_default_classes'] = FALSE;
  /* Field: Content: Iron */
  $handler->display->display_options['fields']['field_bp_iron']['id'] = 'field_bp_iron';
  $handler->display->display_options['fields']['field_bp_iron']['table'] = 'field_data_field_bp_iron';
  $handler->display->display_options['fields']['field_bp_iron']['field'] = 'field_bp_iron';
  $handler->display->display_options['fields']['field_bp_iron']['label'] = '';
  $handler->display->display_options['fields']['field_bp_iron']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_iron']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Carbohydrates */
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['id'] = 'field_bp_pdv_carbohydrates';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['table'] = 'field_data_field_bp_pdv_carbohydrates';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['field'] = 'field_bp_pdv_carbohydrates';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Cholesterol */
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['id'] = 'field_bp_pdv_cholesterol';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['table'] = 'field_data_field_bp_pdv_cholesterol';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['field'] = 'field_bp_pdv_cholesterol';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Fiber */
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['id'] = 'field_bp_pdv_fiber';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['table'] = 'field_data_field_bp_pdv_fiber';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['field'] = 'field_bp_pdv_fiber';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Saturated Fat */
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['id'] = 'field_bp_pdv_saturated_fat';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['table'] = 'field_data_field_bp_pdv_saturated_fat';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['field'] = 'field_bp_pdv_saturated_fat';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Sodium */
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['id'] = 'field_bp_pdv_sodium';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['table'] = 'field_data_field_bp_pdv_sodium';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['field'] = 'field_bp_pdv_sodium';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Total Fat */
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['id'] = 'field_bp_pdv_total_fat';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['table'] = 'field_data_field_bp_pdv_total_fat';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['field'] = 'field_bp_pdv_total_fat';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['element_default_classes'] = FALSE;
  /* Field: Content: PIM Change Date */
  $handler->display->display_options['fields']['field_bp_pim_change_date']['id'] = 'field_bp_pim_change_date';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['table'] = 'field_data_field_bp_pim_change_date';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['field'] = 'field_bp_pim_change_date';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_change_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_change_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: PIM Creation Date */
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['id'] = 'field_bp_pim_creation_date';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['table'] = 'field_data_field_bp_pim_creation_date';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['field'] = 'field_bp_pim_creation_date';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: PIM NID */
  $handler->display->display_options['fields']['field_bp_pim_nid']['id'] = 'field_bp_pim_nid';
  $handler->display->display_options['fields']['field_bp_pim_nid']['table'] = 'field_data_field_bp_pim_nid';
  $handler->display->display_options['fields']['field_bp_pim_nid']['field'] = 'field_bp_pim_nid';
  $handler->display->display_options['fields']['field_bp_pim_nid']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pim_nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_nid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_nid']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Primary Image */
  $handler->display->display_options['fields']['field_bp_primary_image']['id'] = 'field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['table'] = 'field_data_field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['field'] = 'field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['label'] = '';
  $handler->display->display_options['fields']['field_bp_primary_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_primary_image']['element_default_classes'] = FALSE;
  /* Field: Content: Product Allergens */
  $handler->display->display_options['fields']['field_bp_product_allergens']['id'] = 'field_bp_product_allergens';
  $handler->display->display_options['fields']['field_bp_product_allergens']['table'] = 'field_data_field_bp_product_allergens';
  $handler->display->display_options['fields']['field_bp_product_allergens']['field'] = 'field_bp_product_allergens';
  $handler->display->display_options['fields']['field_bp_product_allergens']['label'] = '';
  $handler->display->display_options['fields']['field_bp_product_allergens']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_allergens']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_allergens']['delta_offset'] = '0';
  /* Field: Content: Product Attributes */
  $handler->display->display_options['fields']['field_bp_product_attributes']['id'] = 'field_bp_product_attributes';
  $handler->display->display_options['fields']['field_bp_product_attributes']['table'] = 'field_data_field_bp_product_attributes';
  $handler->display->display_options['fields']['field_bp_product_attributes']['field'] = 'field_bp_product_attributes';
  $handler->display->display_options['fields']['field_bp_product_attributes']['label'] = '';
  $handler->display->display_options['fields']['field_bp_product_attributes']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_attributes']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_attributes']['delta_offset'] = '0';
  /* Field: Content: Product Category */
  $handler->display->display_options['fields']['field_bp_product_category']['id'] = 'field_bp_product_category';
  $handler->display->display_options['fields']['field_bp_product_category']['table'] = 'field_data_field_bp_product_category';
  $handler->display->display_options['fields']['field_bp_product_category']['field'] = 'field_bp_product_category';
  $handler->display->display_options['fields']['field_bp_product_category']['label'] = '';
  $handler->display->display_options['fields']['field_bp_product_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_category']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_category']['delta_offset'] = '0';
  /* Field: Content: Protein */
  $handler->display->display_options['fields']['field_bp_protein']['id'] = 'field_bp_protein';
  $handler->display->display_options['fields']['field_bp_protein']['table'] = 'field_data_field_bp_protein';
  $handler->display->display_options['fields']['field_bp_protein']['field'] = 'field_bp_protein';
  $handler->display->display_options['fields']['field_bp_protein']['label'] = '';
  $handler->display->display_options['fields']['field_bp_protein']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_protein']['element_default_classes'] = FALSE;
  /* Field: Content: Retail Size */
  $handler->display->display_options['fields']['field_bp_retail_size']['id'] = 'field_bp_retail_size';
  $handler->display->display_options['fields']['field_bp_retail_size']['table'] = 'field_data_field_bp_retail_size';
  $handler->display->display_options['fields']['field_bp_retail_size']['field'] = 'field_bp_retail_size';
  $handler->display->display_options['fields']['field_bp_retail_size']['label'] = '';
  $handler->display->display_options['fields']['field_bp_retail_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_retail_size']['element_default_classes'] = FALSE;
  /* Field: Content: Saturated Fat */
  $handler->display->display_options['fields']['field_bp_saturated_fat']['id'] = 'field_bp_saturated_fat';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['table'] = 'field_data_field_bp_saturated_fat';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['field'] = 'field_bp_saturated_fat';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_saturated_fat']['element_default_classes'] = FALSE;
  /* Field: Content: Serving Size */
  $handler->display->display_options['fields']['field_bp_serving_size']['id'] = 'field_bp_serving_size';
  $handler->display->display_options['fields']['field_bp_serving_size']['table'] = 'field_data_field_bp_serving_size';
  $handler->display->display_options['fields']['field_bp_serving_size']['field'] = 'field_bp_serving_size';
  $handler->display->display_options['fields']['field_bp_serving_size']['label'] = '';
  $handler->display->display_options['fields']['field_bp_serving_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_serving_size']['element_default_classes'] = FALSE;
  /* Field: Content: Servings per Container */
  $handler->display->display_options['fields']['field_bp_servings_per_container']['id'] = 'field_bp_servings_per_container';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['table'] = 'field_data_field_bp_servings_per_container';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['field'] = 'field_bp_servings_per_container';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['label'] = '';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_servings_per_container']['element_default_classes'] = FALSE;
  /* Field: Content: Sodium */
  $handler->display->display_options['fields']['field_bp_sodium']['id'] = 'field_bp_sodium';
  $handler->display->display_options['fields']['field_bp_sodium']['table'] = 'field_data_field_bp_sodium';
  $handler->display->display_options['fields']['field_bp_sodium']['field'] = 'field_bp_sodium';
  $handler->display->display_options['fields']['field_bp_sodium']['label'] = '';
  $handler->display->display_options['fields']['field_bp_sodium']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_sodium']['element_default_classes'] = FALSE;
  /* Field: Content: Sugars */
  $handler->display->display_options['fields']['field_bp_sugars']['id'] = 'field_bp_sugars';
  $handler->display->display_options['fields']['field_bp_sugars']['table'] = 'field_data_field_bp_sugars';
  $handler->display->display_options['fields']['field_bp_sugars']['field'] = 'field_bp_sugars';
  $handler->display->display_options['fields']['field_bp_sugars']['label'] = '';
  $handler->display->display_options['fields']['field_bp_sugars']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_sugars']['element_default_classes'] = FALSE;
  /* Field: Content: Total Fat */
  $handler->display->display_options['fields']['field_bp_total_fat']['id'] = 'field_bp_total_fat';
  $handler->display->display_options['fields']['field_bp_total_fat']['table'] = 'field_data_field_bp_total_fat';
  $handler->display->display_options['fields']['field_bp_total_fat']['field'] = 'field_bp_total_fat';
  $handler->display->display_options['fields']['field_bp_total_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_total_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_total_fat']['element_default_classes'] = FALSE;
  /* Field: Content: Trans Fat */
  $handler->display->display_options['fields']['field_bp_trans_fat']['id'] = 'field_bp_trans_fat';
  $handler->display->display_options['fields']['field_bp_trans_fat']['table'] = 'field_data_field_bp_trans_fat';
  $handler->display->display_options['fields']['field_bp_trans_fat']['field'] = 'field_bp_trans_fat';
  $handler->display->display_options['fields']['field_bp_trans_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_trans_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_trans_fat']['element_default_classes'] = FALSE;
  /* Field: Content: UNFI Item */
  $handler->display->display_options['fields']['field_bp_unfi_item']['id'] = 'field_bp_unfi_item';
  $handler->display->display_options['fields']['field_bp_unfi_item']['table'] = 'field_data_field_bp_unfi_item';
  $handler->display->display_options['fields']['field_bp_unfi_item']['field'] = 'field_bp_unfi_item';
  $handler->display->display_options['fields']['field_bp_unfi_item']['label'] = '';
  $handler->display->display_options['fields']['field_bp_unfi_item']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_unfi_item']['element_default_classes'] = FALSE;
  /* Field: Content: UPC */
  $handler->display->display_options['fields']['field_bp_upc']['id'] = 'field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['table'] = 'field_data_field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['field'] = 'field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['label'] = '';
  $handler->display->display_options['fields']['field_bp_upc']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_upc']['element_default_classes'] = FALSE;
  /* Field: Content: Vitamin A */
  $handler->display->display_options['fields']['field_bp_vitamin_a']['id'] = 'field_bp_vitamin_a';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['table'] = 'field_data_field_bp_vitamin_a';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['field'] = 'field_bp_vitamin_a';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['label'] = '';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_vitamin_a']['element_default_classes'] = FALSE;
  /* Field: Content: Vitamin C */
  $handler->display->display_options['fields']['field_bp_vitamin_c']['id'] = 'field_bp_vitamin_c';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['table'] = 'field_data_field_bp_vitamin_c';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['field'] = 'field_bp_vitamin_c';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['label'] = '';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_vitamin_c']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Product Category (field_bp_product_category) */
  $handler->display->display_options['sorts']['field_bp_product_category_tid']['id'] = 'field_bp_product_category_tid';
  $handler->display->display_options['sorts']['field_bp_product_category_tid']['table'] = 'field_data_field_bp_product_category';
  $handler->display->display_options['sorts']['field_bp_product_category_tid']['field'] = 'field_bp_product_category_tid';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bmb_product' => 'bmb_product',
  );
  /* Filter criterion: Domains: Domain ID */
  $handler->display->display_options['filters']['domain_id']['id'] = 'domain_id';
  $handler->display->display_options['filters']['domain_id']['table'] = 'domain';
  $handler->display->display_options['filters']['domain_id']['field'] = 'domain_id';
  $handler->display->display_options['filters']['domain_id']['value'] = array(
    '***CURRENT_DOMAIN***' => '***CURRENT_DOMAIN***',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'products-by-category';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Products';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['pane_category']['name'] = 'UNFI';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 'offset';
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 'fields_override';
  $export['global_products_by_category'] = $view;

  $view = new view();
  $view->name = 'global_products_by_category_filtered';
  $view->description = 'View showing BMB products grouped by Category';
  $view->tag = 'BMB Product';
  $view->base_table = 'node';
  $view->human_name = 'Global Products by Category Filtered';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Products by Category';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_bp_product_category',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  /* Field: Content: Calcium */
  $handler->display->display_options['fields']['field_bp_calcium']['id'] = 'field_bp_calcium';
  $handler->display->display_options['fields']['field_bp_calcium']['table'] = 'field_data_field_bp_calcium';
  $handler->display->display_options['fields']['field_bp_calcium']['field'] = 'field_bp_calcium';
  $handler->display->display_options['fields']['field_bp_calcium']['label'] = '';
  $handler->display->display_options['fields']['field_bp_calcium']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_calcium']['element_default_classes'] = FALSE;
  /* Field: Content: Calories */
  $handler->display->display_options['fields']['field_bp_calories']['id'] = 'field_bp_calories';
  $handler->display->display_options['fields']['field_bp_calories']['table'] = 'field_data_field_bp_calories';
  $handler->display->display_options['fields']['field_bp_calories']['field'] = 'field_bp_calories';
  $handler->display->display_options['fields']['field_bp_calories']['label'] = '';
  $handler->display->display_options['fields']['field_bp_calories']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_calories']['element_default_classes'] = FALSE;
  /* Field: Content: Calories from Fat */
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['id'] = 'field_bp_calories_from_fat';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['table'] = 'field_data_field_bp_calories_from_fat';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['field'] = 'field_bp_calories_from_fat';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_calories_from_fat']['element_default_classes'] = FALSE;
  /* Field: Content: Carbohydrates */
  $handler->display->display_options['fields']['field_bp_carbohydrates']['id'] = 'field_bp_carbohydrates';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['table'] = 'field_data_field_bp_carbohydrates';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['field'] = 'field_bp_carbohydrates';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['label'] = '';
  $handler->display->display_options['fields']['field_bp_carbohydrates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_carbohydrates']['element_default_classes'] = FALSE;
  /* Field: Content: Cholesterol */
  $handler->display->display_options['fields']['field_bp_cholesterol']['id'] = 'field_bp_cholesterol';
  $handler->display->display_options['fields']['field_bp_cholesterol']['table'] = 'field_data_field_bp_cholesterol';
  $handler->display->display_options['fields']['field_bp_cholesterol']['field'] = 'field_bp_cholesterol';
  $handler->display->display_options['fields']['field_bp_cholesterol']['label'] = '';
  $handler->display->display_options['fields']['field_bp_cholesterol']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_cholesterol']['element_default_classes'] = FALSE;
  /* Field: Content: Country of Origin */
  $handler->display->display_options['fields']['field_bp_country_of_origin']['id'] = 'field_bp_country_of_origin';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['table'] = 'field_data_field_bp_country_of_origin';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['field'] = 'field_bp_country_of_origin';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['label'] = '';
  $handler->display->display_options['fields']['field_bp_country_of_origin']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_country_of_origin']['element_default_classes'] = FALSE;
  /* Field: Content: Fiber */
  $handler->display->display_options['fields']['field_bp_fiber']['id'] = 'field_bp_fiber';
  $handler->display->display_options['fields']['field_bp_fiber']['table'] = 'field_data_field_bp_fiber';
  $handler->display->display_options['fields']['field_bp_fiber']['field'] = 'field_bp_fiber';
  $handler->display->display_options['fields']['field_bp_fiber']['label'] = '';
  $handler->display->display_options['fields']['field_bp_fiber']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_fiber']['element_default_classes'] = FALSE;
  /* Field: Content: Ingredients */
  $handler->display->display_options['fields']['field_bp_ingredients']['id'] = 'field_bp_ingredients';
  $handler->display->display_options['fields']['field_bp_ingredients']['table'] = 'field_data_field_bp_ingredients';
  $handler->display->display_options['fields']['field_bp_ingredients']['field'] = 'field_bp_ingredients';
  $handler->display->display_options['fields']['field_bp_ingredients']['label'] = '';
  $handler->display->display_options['fields']['field_bp_ingredients']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_ingredients']['element_default_classes'] = FALSE;
  /* Field: Content: Iron */
  $handler->display->display_options['fields']['field_bp_iron']['id'] = 'field_bp_iron';
  $handler->display->display_options['fields']['field_bp_iron']['table'] = 'field_data_field_bp_iron';
  $handler->display->display_options['fields']['field_bp_iron']['field'] = 'field_bp_iron';
  $handler->display->display_options['fields']['field_bp_iron']['label'] = '';
  $handler->display->display_options['fields']['field_bp_iron']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_iron']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Carbohydrates */
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['id'] = 'field_bp_pdv_carbohydrates';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['table'] = 'field_data_field_bp_pdv_carbohydrates';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['field'] = 'field_bp_pdv_carbohydrates';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_carbohydrates']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Cholesterol */
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['id'] = 'field_bp_pdv_cholesterol';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['table'] = 'field_data_field_bp_pdv_cholesterol';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['field'] = 'field_bp_pdv_cholesterol';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_cholesterol']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Fiber */
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['id'] = 'field_bp_pdv_fiber';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['table'] = 'field_data_field_bp_pdv_fiber';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['field'] = 'field_bp_pdv_fiber';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_fiber']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Saturated Fat */
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['id'] = 'field_bp_pdv_saturated_fat';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['table'] = 'field_data_field_bp_pdv_saturated_fat';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['field'] = 'field_bp_pdv_saturated_fat';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_saturated_fat']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Sodium */
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['id'] = 'field_bp_pdv_sodium';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['table'] = 'field_data_field_bp_pdv_sodium';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['field'] = 'field_bp_pdv_sodium';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_sodium']['element_default_classes'] = FALSE;
  /* Field: Content: PDV Total Fat */
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['id'] = 'field_bp_pdv_total_fat';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['table'] = 'field_data_field_bp_pdv_total_fat';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['field'] = 'field_bp_pdv_total_fat';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pdv_total_fat']['element_default_classes'] = FALSE;
  /* Field: Content: PIM Change Date */
  $handler->display->display_options['fields']['field_bp_pim_change_date']['id'] = 'field_bp_pim_change_date';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['table'] = 'field_data_field_bp_pim_change_date';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['field'] = 'field_bp_pim_change_date';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pim_change_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_change_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_change_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: PIM Creation Date */
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['id'] = 'field_bp_pim_creation_date';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['table'] = 'field_data_field_bp_pim_creation_date';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['field'] = 'field_bp_pim_creation_date';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_creation_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: PIM NID */
  $handler->display->display_options['fields']['field_bp_pim_nid']['id'] = 'field_bp_pim_nid';
  $handler->display->display_options['fields']['field_bp_pim_nid']['table'] = 'field_data_field_bp_pim_nid';
  $handler->display->display_options['fields']['field_bp_pim_nid']['field'] = 'field_bp_pim_nid';
  $handler->display->display_options['fields']['field_bp_pim_nid']['label'] = '';
  $handler->display->display_options['fields']['field_bp_pim_nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_nid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_pim_nid']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Primary Image */
  $handler->display->display_options['fields']['field_bp_primary_image']['id'] = 'field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['table'] = 'field_data_field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['field'] = 'field_bp_primary_image';
  $handler->display->display_options['fields']['field_bp_primary_image']['label'] = '';
  $handler->display->display_options['fields']['field_bp_primary_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_primary_image']['element_default_classes'] = FALSE;
  /* Field: Content: Product Allergens */
  $handler->display->display_options['fields']['field_bp_product_allergens']['id'] = 'field_bp_product_allergens';
  $handler->display->display_options['fields']['field_bp_product_allergens']['table'] = 'field_data_field_bp_product_allergens';
  $handler->display->display_options['fields']['field_bp_product_allergens']['field'] = 'field_bp_product_allergens';
  $handler->display->display_options['fields']['field_bp_product_allergens']['label'] = '';
  $handler->display->display_options['fields']['field_bp_product_allergens']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_allergens']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_allergens']['delta_offset'] = '0';
  /* Field: Content: Product Attributes */
  $handler->display->display_options['fields']['field_bp_product_attributes']['id'] = 'field_bp_product_attributes';
  $handler->display->display_options['fields']['field_bp_product_attributes']['table'] = 'field_data_field_bp_product_attributes';
  $handler->display->display_options['fields']['field_bp_product_attributes']['field'] = 'field_bp_product_attributes';
  $handler->display->display_options['fields']['field_bp_product_attributes']['label'] = '';
  $handler->display->display_options['fields']['field_bp_product_attributes']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_attributes']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_attributes']['delta_offset'] = '0';
  /* Field: Content: Product Category */
  $handler->display->display_options['fields']['field_bp_product_category']['id'] = 'field_bp_product_category';
  $handler->display->display_options['fields']['field_bp_product_category']['table'] = 'field_data_field_bp_product_category';
  $handler->display->display_options['fields']['field_bp_product_category']['field'] = 'field_bp_product_category';
  $handler->display->display_options['fields']['field_bp_product_category']['label'] = '';
  $handler->display->display_options['fields']['field_bp_product_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_category']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_bp_product_category']['delta_offset'] = '0';
  /* Field: Content: Protein */
  $handler->display->display_options['fields']['field_bp_protein']['id'] = 'field_bp_protein';
  $handler->display->display_options['fields']['field_bp_protein']['table'] = 'field_data_field_bp_protein';
  $handler->display->display_options['fields']['field_bp_protein']['field'] = 'field_bp_protein';
  $handler->display->display_options['fields']['field_bp_protein']['label'] = '';
  $handler->display->display_options['fields']['field_bp_protein']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_protein']['element_default_classes'] = FALSE;
  /* Field: Content: Retail Size */
  $handler->display->display_options['fields']['field_bp_retail_size']['id'] = 'field_bp_retail_size';
  $handler->display->display_options['fields']['field_bp_retail_size']['table'] = 'field_data_field_bp_retail_size';
  $handler->display->display_options['fields']['field_bp_retail_size']['field'] = 'field_bp_retail_size';
  $handler->display->display_options['fields']['field_bp_retail_size']['label'] = '';
  $handler->display->display_options['fields']['field_bp_retail_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_retail_size']['element_default_classes'] = FALSE;
  /* Field: Content: Saturated Fat */
  $handler->display->display_options['fields']['field_bp_saturated_fat']['id'] = 'field_bp_saturated_fat';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['table'] = 'field_data_field_bp_saturated_fat';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['field'] = 'field_bp_saturated_fat';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_saturated_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_saturated_fat']['element_default_classes'] = FALSE;
  /* Field: Content: Serving Size */
  $handler->display->display_options['fields']['field_bp_serving_size']['id'] = 'field_bp_serving_size';
  $handler->display->display_options['fields']['field_bp_serving_size']['table'] = 'field_data_field_bp_serving_size';
  $handler->display->display_options['fields']['field_bp_serving_size']['field'] = 'field_bp_serving_size';
  $handler->display->display_options['fields']['field_bp_serving_size']['label'] = '';
  $handler->display->display_options['fields']['field_bp_serving_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_serving_size']['element_default_classes'] = FALSE;
  /* Field: Content: Servings per Container */
  $handler->display->display_options['fields']['field_bp_servings_per_container']['id'] = 'field_bp_servings_per_container';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['table'] = 'field_data_field_bp_servings_per_container';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['field'] = 'field_bp_servings_per_container';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['label'] = '';
  $handler->display->display_options['fields']['field_bp_servings_per_container']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_servings_per_container']['element_default_classes'] = FALSE;
  /* Field: Content: Sodium */
  $handler->display->display_options['fields']['field_bp_sodium']['id'] = 'field_bp_sodium';
  $handler->display->display_options['fields']['field_bp_sodium']['table'] = 'field_data_field_bp_sodium';
  $handler->display->display_options['fields']['field_bp_sodium']['field'] = 'field_bp_sodium';
  $handler->display->display_options['fields']['field_bp_sodium']['label'] = '';
  $handler->display->display_options['fields']['field_bp_sodium']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_sodium']['element_default_classes'] = FALSE;
  /* Field: Content: Sugars */
  $handler->display->display_options['fields']['field_bp_sugars']['id'] = 'field_bp_sugars';
  $handler->display->display_options['fields']['field_bp_sugars']['table'] = 'field_data_field_bp_sugars';
  $handler->display->display_options['fields']['field_bp_sugars']['field'] = 'field_bp_sugars';
  $handler->display->display_options['fields']['field_bp_sugars']['label'] = '';
  $handler->display->display_options['fields']['field_bp_sugars']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_sugars']['element_default_classes'] = FALSE;
  /* Field: Content: Total Fat */
  $handler->display->display_options['fields']['field_bp_total_fat']['id'] = 'field_bp_total_fat';
  $handler->display->display_options['fields']['field_bp_total_fat']['table'] = 'field_data_field_bp_total_fat';
  $handler->display->display_options['fields']['field_bp_total_fat']['field'] = 'field_bp_total_fat';
  $handler->display->display_options['fields']['field_bp_total_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_total_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_total_fat']['element_default_classes'] = FALSE;
  /* Field: Content: Trans Fat */
  $handler->display->display_options['fields']['field_bp_trans_fat']['id'] = 'field_bp_trans_fat';
  $handler->display->display_options['fields']['field_bp_trans_fat']['table'] = 'field_data_field_bp_trans_fat';
  $handler->display->display_options['fields']['field_bp_trans_fat']['field'] = 'field_bp_trans_fat';
  $handler->display->display_options['fields']['field_bp_trans_fat']['label'] = '';
  $handler->display->display_options['fields']['field_bp_trans_fat']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_trans_fat']['element_default_classes'] = FALSE;
  /* Field: Content: UNFI Item */
  $handler->display->display_options['fields']['field_bp_unfi_item']['id'] = 'field_bp_unfi_item';
  $handler->display->display_options['fields']['field_bp_unfi_item']['table'] = 'field_data_field_bp_unfi_item';
  $handler->display->display_options['fields']['field_bp_unfi_item']['field'] = 'field_bp_unfi_item';
  $handler->display->display_options['fields']['field_bp_unfi_item']['label'] = '';
  $handler->display->display_options['fields']['field_bp_unfi_item']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_unfi_item']['element_default_classes'] = FALSE;
  /* Field: Content: UPC */
  $handler->display->display_options['fields']['field_bp_upc']['id'] = 'field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['table'] = 'field_data_field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['field'] = 'field_bp_upc';
  $handler->display->display_options['fields']['field_bp_upc']['label'] = '';
  $handler->display->display_options['fields']['field_bp_upc']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_upc']['element_default_classes'] = FALSE;
  /* Field: Content: Vitamin A */
  $handler->display->display_options['fields']['field_bp_vitamin_a']['id'] = 'field_bp_vitamin_a';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['table'] = 'field_data_field_bp_vitamin_a';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['field'] = 'field_bp_vitamin_a';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['label'] = '';
  $handler->display->display_options['fields']['field_bp_vitamin_a']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_vitamin_a']['element_default_classes'] = FALSE;
  /* Field: Content: Vitamin C */
  $handler->display->display_options['fields']['field_bp_vitamin_c']['id'] = 'field_bp_vitamin_c';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['table'] = 'field_data_field_bp_vitamin_c';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['field'] = 'field_bp_vitamin_c';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['label'] = '';
  $handler->display->display_options['fields']['field_bp_vitamin_c']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bp_vitamin_c']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Product Category (field_bp_product_category) */
  $handler->display->display_options['sorts']['field_bp_product_category_tid']['id'] = 'field_bp_product_category_tid';
  $handler->display->display_options['sorts']['field_bp_product_category_tid']['table'] = 'field_data_field_bp_product_category';
  $handler->display->display_options['sorts']['field_bp_product_category_tid']['field'] = 'field_bp_product_category_tid';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['term_node_tid_depth']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title'] = '%1';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['term_node_tid_depth']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['vocabularies'] = array(
    'bmb_product_category' => 'bmb_product_category',
  );
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate_options']['transform'] = TRUE;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['fail'] = 'empty';
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '1';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bmb_product' => 'bmb_product',
  );
  /* Filter criterion: Domains: Domain ID */
  $handler->display->display_options['filters']['domain_id']['id'] = 'domain_id';
  $handler->display->display_options['filters']['domain_id']['table'] = 'domain';
  $handler->display->display_options['filters']['domain_id']['field'] = 'domain_id';
  $handler->display->display_options['filters']['domain_id']['value'] = array(
    '***CURRENT_DOMAIN***' => '***CURRENT_DOMAIN***',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'products/parent-category';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Products';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['pane_category']['name'] = 'UNFI';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 'offset';
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 'fields_override';
  $export['global_products_by_category_filtered'] = $view;

  return $export;
}
