<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<!-- @template: views-view-unformated--global-products-by-category--page.tpl.php -->
<?php if (!empty($title)): 
  $this_title = trim(str_replace('Organic', '', $title)); 
  $this_name = preg_replace("/[^A-Za-z0-9 ]/", '', htmlspecialchars_decode($this_title));
  $this_name = strtolower($this_name);
  $this_name = str_replace('  ', ' ', $this_name);
  $this_name = str_replace(' ', '-', $this_name);
  $zebra_color = ($zebra == 'odd') ? 'purple' : 'green';
  $zebra_color_id = ($zebra == 'odd') ? 'ede6f1' : 'f0f3e3';
?>
<div style="display: inline-block;width: 100%;background-color:#<?php print($zebra_color_id); ?>;">
  <a class="anchor" name="<?php print($this_name); ?>" data-magellan-destination="<?php print($this_name); ?>"></a>
  <div class="page_banner_<?php print($zebra_color); ?>">
    <div class="page_banner_text_<?php print($zebra_color); ?>">
      <p class="quickpen">Organic</p> <p class="lieb-doris"><?php print $this_title; ?></p>
    </div>
  </div>
  <?php endif; ?>
  <div id="product-grid" class="product-grid">
  <?php foreach ($rows as $id => $row): ?>
      <?php print($row); ?>
  <?php endforeach; ?>
  </div>
</div>
