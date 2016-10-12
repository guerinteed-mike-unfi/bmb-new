<?php

/**
 * @file
 * 
 * import prodess helper functions for bmb-product module
 */
 
 // PIM CONNECTION INFO
 define('BMB_PRODUCT_PIM_BASE_URL', 'https://bluemarbledm-staging.metaltoad-sites.com/');
 define('BMB_PRODUCT_PIM_AUTH_ENDPOINT', 'oauth2/token');
 define('BMB_PRODUCT_PIM_PRODUCT_ENDPOINT', 'service/digitalcore/products');
 define('BMB_PRODUCT_PIM_USER', 'bmbwebsites');
 define('BMB_PRODUCT_PIM_PASSWORD', 'Blu3m@rbl3');
 
/**
 * Callback for menu hook
 * 
 * @param 
 * string $method - 'bmbws' or 'pim' indicating what service to use 
 * integer $domain_id - domain identifier of domain access module
 * integer $run_from_ui - 0 = run from cron, 1 = run from UI
 */
function bmb_product_import($method = NULL, $domain_id = NULL, $run_from_ui = 0){
  //print('here - ' . $method . ' - ' . $domain_id . '<br>');
  if(empty($method) || empty($domain_id)) {
    if($run_from_ui == 0) {
      watchdog('BMB Product', 'Missing parameters. Unable to run import.', NULL, WATCHDOG_ERROR);
      return;
    } else {
      drupal_set_message('Missing parameters. Unable to run import.', 'error');
      drupal_goto('/admin/config/bmb-product/settings');
    }
  }
  
  // verify taxonomy settings are there - stored as system settings
  $vocab_product = variable_get('bmb_product_category', 0);
  $vocab_attributes = variable_get('bmb_product_attributes', 0);
  $vocab_allergens = variable_get('bmb_product_allergens', 0);
  if($vocab_product == 0 || $vocab_attributes == 0 || $vocab_allergens == 0){
    if($run_from_ui == 0) {
      watchdog('BMB Product', 'Vocabularies not set up correctly. Unable to run import.', NULL, WATCHDOG_ERROR);
      return;
    } else {
      drupal_set_message('Vocabularies not set up correctly. Unable to run import.', 'error');
      drupal_goto('/admin/config/bmb-product/settings');
    } 
  }
  
  // THIS WILL BE PASSED BY REFERENCE
  // variable used to track the process
  $wsup = array();
  $wsup['import_method'] = $method;
  $wsup['run_from_ui'] = $run_from_ui;
  // get domain info stored by domain access module
  $wsup['domain'] = domain_load($domain_id);
  $wsup['taxonomy']['product'] = taxonomy_vocabulary_load($vocab_product);
  $wsup['taxonomy']['attributes'] = taxonomy_vocabulary_load($vocab_attributes);
  $wsup['taxonomy']['allergens'] = taxonomy_vocabulary_load($vocab_allergens);
  
  // product category taxonomy is used by all domains
  // entry is set at parent domain level
  // make sure it exists
  $parent_taxonomy = taxonomy_get_term_by_name($wsup['domain']['sitename'], $wsup['taxonomy']['product']->machine_name);
  if(empty($parent_taxonomy)){
    $parent_taxonomy = new stdClass();
    $parent_taxonomy->name = $wsup['domain']['sitename'];
    $parent_taxonomy->vid = $wsup['taxonomy']['product']->vid;
    taxonomy_term_save($parent_taxonomy);
  }
  $wsup['taxonomy_parent'] = current($parent_taxonomy);
  
  // we need a list of current items so we can identify those products that should be added/updated/deleted
  $wsup['current_nodes'] = bmb_product_nodes_by_domain_id($domain_id);
  
  // dispatcher 
  switch($method) {
    case 'bmbws':
      bmb_product_bmbws_import($wsup);
      break;
    case 'pim':
      bmb_product_pim_import($wsup);
      break;
    default:
      drupal_set_message('Second parameter unknown. Unsupported import method.', 'error');
      drupal_goto('/admin/config/bmb-product/settings');
  }
  
  // nodes that still have existed flag did not exist in the feed and should be deleted
  $arr_status = array();
  foreach($wsup['current_nodes'] as $nid => $status){
    $arr_status[$status][] = $nid;
    if($status == 'existed'){
      node_delete($nid);
    }
  }
  $str_status = 'BMB Product Update: ' . $wsup['domain']['sitename'] . ' (' . $method . ')<br>';
  if(isset($arr_status['added'])){
    $str_status .= 'Nodes added: ' . count($arr_status['added']) . '<br>';
  } else {
    $str_status .= 'Nodes added: 0<br>';
  }
  if(isset($arr_status['updated'])){
    $str_status .= 'Nodes updated: ' . count($arr_status['updated']) . '<br>';
  } else {
    $str_status .= 'Nodes updated: 0<br>';
  }
  if(isset($arr_status['existed'])){
    $str_status .= 'Nodes deleted: ' . count($arr_status['existed']) . '<br>';
  } else {
    $str_status .= 'Nodes deleted: 0<br>';
  }
  
  watchdog('BMB Product', t($str_status), NULL, WATCHDOG_INFO);
  if($run_from_ui == 1) {
    drupal_set_message($str_status);
  }
  //drupal_goto('/admin/config/bmb-product/settings');
}

