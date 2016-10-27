<?php
/**
 * @file
 * The primary PHP file for the Drupal Bootstrap base theme.
 *
 * This file should only contain light helper functions and point to stubs in
 * other files containing more complex functions.
 *
 * The stubs should point to files within the `./includes` folder named after
 * the function itself minus the theme prefix. If the stub contains a group of
 * functions, then please organize them so they are related in some way and name
 * the file appropriately to at least hint at what it contains.
 *
 * All [pre]process functions, theme functions and template files lives inside
 * the `./templates` folder. This is a highly automated and complex system
 * designed to only load the necessary files when a given theme hook is invoked.
 *
 * Visit this project's official documentation site, http://drupal-bootstrap.org
 * or the markdown files inside the `./docs` folder.
 *
 * @see _bootstrap_theme()
 */

/**
 * Include common functions used through out theme.
 */
//include_once dirname(__FILE__) . '/includes/common.inc';

/**
 * Include any deprecated functions.
 */
//bootstrap_include('bootstrap', 'includes/deprecated.inc');

/**
 * Implements hook_theme().
 *
 * Register theme hook implementations.
 *
 * The implementations declared by this hook have two purposes: either they
 * specify how a particular render array is to be rendered as HTML (this is
 * usually the case if the theme function is assigned to the render array's
 * #theme property), or they return the HTML that should be returned by an
 * invocation of theme().
 *
 * @see _bootstrap_theme()
 */
/*function medorganic_theme(&$existing, $type, $theme, $path) {
  bootstrap_include($theme, 'includes/registry.inc');
  return _bootstrap_theme($existing, $type, $theme, $path);
}*/

/**
 * Clear any previously set element_info() static cache.
 *
 * If element_info() was invoked before the theme was fully initialized, this
 * can cause the theme's alter hook to not be invoked.
 *
 * @see https://www.drupal.org/node/2351731
 */
//drupal_static_reset('element_info');

/**
 * Declare various hook_*_alter() hooks.
 *
 * hook_*_alter() implementations must live (via include) inside this file so
 * they are properly detected when drupal_alter() is invoked.
 */
//bootstrap_include('bootstrap', 'includes/alter.inc');

 /**
 * Theme override for theme_menu_link()
 * Adds a unique ID class to all menu items.
 * 
 * Returns HTML for a menu link and submenu.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_menu_link()
 *
 * @ingroup theme_functions
 */
function medorganic_menu_link(array $variables) {
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

function medorganic_preprocess_panels_pane(&$variables) {
  //ddl($variables);
  
/*  // fieldable panel panes
  if ($variables['pane']->type == 'fieldable_panels_pane') {
    
    if($variables['content']['#bundle'] == 'medorganic_front_cover_image_pane'){
      drupal_add_css(drupal_get_path('theme', 'medorganic') . '/css/fieldable-panels-pane--medorganic_front_cover_image_pane.css');
    }
    
  }*/
  
}




















