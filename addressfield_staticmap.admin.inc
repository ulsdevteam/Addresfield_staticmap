<?php
/**
 * @file
 * 
 * Contains admin page code for the addressfield static map module.
 */

/**
 * Admin form generation callback 
 */
function addressfield_staticmap_admin_form($form, &$form_state) {
  $address_fields = array(
    '' => t('None'),
  );
  
  $fields = field_info_fields();
  foreach ($fields as $name => $field) {
    if ($field['type'] == 'addressfield') {
      $address_fields[$name] = $name;
    }
  }
  
  $form['addressfield_staticmap_field_names'] = array(
    '#type' => 'select',
    '#title' => t("Address Field"),
    '#description' => t('The address field(s) that should be used to generate the static map block.'),
    '#default_value' => variable_get('addressfield_staticmap_field_names', ''),
    '#options' => $address_fields,
    '#multiple' => TRUE,
  );
  $form['addressfield_staticmap_gmap_zoom'] = array(
    '#type' => 'textfield',
    '#title' => t("Zoom Level"),
    '#description' => t('The resolution of the zoom level to use with Google Static Maps API, can be between 0 and 21. Default is 14.'),
    '#default_value' => variable_get('addressfield_staticmap_gmap_zoom', 14),
    '#required' => TRUE,
  );
  $form['addressfield_staticmap_gmap_size'] = array(
    '#type' => 'textfield',
    '#title' => t("Image Size"),
    '#description' => t('Output size of the map image. Default is 400x400, must be defined in WIDTHxHEIGHT format.'),
    '#default_value' => variable_get('addressfield_staticmap_gmap_size', '400x400'),
    '#required' => TRUE,
  );
  $form['addressfield_staticmap_gmap_link'] = array(
    '#type' => 'checkbox',
    '#title' => t("Link to actual Google map"),
    '#description' => t('Check this option to link the static image to a Google map.'),
    '#default_value' => variable_get('addressfield_staticmap_gmap_link', FALSE),
  );
  $form['addressfield_staticmap_gmap_type'] = array(
    '#type' => 'select',
    '#title' => t("Map Type"),
    '#description' => t('Check this option to link the static image to a Google map.'),
    '#default_value' => variable_get('addressfield_staticmap_gmap_type', 'roadmap'),
    '#options' => drupal_map_assoc(array('roadmap', 'satellite', 'terrain', 'hybrid')),
  );
  return system_settings_form($form);
}

/**
 * Admin form validation callback 
 */
function addressfield_staticmap_admin_form_validate($form, &$form_state) {
  $zoom = $form_state['values']['addressfield_staticmap_gmap_zoom'];
  if (empty($zoom) || $zoom < 0 || $zoom > 21 || !is_numeric($zoom)) {
    form_set_error('addressfield_staticmap_gmap_zoom', t('Invalid zoom level. Please enter a value between 0 and 21.'));
    return;
  }
  
  $size = $form_state['values']['addressfield_staticmap_gmap_size'];
  if (empty($size) && !preg_match('/^([0-9]+)x([0-9]+)$/', $size)) {
    form_set_error('addressfield_staticmap_gmap_size', t('Invalid image size. Please enter a validly formatted dimension (ex: 400x400).'));
    return;
  }
}