// -- COMMON FUNCTIONS - START ------------------------------------------------------- //

/**
 * Fetch a list of node ids by domain  
 * 
 * @param $domain_id
 *   domain identifier of domain access module - integer
 * 
 * @return $arr
 *   array of nids
 */
function bmb_product_nodes_by_domain_id($domain_id){
  
  $query = db_select('node', 'n');
  $query->leftJoin('domain_access', 'da', 'n.nid = da.nid');
  $query->condition('da.gid', $domain_id, '=');
  $query->condition('n.type', 'bmb_product', '=');
  $query->fields('n', array('nid'));
  $result = $query->execute();
  
  $arr = array();
  foreach($result as $row){
    //ddl($row);
    $arr[$row->nid]= 'existed';
  }
  return $arr;
}

/**
 * return external info using curl
 * 
 * @param $import_info
 *   array -> url, username, password, etc. 
 * 
 * @return $arr
 *   array -> status, results
 */
function bmb_product_get_external_data($import_info = NULL) {
  if(is_null($import_info)) {
    return array(
      'status' => "error",
      'message' => "Incorrect parameters supplied to function _bmb_pim_get_external_info",
    );
  }
  
  /*print('4 - curl before<pre>');
  print_r($import_info);
  print('</pre><hr>');*/
  
  
  // curl process
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $import_info['url']);                // Set the url
  if(isset($import_info['params'])){
    curl_setopt($ch, CURLOPT_POSTFIELDS, $import_info['params']);      
  }
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);  
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);                    // Will return the response, if false it print the response
  curl_setopt($ch, CURLOPT_FAILONERROR, TRUE);
  //curl_setopt($ch, CURLOPT_VERBOSE, TRUE);
  //curl_setopt($ch, CURLOPT_HEADER, FALSE);
  if(isset($import_info['header_info'])){
    curl_setopt($ch, CURLOPT_HTTPHEADER, $import_info['header_info']);      
  }
  
  $result = curl_exec($ch);
  
  /*print('curl results<pre>');
  print_r($result);
  print('</pre><hr>');*/
  
  if($errno = curl_errno($ch)) {
    $error_message = curl_strerror($errno);
    $curl_error_message = "cURL error ({$errno}): {$error_message}";
  }
  
  // Closing
  curl_close($ch);
  
  if(isset($curl_error_message)) {
    return array(
      'status' => "error",
      'message' => "cURL Error: " . $curl_error_message,
    ); 
  } elseif ($result === false) {
    return array(
      'status' => "error",
      'message' => "cURL result is empty.",
    ); 
  }
  /*print('here - <br>');
  print($result);
  print('<hr>');*/
  
  return array(
    'status' => "success",
    'results' => json_decode($result, true),
  );
}

