<?php
error_reporting(E_ALL & ~E_NOTICE & ~E_WARNING & ~ E_PARSE);

function PwsGetXml($path) {
    $ch = curl_init();
    
    curl_setopt($ch, CURLOPT_URL,$path);
    curl_setopt($ch, CURLOPT_FAILONERROR,1);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION,1);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_NOSIGNAL, 1);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
    
    $foo = curl_exec($ch);

    $curl_errno = curl_errno($ch);
    $curl_error = curl_error($ch);
    curl_close($ch);
    $pattern = "/<NewDataSet(.*)NewDataSet>/s";
    preg_match($pattern, $foo, $matches);
    if( is_array($matches) && array_key_exists(0, $matches) ) {    
      if($matches[0]!=""){
        $xml = $matches[0];
        $xml = str_replace('xmlns=""', '', $xml);
        $xml = str_replace('diffgr:', '', $xml);
        $xml = str_replace('msdata:', '', $xml);
        $xml = str_replace('Vegetarian Entrees and Side Dishes', 'Entrees and Side Dishes', $xml);
        // And add the XML header
        $xml = "<?xml version='1.0'?>".$xml;
        $xml_object = new SimpleXMLElement($xml); 
        //print $xml_object;
        $json = json_encode($xml_object);
        return $json;
    }
 }
}

function PwsGetCategoryNamesByBrand($brand){
    $url = "https://bmbws.unfi.com/BMBPWS.asmx/BMBGetCategoryNamesByBrand?Brand=".$brand;
    return PwsGetXml($url);
}

function PwsGetProductList($brand, $catId){
    global $pws_base_url;
    // https://10.1.93.34/BMBPWS.asmx/BMBGetProductList?Brand=koyo&CatID=34
    $url = "https://bmbws.unfi.com/BMBPWS.asmx/BMBGetProductList"
        ."?Brand=" .$brand
        ."&CatID=".$catId;
    
    return PwsGetXml($url);
}   

function PwsGetProductDetails($upc){
    global $pws_base_url;
    // https://10.1.93.34/BMBPWS.asmx/BMBGetProductList?Brand=koyo&CatID=34
    $url = "https://bmbws.unfi.com/BMBPWS.asmx/BMBGetProductDetails"
        ."?upc=" .$upc;
    
    return PwsGetXml($url);
}

function PwsGetProductAttributes($upc){
    global $pws_base_url;
    // https://10.1.93.34/BMBPWS.asmx/BMBGetProductList?Brand=koyo&CatID=34
    $url = "https://bmbws.unfi.com/BMBPWS.asmx/BMBGetAttributesbyUPC"
        ."?upc=" .$upc;
    
    return PwsGetXml($url);
}

function PwsGetProductAllergens($upc){
    global $pws_base_url;
    // https://10.1.93.34/BMBPWS.asmx/BMBGetProductList?Brand=koyo&CatID=34
    $url = "https://bmbws.unfi.com/BMBPWS.asmx/BMBGetAllergensbyUPC"
        ."?upc=" .$upc;
    
    return PwsGetXml($url);
} 
      
function PwsGetProductImage($upc){
    global $pws_base_url;
    // https://10.1.93.34/BMBPWS.asmx/BMBGetProductList?Brand=koyo&CatID=34
    $url = "https://bmbws.unfi.com/BMBPWS.asmx/BMBGetProductImage"
        ."?upc=" .$upc;
    
    return PwsGetXml($url);
}

/**
* 
* Returns the string for the web service 
* 
* @param undefined $site
* 
* @return
*/
function site_web_service_name($site = null) {
  if( !isset($site) ) {
     return null;
  }
  
  switch($site){
    case "ahlaska":
      $site = "Ah!Laska";
      break;
    case "field_day":
      $site = "field%20day";
      break;
    case "fwf":
      $site = "Fantastic%20World%20Foods";
      break;
    case "koyo":
      $site = "Koyo";
      break;    
    case "med_organic":
      $site = "mediterranean%20organic";
      break;
    case "old_wessex":
      $site = "old%20wessex";
      break;
    case "rising_moon":
      $site = "Rising%20Moon";
      break;
    case "harvest_bay":
      $site = "harvest%20bay";
      break; 
    case "a_vogel":
      $site = "a%20vogel";
      break;
    case "mt_vikos":
      $site = "mt%20vikos";
      break;
    case "tumaros":
      $site = "tumaros";
      break;
    case "woodstock":
      $site = "woodstock";
      break;   
  }
  return $site;
}

