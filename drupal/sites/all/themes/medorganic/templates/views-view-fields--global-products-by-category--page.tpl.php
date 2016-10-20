<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
 
 $m = $row->_field_data['nid']['entity']; 
 $this_alias = drupal_get_path_alias('node/'. $m->nid);
 
?>

<!-- @template: views-view-fields--global-products-by-category--page.tpl.php -->
<div id="product-box" class="product-box">
   <div id="product-box-container" class="product-box-container">
      <a href="/<?php print($this_alias); ?>">
        <img src="/sites/default/files/<?php print($m->field_bp_upc['und'][0]['value']); ?>.jpg">
      </a>
      <div class="product-title"><a href="/<?php print($this_alias); ?>"><?php print($m->title); ?></a></div>
      <ul class="product-icons">
         <li class="product-buy" title="Buy"><a href="http://www.bluemarblebrandsshop.com/cgi-sys/cgiwrap/ffblue/sc/order.cgi?storeid=*16fc824eb18b60f907a5b54f2c&amp;dbname=products&amp;sku=<?php print($m->field_bp_unfi_item['und'][0]['value']); ?>&amp;function=add" target="_blank"></a></li>
         <li class="product-locator" title="Product Locator"><a href="/med_organic_store_locator"></a></li>
         <li class="product-recipe" title="Recipes"><a href="/med_organic_recipes"></a></li>
         <li class="product-nutrition" id="nutrition_hover_Table" title="Nutrition Information">
            <a href="#" class="nutrition-hover"></a>
            <div class="nutrition-panel">
               <div class="close"></div>
               <div id="nutrinfo_chart">
                  <table width="200" cellpadding="2" cellspacing="0" align="center">
                     <tbody>
                        <tr>
                           <td colspan="3">
                              <div align="center"><span class="nutritional_heading">Nutritional Facts </span></div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <div class="field field-name-field-serving-size field-type-text field-label-inline clearfix">
                                 <div class="field-label">Serving Size:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_serving_size['und'][0]['value']); ?>                           
                                    </div>
                                 </div>
                              </div>
                              <div align="left"> </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <div class="field field-name-field-serving-per-container field-type-text field-label-inline clearfix">
                                 <div class="field-label">Serving Per Container:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_servings_per_container['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <div align="center"><img src="images/black_spacer.gif" width="100%" height="10"></div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <div align="left">
                                 <table width="190" border="0" cellspacing="0" cellpadding="0">
                                    <tbody>
                                       <tr>
                                          <td>
                                             <div class="field field-name-field-calories field-type-text field-label-inline clearfix">
                                                <div class="field-label">Calories:&nbsp;</div>
                                                <div class="field-items">
                                                   <div class="field-item even">
                                                      <?php print($m->field_bp_calories['und'][0]['value']); ?>
                                                   </div>
                                                </div>
                                             </div>
                                          </td>
                                          <td>
                                             <div class="field field-name-field-calories-from-fat field-type-text field-label-inline clearfix">
                                                <div class="field-label">Calories from Fat:&nbsp;</div>
                                                <div class="field-items">
                                                   <div class="field-item even">
                                                      <?php print($m->field_bp_calories_from_fat['und'][0]['value']); ?>
                                                   </div>
                                                </div>
                                             </div>
                                          </td>
                                       </tr>
                                    </tbody>
                                 </table>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <div align="center">
                                 <img src="images/black_spacer.gif" width="100%" height="5">
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3" align="right">
                              <strong>% Daily Value </strong>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="150" colspan="2" align="left">
                              <div class="field field-name-field-total-fat field-type-text field-label-inline clearfix">
                                 <div class="field-label">Total Fat:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_total_fat['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div class="field field-name-field-total-fat-percent field-type-text field-label-hidden">
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_pdv_total_fat['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="5">&nbsp;</td>
                           <td>
                              <div class="field field-name-field-saturated-fat field-type-text field-label-inline clearfix">
                                 <div class="field-label">Saturated Fat:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_saturated_fat['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div class="field field-name-field-saturated-fat-percent field-type-text field-label-hidden">
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_pdv_saturated_fat['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="5">&nbsp;</td>
                           <td>
                              <div class="field field-name-field-trans-fat field-type-text field-label-inline clearfix">
                                 <div class="field-label">Trans Fat:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_trans_fat['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td style="width: 146px">&nbsp;</td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="150" colspan="2">
                              <div class="field field-name-field-cholesterol field-type-text field-label-inline clearfix">
                                 <div class="field-label">Cholesterol:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_cholesterol['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div class="field field-name-field-cholesterol-percent field-type-text field-label-hidden">
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_pdv_cholesterol['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="150" colspan="2">
                              <div class="field field-name-field-sodium field-type-text field-label-inline clearfix">
                                 <div class="field-label">Sodium:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_sodium['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div class="field field-name-field-sodium-percent field-type-text field-label-hidden">
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_pdv_sodium['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="150" colspan="2">
                              <div class="field field-name-field-total-carbohydrates field-type-text field-label-inline clearfix">
                                 <div class="field-label">Carbohydrates:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_carbohydrates['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div class="field field-name-field-total-carb-percent field-type-text field-label-hidden">
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_pdv_carbohydrates['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="5">&nbsp;</td>
                           <td width="150">
                              <div class="field field-name-field-dietary-fiber field-type-text field-label-inline clearfix">
                                 <div class="field-label">Fiber:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_fiber['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div class="field field-name-field-dietary-fiber-percent field-type-text field-label-hidden">
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_pdv_fiber['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="5">&nbsp;</td>
                           <td width="150">
                              <div class="field field-name-field-sugar field-type-text field-label-inline clearfix">
                                 <div class="field-label">Sugars:&nbsp;</div>
                                 <div class="field-items">
                                    <div class="field-item even">
                                       <?php print($m->field_bp_sugars['und'][0]['value']); ?>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div align="right"></div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td width="150" colspan="2">
                              <div align="left">
                                 <div class="field field-name-field-protein field-type-text field-label-inline clearfix">
                                    <div class="field-label">Protein:&nbsp;</div>
                                    <div class="field-items">
                                       <div class="field-item even">
                                          <?php print($m->field_bp_protein['und'][0]['value']); ?>
                                       </div>
                                    </div>
                                 </div>
                              </div>
                           </td>
                           <td align="right" style="width: 146px">
                              <div align="right">
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="5">
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <div class="field field-name-field-vitamin-a field-type-text field-label-inline clearfix">
                                 <div style="float: left;width: 45%;">
                                    <div class="field-label">Vitamin A:&nbsp;</div>
                                    <div class="field-items">
                                       <div class="field-item even">
                                          <?php print($m->field_bp_vitamin_a['und'][0]['value']); ?>%
                                       </div>
                                    </div>
                                 </div>
                                 <div class="field-items-dot" style="width: 10%;">
                                    <div class="field-item even">
                                       •
                                    </div>
                                 </div>
                                 <div style="float:right;text-align: right;width: 45%;">
                                    <div class="field-label" style="float: right;">Vitamin C:&nbsp;
                                       <?php print($m->field_bp_vitamin_c['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <img src="images/black_spacer.gif" width="100%" height="1">
                           </td>
                        </tr>
                        <tr>
                           <td colspan="3">
                              <div class="field field-name-field-vitamin-a field-type-text field-label-inline clearfix">
                                 <div style="float: left;width: 45%;">
                                    <div class="field-label">Calcium:&nbsp;</div>
                                    <div class="field-items">
                                       <div class="field-item even">
                                          <?php print($m->field_bp_calcium['und'][0]['value']); ?>%
                                       </div>
                                    </div>
                                 </div>
                                 <div class="field-items-dot" style="width: 10%;">
                                    <div class="field-item even">
                                       •
                                    </div>
                                 </div>
                                 <div style="float:right;text-align: left;width: 45%;">
                                    <div class="field-label" style="float: right;">Iron:&nbsp;
                                       <?php print($m->field_bp_iron['und'][0]['value']); ?>%
                                    </div>
                                 </div>
                              </div>
                           </td>
                        </tr>
                     </tbody>
                  </table>
               </div>
               <div id="nutrinfo_summary">
                  <h2 align="left">
                     <span id="lblIng">Ingredients</span>
                  </h2>
                  <p align="left"></p>
                  <div class="field field-name-field-ingredients field-type-text-long field-label-hidden">
                     <div class="field-items">
                        <div class="field-item even">
                           <?php print($m->field_bp_ingredients['und'][0]['value']); ?>
                        </div>
                     </div>
                  </div>
                  <div class="field field-name-field-ingredients field-type-text-long field-label-hidden">
                     <div class="field-items">
                        <div class="field-item even" style="text-transform: uppercase;">
                           Distributed by<br>Mediterranean Organic<br>313 Iron Horse Way<br>Providence, RI 02908 USA
                        </div>
                     </div>
                  </div>
                  <div class="field field-name-field-ingredients field-type-text-long field-label-hidden">
                     <div class="field-items">
                        <div class="field-item even" style="text-transform: uppercase;">
                           Certified Organic By<br> Quanlity Assurance<br>International (QAI)<br>San Diego, CA 92122 USA
                        </div>
                     </div>
                  </div>
                  <div class="field field-name-field-ingredients field-type-text-long field-label-hidden">
                     <div class="field-items">
                        <div class="field-item even" style="text-transform: uppercase;">
                           <img src="images/certified_organic_logo.png">
                        </div>
                     </div>
                  </div>
               </div>
               <div class="nutrition-disclaimer">
                  NCW 2.1<br>Always use the consumer package for nutritional information as formula and ingredient changes may occur at any time and may not match the website.
               </div>
            </div>
         </li>
      </ul>
   </div>
</div>