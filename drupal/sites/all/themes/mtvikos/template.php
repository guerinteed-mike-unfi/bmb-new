<?php

 /**
 * Theme override for theme_menu_link()
 * Adds a unique ID class to all menu items.
 * 
 * overrides function in /themes/bootstrap/
 */
function mtvikos_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  
  // add ids to each menu item
  $this_title = strtolower($element['#title']);
  //Make alphanumeric (removes all other characters)
  $this_title = preg_replace("/[^a-z0-9 ]/", '', $this_title);
  //Clean up multiple dashes or whitespaces
  $this_title = preg_replace("/[\s-]+/", " ", $this_title);
  //Convert whitespaces and underscore to dash
  $this_title = preg_replace("/[\s_]/", "-", $this_title);
  
  // add id to element
  $element['#attributes']['id'][] = $this_title;
  
  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#title'] .= ' <span class="caret"></span>';
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}