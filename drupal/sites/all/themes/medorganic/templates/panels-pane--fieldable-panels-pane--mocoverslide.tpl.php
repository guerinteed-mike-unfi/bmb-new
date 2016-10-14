<!--<pre>
<?php //print_r($content); ?>
</pre>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php //print render($title_suffix); ?>
  <?php //print render($content); ?>
</div>-->
<?php 
$target_string = "";
if($content['field_open_in_new_window']['#items'][0]['value'] == 1) {
  $target_string = 'target="_blank" ';
}
?>
<div class="mo_slide_wrapper" style="background: url(<?php print file_create_url($content['field_background_image'][0]['#item']['uri']); ?>) no-repeat top center;">
  <div class="mo_slide_text">
    <p><a href="<?php print $content['field_click_through_url']['#items'][0]['value']; ?>"<?php print $target_string; ?>><?php print $content['field_display_text']['#items'][0]['value']; ?></a></p>
    
  </div>
</div>

<?php

?>