/**
 * @param array $product
 *   information defining a BMB Product
 * @param array $wsup
 *   array variable holding info on the overvall process. **passed by reference
 * 
 * @return none
 */
function bmb_product_save_product($product, &$wsup){
  
  /*print('product in node save<pre>');
  print_r($product);
  print('</pre><hr>');*/
  
  // verify if bmb product with current UPC already exists in system
  $nid = bmb_product_product_by_upc($product['upc']);
  
  $str_status = "";
  if($nid){
    // a node id with this UPC was found so update it
    
    $n = node_load($nid);
    $str_status = "updated";
    
  } else {
    //print('ADDING node with upc ' . $product['upc'] . '<br>');
    
    $n = new stdClass();
    $n->type = 'bmb_product';
    
    // adds: status=1; promote=1; sticky=0; uid=[current]; created=[timestamp]; revision=""; menu=[default array]
    node_object_prepare($n);
    
    // these fields unique to new node
    $n->uid = 1;
    $n->language = 'und'; // Or e.g. 'en' if locale is enabled
    $n->comment = 0; // 0 = comments disabled, 1 = read only, 2 = read/write
    
    $str_status = "added";
  }
  
  // common for both update and save -------------------------//
  if(!empty($product['title'])){
    $n->title = $product['title'];
  }
  
  if(!empty($product['description'])){
    $n->body['und'][0]['value'] = $product['description'];
  }
  
  if(!is_null($wsup['domain']['domain_id'])){
    $n->domains = array($wsup['domain']['domain_id'] => $wsup['domain']['domain_id']);
  }
  
  //send to affiliates
  $n->domain_site = FALSE;
  
  // import field => drupal field name
  $arr_mapping = array(
    'upc' => 'field_bp_upc',
    'UNFI_item' => 'field_bp_unfi_item',
    'ingredients' => 'field_bp_ingredients',
    'country' => 'field_bp_country_of_origin',
    'serving_size' => 'field_bp_serving_size',
    'servings_per_container' => 'field_bp_servings_per_container',
    'retail_size' => 'field_bp_retail_size',
    'primary_image' => 'field_bp_primary_image',
    'calories' => 'field_bp_calories',
    'calories_from_fat' => 'field_bp_calories_from_fat',
    'total_fat' => 'field_bp_total_fat',
    'pdv_total_fat' => 'field_bp_pdv_total_fat',
    'saturated_fat' => 'field_bp_saturated_fat',
    'pdv_saturated_fat' => 'field_bp_pdv_saturated_fat',
    'trans_fat' => 'field_bp_trans_fat',
    'cholesterol' => 'field_bp_cholesterol',
    'pdv_cholesterol' => 'field_bp_pdv_cholesterol',
    'sodium' => 'field_bp_sodium',
    'pdv_sodium' => 'field_bp_pdv_sodium',
    'carbohydrates' => 'field_bp_carbohydrates',
    'pdv_carbohydrates' => 'field_bp_pdv_carbohydrates',
    'fiber' => 'field_bp_fiber',
    'pdv_fiber' => 'field_bp_pdv_fiber',
    'sugars' => 'field_bp_sugars',
    'protein' => 'field_bp_protein',
    'vitamin_a' => 'field_bp_vitamin_a',
    'vitamin_c' => 'field_bp_vitamin_c',
    'calcium' => 'field_bp_calcium',
    'iron' => 'field_bp_iron',
    'pim_nid' => 'field_bp_pim_nid',
    'pim_created' => 'field_bp_pim_creation_date',
    'pim_changed' => 'field_bp_pim_change_date',
  );
  foreach($arr_mapping as $key => $value) {
    if(isset($product[$key])){
      $value_checked = $product[$key];
      $n->{$value}['und'][0]['value'] = $value_checked;
    }
  }
  
  // categories
  if(isset($product['category_info'])){
    $n->field_bp_product_category['und'] = $product['category_info'];
  }
  if(isset($product['attribute_category_info'])){
    $n->field_bp_product_attributes['und'] = $product['attribute_category_info'];
  }
  if(isset($product['allergen_category_info'])){
    $n->field_bp_product_allergens['und'] = $product['allergen_category_info'];
  }
  
  node_save($n);
  
  // reminder - passed in as reference
  $wsup['current_nodes'][$n->nid] = $str_status;
}