function base64_to_jpeg($base64_string, $output_file) {
    $ifp = fopen($output_file, "wb"); 

    $data = explode(',', $base64_string);

    fwrite($ifp, base64_decode($data[1])); 
    fclose($ifp); 

    return $output_file; 
}

// magic starts here -------------------------------- //

$current_directory = getcwd();

print('<h1>Update Product Information</h1>');

flush();

if(isset($_POST) && is_array($_POST['filename'])) {
  
  $current_directory = getcwd();
  
  $values_filename = $_POST['filename'];
  foreach($values_filename as $site_name ) {
    
    print('<h2>Updating ' . $site_name . '</h2>');

    // return the site name needed by web service
    $ws_name = site_web_service_name($site_name);
    
    $cat_by_brand = PwsGetCategoryNamesByBrand($ws_name);
    
    //parse json File for categories
    $arr = json_decode($cat_by_brand);
    
    $arr_categories = array();
    if(gettype($arr->Table) == 'array') {
      foreach($arr->Table as $cat_values){
        //print_r($cat_value);
        $arr_categories[] = $cat_values->CategoryID;
      }
    } elseif(gettype($arr->Table) == 'object') {
      $arr_categories[] = $arr->Table->CategoryID;
    }
    
    $all_products = "";
    foreach($arr_categories as $cat_value){
      //print_r($cat_value);
      //$cat_value = $cat_values->CategoryID;
      
      $prod_info = NULL;
      $prod_info_serialized = NULL;
      $prod_item = NULL;
      
      $prod_info = PwsGetProductList($ws_name, $cat_value);
      
      $all_products .= $prod_info;
    }
    
    //deal will all products list
    $all_products = str_replace('{"Table":{"@attributes":', '{"Table":[{"@attributes":', $all_products);
    $all_products = str_replace(']}{"Table":[', ',', $all_products);
    $all_products = str_replace(']}{"Table":', ',', $all_products);
    $all_products = str_replace('}{"Table":[', ',', $all_products);
    
    $all_products_decoded = json_decode($all_products);
    
    //loop through the all products list so we can get UPC to get product info from web services
    $arr_products = array();
    foreach($all_products_decoded->Table as $product) {
      //print($product->UPC);
      
      $current_upc = $product->UPC;
      
      $arr_temp['upc'] = $product->UPC;
      $arr_temp['title'] = $product->Product_Name;
      if(!empty($product->Product_Description)){
        if(gettype($product->Product_Description) != 'object'){
          $arr_temp['description'] = $product->Product_Description;
        } else {
          $arr_temp['description'] = "NA";
        }
      } else {
        $arr_temp['description'] = "NA";
      }
      
      
      $arr_temp['category'] = $product->Category_Name;
      
      
      // product details
      $prod_descript = PwsGetProductDetails($current_upc);
      $prod_descript_decoded = json_decode($prod_descript);
      
      $arr_temp['ingredients'] = $prod_descript_decoded->Table->Ingredients;
      if(is_string($prod_descript_decoded->Table->ServingSize)){
        $arr_temp['serving_size'] = $prod_descript_decoded->Table->ServingSize;
      } else {
        $arr_temp['serving_size'] = "NA";
      }
      if(is_string($prod_descript_decoded->Table->ServingSize)){
        $arr_temp['servings_per_container'] = $prod_descript_decoded->Table->ServingsPerContainer;
      } else {
        $arr_temp['servings_per_container'] = "NA";
      }
      $arr_temp['calories'] = $prod_descript_decoded->Table->Calories;
      $arr_temp['calories_from_fat'] = $prod_descript_decoded->Table->CaloriesfromFat;
      $arr_temp['total_fat'] = $prod_descript_decoded->Table->TotalFat;
      $arr_temp['saturated_fat'] = $prod_descript_decoded->Table->SaturatedFat;
      $arr_temp['cholesterol'] = $prod_descript_decoded->Table->Cholesterol;
      $arr_temp['sodium'] = $prod_descript_decoded->Table->Sodium;
      $arr_temp['carbohydrates'] = $prod_descript_decoded->Table->TotalCarbohydrates;
      $arr_temp['fiber'] = $prod_descript_decoded->Table->DietaryFiber;
      $arr_temp['sugars'] = $prod_descript_decoded->Table->Sugar;
      $arr_temp['protein'] = $prod_descript_decoded->Table->Protein;
      $arr_temp['vitamin_a'] = $prod_descript_decoded->Table->VitaminA;
      $arr_temp['vitamin_c'] = $prod_descript_decoded->Table->VitaminC;
      $arr_temp['calcium'] = $prod_descript_decoded->Table->Calcium;
      $arr_temp['iron'] = $prod_descript_decoded->Table->Iron;
      $arr_temp['pdv_total_fat'] = $prod_descript_decoded->Table->PDVTotalFat;
      $arr_temp['pdv_saturated_fat'] = $prod_descript_decoded->Table->PDVSaturatedFat;
      $arr_temp['pdv_cholesterol'] = $prod_descript_decoded->Table->PDVCholesterol;
      $arr_temp['pdv_sodium'] = $prod_descript_decoded->Table->PDVSodium;
      $arr_temp['pdv_carbohydrates'] = $prod_descript_decoded->Table->PDVTotalCarbohydrate;
      $arr_temp['pdv_fiber'] = $prod_descript_decoded->Table->PDVDietaryFiber;
      $arr_temp['UNFI_item'] = $prod_descript_decoded->Table->UNFIItemNo;
      $arr_temp['trans_fat'] = $prod_descript_decoded->Table->Transfat;
      /*
  country_of_origin
  certified_organic
  */
      
      
      // product attributes
      $prod_attributes = PwsGetProductAttributes($current_upc);
      $prod_attributes_decoded = json_decode($prod_attributes);
      /*print('attributes --- ' . $current_upc . '<pre>');
      print_r($prod_attributes_decoded->Table);
      print('<pre><hr>');*/
      $arr_attributes = array();
      //print('<br>attribute type - ' . gettype($prod_attributes_decoded->Table) . ' - ' . $current_upc);
      if(gettype($prod_attributes_decoded->Table) == 'object'){
        /*print('<br>attr object<pre>');
        print_r($prod_attributes_decoded->Table);
        print('</pre>');*/
        $arr_attr_temp = array();
        $arr_attr_temp['display'] = $prod_attributes_decoded->Table->DisplayName;
        $arr_attr_temp['tooltip'] = $prod_attributes_decoded->Table->tooltip;
        $arr_temp['product_attributes'] = $arr_attr_temp;
      } elseif(gettype($prod_attributes_decoded->Table) == 'array'){
        foreach($prod_attributes_decoded->Table as $attr) {
          $arr_attr_temp = array();
          $arr_attr_temp['display'] = $attr->DisplayName;
          $arr_attr_temp['tooltip'] = $attr->tooltip;
          $arr_attributes[] = $arr_attr_temp;
        }
        $arr_temp['product_attributes'] = $arr_attributes;
      } else {
        $arr_temp['product_attributes'] = NULL;
      }
      

      // product Image
      $prod_image = PwsGetProductImage($current_upc);
      $prod_image_decode = json_decode($prod_image);
      $str_image = $prod_image_decode->Table->IMG_UNFI_IMAGE;
      //print('<br>image - ' . $str_image . '<hr>');
      
      $image_file = fopen($current_directory . "\\output\\images\\" . $site_name . '\\' . $current_upc . ".jpg", "w") or die("1Unable to open file!");
      fwrite($image_file, base64_decode($str_image));
      fclose($image_file);

      
      // product allergens
      $prod_allergens = PwsGetProductAllergens($current_upc);
      $prod_allergens_decoded = json_decode($prod_allergens);
      //print('<br>allergen type - ' . gettype($prod_allergens_decoded->Table) . ' - ' . $current_upc);
      
       $arr_allergens = array();
      if(gettype($prod_allergens_decoded->Table) == 'object'){
        $arr_allergens_temp = array();
        $arr_allergens_temp['display'] = $prod_allergens_decoded->Table->DisplayName;
        $arr_allergens_temp['tooltip'] = $prod_allergens_decoded->Table->tooltip;
        $arr_allergens[] = $arr_allergens_temp;
      } elseif(gettype($prod_allergens_decoded->Table) == 'array'){
        $arr_allergens = array();
        foreach($prod_allergens_decoded->Table as $attr) {
          $arr_allergens_temp = array();
          $arr_allergens_temp['display'] = $attr->DisplayName;
          $arr_allergens_temp['tooltip'] = $attr->tooltip;
          $arr_allergens[] = $arr_allergens_temp;
        }
        $arr_temp['allergens'] = $arr_allergens_temp;
      } else {
        $arr_temp['allergens'] = NULL;
      }
    
      //add to main product array
      $arr_products[] = $arr_temp;

  }
  
  print('<br><br>all products --- <pre>');
  print_r($arr_products);
  print('<pre><hr>');
  
  $arr_product_to_json = json_encode($arr_products);
  
  
  $json_file = fopen($current_directory . "\\output\\json\\" . $site_name . ".json", "w") or die("8Unable to open file!");
  fwrite($json_file, $arr_product_to_json);
  fclose($json_file);
  
}

}


?>