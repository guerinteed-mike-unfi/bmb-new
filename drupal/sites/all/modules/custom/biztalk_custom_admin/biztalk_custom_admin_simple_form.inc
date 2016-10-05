<?php

/**
 * Upon visiting a webform's BizTalk configuration page, create rows for headers
 * @param int $nid - the node id of the webform being configured
 * @param int $bid - in case this module is extended to go beyond Contact Us forms, that unique ID
 *
 * Called at the top of biztalk_webform()
 */
function populate_for_webform($nid, $bid) {
  $query = db_select('biztalk_header', 'h');
  $query->condition('h.bid', $bid)
        ->fields('h', array('hid'));
  $results = $query->execute()->fetchAll();

  foreach ($results as $idx => $result) {
    $query = db_select('biztalk_map_component', 'b');
    $query->condition('b.nid', $nid)
          ->condition('b.hid', $result->hid)
          ->fields('b', array('nid'))
          ->orderBy('hid');
    $results = $query->execute();
    $count = $results->rowCount();
    if (!$count) {
      db_insert('biztalk_map_component')->fields(
        array(
          'nid' => $nid,
          'hid' => $result->hid,
          // 'weight' => $idx,
      ))->execute();
    }
  }
}

/**
 * Returns array of options for select list of all webform's components
 * @param int $webform_nid - the node id of the webform being configured, passed in via hook_menu
 */
function get_component_options($webform_nid) {
  // query for the components
  $query = db_select('webform_component', 'wc');
  $query->condition('wc.nid', $webform_nid)
        ->fields('wc', array('cid', 'name'));
  $results = $query->execute()->fetchAll();

  $options = array('- None -' => '- None -');
  foreach ($results as $result) {
    $options[$result->cid] = $result->name;
  }
  return $options;
}

/**
 * Returns query results of all the rows for the draggable table (except the last "add new" row)
 * @param int $nid - the node id of the webform being configured
 * @param int $bid - in case this module is extended to go beyond Contact Us forms, that unique ID
 */
function get_rows_for_webform($nid, $bid) {
  $query = db_select('biztalk_header', 'h');
  $query->leftJoin('biztalk_map_component', 'c', 'c.hid = h.hid AND c.nid = :nid', array(':nid' => $nid));
  $bid = variable_get('biztalk_bid', 1);
  $query->condition('h.bid', $bid)
        ->fields('h', array('hid', 'bid', 'human'))
        ->fields('c', array('nid', 'cid', 'weight'))
        ->orderBy('weight')
        ->orderBy('hid');
  return $query->execute()->fetchAll();
}

/**
 * Create form
 * Called from hook_menu
 */
function biztalk_webform($form, &$form_state, $webform_nid) {
  $nid = arg(3);
  $bid = variable_get('biztalk_bid', 1);

  // in the very beginning we check to see if there are entries for this webform nid, if there are not we'll add default rows
  populate_for_webform($nid, $bid);

  $form = array();
  $form['biztalk_table']['#tree'] = TRUE; // for draggable table

  // get an array of options to populate select list
  $options = get_component_options($webform_nid);

  // get rows from the database to build the draggable table
  $results = get_rows_for_webform($nid, $bid);

  $form["biztalk-enabled-$bid-$nid"] = array(
    '#type' =>'checkbox',
    '#title' => t('Include this webform in periodic CSV export.'),
    '#default_value' => variable_get("biztalk-enabled-$bid-$nid", TRUE),
  );
  foreach ($results as $i => $result) {
    $cid = (property_exists($result, 'cid')) ? $result->cid : NULL;
    $bid = (property_exists($result, 'bid')) ? $result->bid : NULL;
    $hid = (property_exists($result, 'hid')) ? $result->hid : NULL;
    $weight = (property_exists($result, 'weight') && $result->weight != NULL) ? $result->weight : $i;
    $human = (property_exists($result, 'human')) ? $result->human : NULL;

    $form['biztalk_table'][$i]= array(
      'wf_field' => array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => ($cid) ? $cid : '- None -',
      ),
      'maps_to' => array(
        '#type' => 'textfield',
        '#default_value' => $human,
      ),
      'bid' => array(
        '#type' => 'textfield',
        '#default_value' => $bid,
        '#access' => FALSE,
      ),
      'nid' => array(
        '#type' => 'textfield',
        '#default_value' => $nid,
        '#access' => FALSE,
      ),
      'hid' => array(
        '#type' => 'textfield',
        '#default_value' => $hid,
        '#access' => FALSE,
      ),
      'cid' => array(
        '#type' => 'textfield',
        '#default_value' => $cid,
        '#access' => FALSE,
      ),
      'add_remove' => array(
        '#title' => 'Remove',
        '#type' => 'submit',
        '#name' => "remove-$bid-$nid-$hid",
        '#value' => 'Remove',
      ),
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => $weight,
        '#delta' => 100,
        '#title_display' => 'invisible',
      ),
    );
    // dpm($weight, 'weight');
    $weight++;
  }

  // Make a 'new' row
  $new_row = array(
    'wf_field' => array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => '- None -',
    ),
    'maps_to' => array(
      '#type' => 'textfield',
      '#default_value' => '',
      '#description' => 'Leave blank unless adding new mapping.',
    ),
    'bid' => array(
      '#type' => 'textfield',
      '#default_value' => $bid,
      '#access' => FALSE,
    ),
    'nid' => array(
      '#type' => 'textfield',
      '#default_value' => arg(3),
      '#access' => FALSE,
    ),
    'weight' => array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $weight+1,
      '#delta' => 100,
      '#title_display' => 'invisible',
    ),
  );

  // Use array_push to make sure it's at the end of the table
  array_push($form['biztalk_table'], $new_row);

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'), '#name' => 'save');
  return $form;
}