/**
 * 
 * @param int $upc
 *   The UPC of the product, UNFI unique product identifier
 * 
 * @return
 *   if found the entity_id (nid) of the product with this upc
 */
function bmb_product_product_by_upc($upc){
  
  $query = db_select('field_data_field_bp_upc', 'z');
  $query->fields('z', array('entity_id'));
  $query->condition('field_bp_upc_value', $upc, '=');
  $query->range(0,1);
  $result = $query->execute()->fetchAll(PDO::FETCH_ASSOC);
  
  if($result) {
    return $result[0]['entity_id'];
  } else {
    return NULL;
  } 
}

// -- COMMON FUNCTIONS - END -------------------------------------------------------- //

// -- BMBWS FUNCTIONS - BEGIN -------------------------------------------------------- //

function bmb_product_bmbws_import(&$wsup) {
  
  //URL to file is stored as vars setting
  $bmbws_file_url = variable_get('bmb_product_bmbws_url_' . $wsup['domain']['domain_id'], NULL);
  
  // parse the path above to get the file name to use for image path 
  $arr_image_temp = explode('/', $bmbws_file_url);
  $image_path_temp = str_replace('.json', '', end($arr_image_temp));
  $wsup['image_path'] = '/bmb_update_nodes/output/json/images/' . $image_path_temp . '/';
  
  
  // get data from file
  $product_feed = array();
  $product_feed['url'] = $bmbws_file_url;
  $products_returned = bmb_product_get_external_data($product_feed);
  if($products_returned['status'] == 'error'){
    drupal_set_message('There was a BMBWS error retrieving the file.', 'error');
    drupal_goto('/admin/config/bmb-product/settings');
  }
  
  // process each product record
  foreach($products_returned['results'] as $product) {
    
    //return taxonomy children - parent term is site
    $site_taxonomy_children = taxonomy_get_tree($wsup['taxonomy_parent']->vid, $wsup['taxonomy_parent']->tid);
    
    $product['current_taxonomy'] = $site_taxonomy_children;
    $product_normalized = bmb_product_normalize_input_bmbws($product, $wsup);
    
    // save or update node
    bmb_product_save_product($product_normalized, $wsup);
  }
}

