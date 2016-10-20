

<?php if($content['field_add_anchor']['#items'][0]['value'] == 1): ?>
<a class="anchor" name="<?php print $content['field_panel_id']['#items'][0]['value']; ?>" data-magellan-destination="<?php print $content['field_panel_id']['#items'][0]['value']; ?>"></a>
<?php endif; ?>
<div id="<?php print $content['field_panel_id']['#items'][0]['value']; ?>" class="<?php print $content['field_panel_class']['#items'][0]['value']; ?>">
  <div class="<?php print $content['field_panel_class']['#items'][0]['value']; ?>-title"><h3><?php print $content['title']['#value']; ?></h3></div>
  <div class="<?php print $content['field_panel_class']['#items'][0]['value']; ?>-subtitle"><h4><?php print $content['field_subtitle']['#items'][0]['value']; ?></h4></div>
  <div class="<?php print $content['field_panel_class']['#items'][0]['value']; ?>-description"><?php print $content['field_description']['#items'][0]['value']; ?></div>
</div>