/**
 * Implementation defined by hook_theme in .module file
 */
function theme_biztalk_webform($variables) {
  $nid = arg(3);
  $form = $variables['form'];
  $rows = array();
  foreach (element_children($form['biztalk_table']) as $id) {
    $form['biztalk_table'][$id]['weight']['#attributes']['class'] = array('custom-admin-test-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['biztalk_table'][$id]['wf_field']),
        drupal_render($form['biztalk_table'][$id]['maps_to']),
        drupal_render($form['biztalk_table'][$id]['add_remove']),
        drupal_render($form['biztalk_table'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }

  $header = array(t('Webform Field'), t('Maps to...'), t('Remove'), t('Weight'));
  $table_id = 'custom-admin-test-table';

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  $output .= drupal_render_children($form);
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'custom-admin-test-weight');

  $title = node_load($nid)->title;
  $preoutput = _biztalk_page($nid) . "<br/><hr/><h1>$title</h1>";

  return $preoutput . $output;
}

/**
 * Implement submission
 */
function biztalk_webform_submit($form, &$form_state) {
  // Slight overkill having these values on each row, but it's okay
  $bid = $form_state['values']['biztalk_table'][0]['bid'];
  $nid = $form_state['values']['biztalk_table'][0]['nid'];
  $enabled = $form_state['values']["biztalk-enabled-$bid-$nid"];

  // save this value in the {variable} table
  variable_set("biztalk-enabled-$bid-$nid", $enabled);

  $trigger_name = $form_state['triggering_element']['#name'];
  if ($trigger_name == 'save') {
    // clicked 'Save Changes' at the bottom
    return _biztalk_webform_submit_save($form, $form_state);
  } else {
    // clicked one of the remove buttons
    return _biztalk_webform_submit_remove($form, $form_state, $trigger_name);
  }
}

/**
 * Function for when a user clicked one of the "Remove" buttons
 * Redirects to the confirmation form, passing in necessary variables
 */
function _biztalk_webform_submit_remove($form, &$form_state, $trigger_name) {
  // Find out which "Remove" button was clicked
  $trigger_arr = explode('-', $trigger_name);
  $hid = $trigger_arr[count($trigger_arr) - 1];
  $form_state['redirect'] = 'admin/config/biztalk_custom_admin/confirm/' . urlencode($hid) . '/' . urlencode($trigger_arr[2]);
}

/**
 * Confirmation of removal of a header row.
 * They may cancel or remove. The _submit function is called only if they click "Remove"
 */
function biztalk_webform_submit_removal_confirm($form, &$form_state, $hid, $nid) {
  $form = array();
  $form['remove_hid'] = array(
    '#type' => 'textfield',
    '#value' => $hid,
    '#access' => FALSE,
  );
  $form['redirect_nid'] = array(
    '#type' => 'textfield',
    '#value' => $nid,
    '#access' => FALSE,
  );
  $form_state['values']['redirect_nid'] = $nid;
  // just in case
  $hid = urldecode($hid);
  $nid = urldecode($nid);
  // find human column for hid
  $human = db_query('SELECT human FROM {biztalk_header} WHERE hid = :hid', array(':hid' => $hid))->fetchField();
  $form['human'] = array(
    '#type' => 'textfield',
    '#value' => $human,
    '#access' => FALSE,
  );

  $question = t('Are you sure you want to remove the header "@header"', array('@header' => $human));
  $cancel_path = 'admin/config/biztalk_custom_admin/' . $nid;
  $desc = t('This will remove "@header" from all webform mappings.', array('@header' => $human));
  $yes = 'Remove';
  $no = 'Cancel';
  $confirm_name = 'biztalk_confirm';

  return confirm_form($form, $question, $cancel_path, $desc, $yes, $no, $confirm_name);
}

/**
 * User has confirmed removal of a header row
 * Redirects back to the configuration page for the webform node being configured for the BizTalk export
 */
function biztalk_webform_submit_removal_confirm_submit($form, &$form_state) {
  // here and every call like this, it's not fully built out per webform nid, but stubbed out for future bids
  $bid = variable_get('biztalk_bid', 1);
  $hid = $form_state['values']['remove_hid'];
  $nid = $form_state['values']['redirect_nid'];
  $human = $form_state['values']['human'];

  // remove the row in {biztalk_header}
  db_delete('biztalk_header')->condition('hid', $hid)->condition('bid', $bid)->execute();

  // remove rows in {biztalk_map_component}
  db_delete('biztalk_map_component')->condition('nid', $nid)->condition('hid', $hid)->execute();

  drupal_set_message(t("Removed header mapping '@human'", array("@human" => $human)));
  $form_state['redirect'] = 'admin/config/biztalk_custom_admin/' . $form_state['values']['redirect_nid'];
}

function biztalk_custom_admin_cron_form ($form, &$form_state) {
  $form = array();
  $last_sid = variable_get('biztalk_last_sid', 1);
  $form['sid_counter'] = array(
    '#markup' => '<p>Current submission counter value: ' . $last_sid . '</p>'
  );

  $form['reset_sid_counter'] = array(
    '#type' => 'submit',
    '#name' => 'reset-counter',
    '#value' => t('Reset submission counter'),
  );

  $form['biztalk_folder'] = array(
    '#type' => 'textfield',
    '#title' => 'Folder to place pipe-delimited files',
    '#description' => 'Optional. Subdirectory within the mounted directory below.',
    '#default_value' => variable_get('biztalk_folder'),
  );

  $form['biztalk_mounted_directory'] = array(
    '#type' => 'textfield',
    '#title' => 'Mounted Directory',
    '#description' => 'Directory to dump biztalk files. This should be a UNFI mounted directory.',
    '#default_value' => variable_get('biztalk_mounted_directory', '/mnt/BMBCRM'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#name' => 'save',
    '#value' => t('Save'),
  );

  return $form;
}

function biztalk_custom_admin_cron_form_submit($form, &$form_state) {
  // reset the variable to sid 0, mainly for testing purposes
  if ($form_state['triggering_element']['#name'] == 'reset-counter') {
    variable_set('biztalk_last_sid', 0);
  } else {
    variable_set('biztalk_folder', $form_state['values']['biztalk_folder']);
    variable_set('biztalk_mounted_directory', $form_state['values']['biztalk_mounted_directory']);
  }
}

/**
 * Function for when a user clicked one of the "Save changes" button
 * Updates the weights in the database tables, adds any new rows necessary
 */
function _biztalk_webform_submit_save($form, &$form_state) {
  foreach ($form_state['values']['biztalk_table'] as $item) {
    // if they're adding a new row, no header id (hid) can possibly be set, and it's not in that form element
    if (!isset($item['hid']) && trim($item['maps_to']) != '') {
      // insert new row into {biztalk_header}
      $bid = variable_get('biztalk_bid', 1);
      $hid = db_insert('biztalk_header')->fields(array('bid' => $bid, 'human' => trim($item['maps_to'])))->execute();
      // after it's inserted, let's add to the array giving it the hid
      $item['hid'] = $hid;
    }

    // skip logic at the last "add new row" if they entered nothing
    if (!isset($item['hid']) && empty(trim($item['maps_to']))) continue;

    // if they've changed the text box (an existing maps_to => human column), we'll want to update that as we know the hid. {biztalk_header}
    $results = db_query('SELECT human FROM {biztalk_header} WHERE bid = :bid AND hid = :hid', array(':bid' => $item['bid'], ':hid' => $item['hid']));
    foreach ($results as $result) {
      $old_human = $result->human;
    }
    // if they're different, update to the new one
    if ($old_human != $item['maps_to']) {
      $record = array(
        'human' => $item['maps_to'],
        'bid' => $item['bid'],
        'hid' => $item['hid'],
      );
      drupal_write_record('biztalk_header', $record, array('hid', 'bid'));
    }

    $record = array(
      'nid' => $item['nid'],
      'cid' => $item['wf_field'],
      'hid' => $item['hid'],
      'weight' => $item['weight'],
    );

    // check to see if record already exists
    $query = db_select('biztalk_map_component', 'b');
    $query->condition('b.nid', $record['nid'])
          ->condition('b.hid', $record['hid'])
          ->fields('b', array('nid'));
    $results = $query->execute()->fetchAll();

    // write or update the record if it's safe to
    $primary_keys = array();
    if ($results) {
      // needs to update, drupal_write_record needs to know the primary keys in the case of update
      $primary_keys = array('nid', 'hid');
    }
    // insert or update accordingly
    $result = drupal_write_record('biztalk_map_component', $record, $primary_keys);
  }
}