function bmb_product_normalize_input_bmbws($product, $wsup){
  
  // trim each value
  $arr = array();
  foreach($product as $key => $value){
    if(gettype($value) != 'array'){
      $arr[$key] = htmlspecialchars_decode(trim($value));
    }
  }
  
  // add image
  $arr['primary_image'] = $wsup['image_path'] . $arr['upc'] . '.jpg';
  
  // product categorization bmb_pim_category
  // PWS import only supplied a single level category for products
  // if category does not exist add the category with parent of the site
  // **note category must be provided as an array to bmb_pim_create_node_save
  if(isset($product['category'])){
    foreach($product['current_taxonomy'] as $tax_item) {
      if(strtolower($tax_item->name) == strtolower($product['category'])){
        //$arr['category_info'][] = $tax_item;
        $arr['category_info'][] = array('tid' => $tax_item->tid);
        break;
      }
    }
    if(!isset($arr['category_info'])) {
      // no category info found so we add it then update info
      $new_term = new stdClass();
      $new_term->name = $product['category'];
      $new_term->vid = $wsup['taxonomy_parent']->vid;
      $new_term->parent = $wsup['taxonomy_parent']->tid;
      taxonomy_term_save($new_term);
      $arr['category_info'][] = array('tid' => $new_term->tid);
      $arr['new_category'] = 1;  
    }
  } // end product category
  
  // product attribute taxonomy
  if(isset($product['product_attributes'])) {
    
    // check first for single array with keys as properties
    if(isset($product['product_attributes']['display'])){
      $found_attribute_single = taxonomy_get_term_by_name($product['product_attributes']['display'], $wsup['taxonomy']['attributes']->machine_name);
      if(empty($found_attribute_single)){
        $new_attr = new stdClass();
        $new_attr->name = $product['product_attributes']['display'];
        $new_attr->vid = $wsup['taxonomy']['attributes']->vid;
        $new_attr->description = $product['product_attributes']['tooltip'];
        taxonomy_term_save($new_attr);
        $arr_current = $new_attr;
      } else {
         $arr_current = current($found_attribute_single);
      }
      $arr['attribute_category_info'][] = array('tid' => $arr_current->tid); 
    } else {
      // array of multiple items with numeric keys
      foreach($product['product_attributes'] as $prod_attr) {
        // check if term exists
        $found_attr = taxonomy_get_term_by_name($prod_attr['display'], $wsup['taxonomy']['attributes']->machine_name);
        if(empty($found_attr)){
          print('not found - ' . $prod_attr['display'] . '<br><hr>');
          $new_attr = new stdClass();
          $new_attr->name = $prod_attr['display'];
          $new_attr->vid = $wsup['taxonomy']['attributes']->vid;
          $new_attr->description = $prod_attr['tooltip'];
          taxonomy_term_save($new_attr);
          $arr_current = $new_attr;
        } else {
          $arr_current = current($found_attr);
        }
        $arr['attribute_category_info'][] = array('tid' => $arr_current->tid);
      } 
    }
  } // end attribute taxonomy
  
  // product allergen taxonomy
  if(isset($product['allergens'])) {
    // can be a single array with keys being properties or have multiple items with numeric indexes
    if(isset($product['allergens']['display'])){
      $found_allergen_single = taxonomy_get_term_by_name($product['allergens']['display'], $wsup['taxonomy']['allergens']->machine_name);
      if(empty($found_allergen_single)){
        $new_allergen = new stdClass();
        $new_allergen->name = $product['allergens']['display'];
        $new_allergen->vid = $wsup['taxonomy']['allergens']->vid;
        $new_allergen->description = $product['allergens']['tooltip'];
        taxonomy_term_save($new_allergen);
        $arr_allergen_current = $new_allergen;
      } else {
        $arr_allergen_current = current($found_allergen_single);
      }
      $arr['allergen_category_info'][] = array('tid' => $arr_allergen_current->tid);
    } else {
      // array of multiple values with numeric key index
      foreach($product['allergens'] as $prod_allergen) {
        // check if term exists
        $found_allergen = taxonomy_get_term_by_name($prod_allergen['display'], $wsup['taxonomy']['allergens']->machine_name);
        if(empty($found_allergen)){
          $new_allergen = new stdClass();
          $new_allergen->name = $prod_allergen['display'];
          $new_allergen->vid = $wsup['taxonomy']['allergens']->vid;
          $new_allergen->description = $prod_allergen['tooltip'];
          taxonomy_term_save($new_allergen);
          $arr_allergen_current = $new_allergen;
        } else {
          $arr_allergen_current = current($found_allergen);
        }
        $arr['allergen_category_info'][] = array('tid' => $arr_allergen_current->tid);
      }
    }
  }
  
  /*print('end of normalize<pre>');
  print_r($arr);
  print('</pre><hr>');
  return;*/
  
  return $arr;
}

// -- BMBWS FUNCTIONS - END -------------------------------------------------------- //

// -- PIM FUNCTIONS - BEGIN -------------------------------------------------------- //

