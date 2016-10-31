<?php 
//set all variables for each
// print_r($row);  -also $view
ddl($row);

$slide_title = $row->field_field_slide_title[0]['rendered']['#markup'];
$display_text_1 = $row->field_body[0]['rendered']['#markup'];
$display_text_2 = $row->field_field_display_text_2[0]['rendered']['#markup'];

// get image info for common image
$image_path = file_create_url($row->field_field_image_common[0]['rendered']['#item']['uri']);
$image_alt = $row->field_field_image_common[0]['rendered']['#item']['alt'];
$open_in_new_window = ($row->field_field_open_in_new_window[0]['raw']['value'] == 0 ? '' : ' target="_blank"');

// determines what is clickable -> None, Whole Slide or Diplay Text
$clickable_area = $row->field_field_clickable_area[0]['raw']['value'];

// click through URL 
$click_through_url = $row->field_field_click_through_url[0]['rendered']['#markup'];

$anchor_opening = "";
if($clickable_area != 'None' && !empty($click_through_url)) {
  $anchor_opening = '<a href="';
  $anchor_opening .= $click_through_url . '"';
  $anchor_opening .= ' ' . $open_in_new_window . '>';
}

//get slide #
for($x=0; $x<=count($view->result); $x++){
  if($view->result[$x]->nid == $row->nid){
    $slide_number = $x + 1;
    break;
  }
}
?>
<?php if ($clickable_area == "Whole Slide") {
  print $anchor_opening;
}
?>

<img typeof="foaf:Image" class="img-responsive" src="<?php print $image_path; ?>">

<?php if ($clickable_area == "Display Text") {
  print $anchor_opening;
}
?>

<div id="carousel-caption-<?php print $slide_number; ?> item-nid-<?php print $row->nid; ?>" class="carousel-caption">

    <?php if (!empty($slide_title)): ?>
      <?php print $slide_title; ?>
    <?php endif ?>
    
    <?php if (!empty($display_text_1)): ?>
      <?php print $display_text_1; ?>
    <?php endif ?>
    
    <?php if (!empty($display_text_2)): ?>
      <?php print $display_text_2; ?>
    <?php endif ?>
    
</div>

<?php if ($clickable_area != "None"): ?>
  </a>
<?php endif; ?>