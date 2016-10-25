<?php 
//set all variables for each
// print_r($row);  -also $view
$image_path = file_create_url($row->_field_data['nid']['entity']->field_image_common['und'][0]['uri']);
$cta_url = $row->_field_data['nid']['entity']->field_click_through_url['und'][0]['value'];
$open_in_new_window = $row->_field_data['nid']['entity']->field_open_in_new_window['und'][0]['value'];
$node_description = $row->_field_data['nid']['entity']->body['und'][0]['value'];

//get slide #
for($x=0; $x<=count($view->result); $x++){
  if($view->result[$x]->nid == $row->nid){
    $slide_number = $x + 1;
    break;
  }
}
?>
<img typeof="foaf:Image" class="img-responsive" src="<?php print $image_path; ?>">
<div id="carousel-caption-<?php print $slide_number; ?> item-nid-<?php print $row->nid; ?>" class="carousel-caption">

  <a href="/<?php print $cta_url; ?>"<?php if($open_in_new_window == 1){ print(' target="_blank"'); } ?>>
    <?php if (!empty($row->node_title)): ?>
      <h3 class="carousel-title"><?php print $row->node_title ?></h3>
    <?php endif ?>
    
    <?php if (!empty($node_description)): ?>
      <div class="carousel-description">
        <p><?php print $node_description ?></p>
      </div>
    <?php endif ?>
   </a>
</div>