function bmb_product_pim_import(&$wsup) {
  
  // retrieve pim domain id - saved in vars
  $pim_brand_id = variable_get('bmb_product_pim_siteid_' . $wsup['domain']['domain_id'], NULL);
  $wsup['pim_brand_id'] = $pim_brand_id;
  
  // authenticate with pim servers
  $auth_info = array();
  $auth_info['url'] = BMB_PRODUCT_PIM_BASE_URL . BMB_PRODUCT_PIM_AUTH_ENDPOINT;
  $auth_info['params'] = array('grant_type' => 'password', 'client_id' => 'default', 'username' => BMB_PRODUCT_PIM_USER, 'password' => BMB_PRODUCT_PIM_PASSWORD);
  $auth_returned = bmb_product_get_external_data($auth_info);
  
  /*print('11 - auth returned<pre>');
  print_r($auth_returned);
  print('</pre><hr>');*/
  
  
  
  if($auth_returned['status'] == 'error'){
    drupal_set_message(t('Unable to authenticate with the PIM.'), 'error');
    watchdog('BMB Product', t('Unable to authenticate with the PIM.'), NULL, WATCHDOG_ERROR);
    drupal_goto('/admin/config/bmb-product/settings');
  }
  $wsup['auth'] = $auth_returned['results'];
  
  /*print('333 - right before<pre>');
  print_r($wsup);
  print('</pre><hr>');*/
  
  $product_feed = array();
  //$product_feed['url'] = BMB_PRODUCT_PIM_BASE_URL . BMB_PRODUCT_PIM_PRODUCT_ENDPOINT;
  $product_feed['url'] = 'http://bmb-new.com/pim_api_products_from_test.txt';
  $product_feed['header_info'] = array('Authorization:Bearer ' . $wsup['auth']['access_token']);
  $product_feed['params'] = array('brand' => '1|' . $pim_brand_id);
  
  $products_returned = bmb_product_get_external_data($product_feed);
  
  /*print('5 - products returned<pre>');
  print_r($products_returned);
  print('</pre><hr>');*/
  
  foreach($products_returned['results']['results'] as $product){
    
    //return taxonomy children - parent term is site
    $site_taxonomy_children = taxonomy_get_tree($wsup['taxonomy_parent']->vid, $wsup['taxonomy_parent']->tid);
    
    $product['current_taxonomy'] = $site_taxonomy_children;
    $product_normalized = bmb_product_normalize_input_pim($product, $wsup);
    
    print('product normalized<pre>');
    print_r($product_normalized);
    print('</pre><hr>');
    
    
  }
}

/**
 * 
 * @param undefined $product
 * @param undefined $wsup
 * 
 * note - see bmb_product README.TXT for info on $arr values
 * 
 * @return
 */
function bmb_product_normalize_input_pim($product, $wsup){
  $arr = array();
  
  $arr['UNFI_item'] = $product['item_num'];    ////??????
  $arr['domain_id'] = $wsup['domain']['domain_id'];
  $arr['pim_nid'] = $product['nid'];
  $arr['pim_created'] = $product['created'];
  $arr['pim_changed'] = $product['changed'];
  $arr['country'] = current($product['country_of_origin']);
  $arr['upc'] = $product['upc'];
  $arr['title'] = $product['title'];
  $arr['primary_image'] = $product['primary_image']['renditions']['web_thumbnail'];
  $arr['description'] = $product['item_description'];
  $arr['ingredients'] = $product['ingredients_print'];
  $arr['retail_size'] = trim($product['item_size']) . ' ' . trim($product['item_size_uom']);
  $arr['serving_size'] = $product['nutrition_panel'][0]['serving_size_string'];
  $arr['servings_per_container'] = $product['nutrition_panel'][0]['estimated_servings'];
  $arr['calories'] = $product['nutrition_panel'][0]['calories_value'];
  $arr['calories_from_fat'] = $product['nutrition_panel'][0]['calories_from_fat_value'];
  $arr['total_fat'] = $product['nutrition_panel'][0]['total_fat_value'];
  $arr['trans_fat'] = $product['nutrition_panel'][0]['trans_fat_value'];
  $arr['saturated_fat'] = $product['nutrition_panel'][0]['saturated_fat_value'];
  $arr['cholesterol'] = $product['nutrition_panel'][0]['cholesterol_value'];
  $arr['sodium'] = $product['nutrition_panel'][0]['sodium_value'];
  $arr['carbohydrates'] = $product['nutrition_panel'][0]['total_carbohydrate_value'];
  $arr['fiber'] = $product['nutrition_panel'][0]['dietary_fiber_value'];
  $arr['sugars'] = $product['nutrition_panel'][0]['sugar_value'];
  $arr['protein'] = $product['nutrition_panel'][0]['protein_value'];
  $arr['vitamin_a'] = $product['nutrition_panel'][0]['vitamin_a_value'];
  $arr['vitamin_c'] = $product['nutrition_panel'][0]['vitamin_c_value'];
  $arr['calcium'] = $product['nutrition_panel'][0]['calcium_value'];
  $arr['iron'] = $product['nutrition_panel'][0]['iron_value'];
  $arr['pdv_total_fat'] = $product['nutrition_panel'][0]['total_fat_daily_value'];
  $arr['pdv_saturated_fat'] = $product['nutrition_panel'][0]['saturated_fat_daily_value'];
  $arr['pdv_cholesterol'] = $product['nutrition_panel'][0]['cholesterol_daily_value'];
  $arr['pdv_sodium'] = $product['nutrition_panel'][0]['sodium_daily_value'];
  $arr['pdv_carbohydrates'] = $product['nutrition_panel'][0]['total_carb_daily_value'];
  $arr['pdv_fiber'] = $product['nutrition_panel'][0]['dietary_fiber_daily_value'];
  
  // trim each value
  $arr_temp = array_map('trim', $arr);
  $arr = $arr_temp;
  
  // -- categories -- //
  
  // primary ?????
  
  // attributes - these are listed as single values so we will put together a list
  /*
  bpa_free
  [gluten_free] => Array([24962] => Gluten-Free Certification Program GFCP)
  [kosher_certifying_agency] => Array([25002] => KSA)
  [kosher_daily] => 
  [kosher_mbuf] => 
  [kosher_pareve] => 1
  [kosher_passover] =>  
  [non_gmo] => Array([27198] => Enrolled)
  [organic_attributes] => Array([24907] => >70%)
  [organic_certifier] => Array([24976] => BCS OKO-Garantie GMBH)
  [salt_content_attributes] => Array([23716] => No Salt Added, [23718] => Sodium Free)
  [veg_attributes] => Array([24911] => Vegetarian)
  [whole_grain_per_serving] => 0.1
  [fair_trade_certificate] => Array  - lots o stuff
  [gluten_free_certificate] => Array  - lots o stuff 
  [kosher_certificate] => Array
  [organic_certificate] => Array
  */
  
  // allergens in major_allergen_attributes
  if(isset($product['major_allergen_attributes'])){
    foreach($product['major_allergen_attributes'] as $allergen_key => $allergen_value){
      //print('key - ' . $allergen_key . ' | value - ' . $allergen_value . '<br>');
      $allergen_value = trim($allergen_value);
      $found_allergen = taxonomy_get_term_by_name($allergen_value, $wsup['taxonomy']['allergens']->machine_name);
      if(empty($found_allergen)){
        $new_allergen = new stdClass();
        $new_allergen->name = $allergen_value;
        $new_allergen->vid = $wsup['taxonomy']['allergens']->vid;
        taxonomy_term_save($new_allergen);
        $arr_allergen_current = $new_allergen;
      } else {
        $arr_allergen_current = current($found_allergen);
      }
      $arr['allergen_category_info'][] = array('tid' => $arr_allergen_current->tid);
    }
  }
  
  
  
  
  
  return $arr;
}

// -- PIM FUNCTIONS - END -------------------------------------------------------- //
























