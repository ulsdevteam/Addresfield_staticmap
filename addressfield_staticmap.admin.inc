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
  
  $apis = array(
    'google_maps' => t('Google Static Maps'),
    'google_maps_api' => t('regular Google Maps with fallback to Static Map'),
    'mapquest' => t('Mapquest'),
  );
  
  $form['addressfield_staticmap_api'] = array(
    '#type' => 'select',
    '#title' => t("Mapping API"),
    '#description' => t('The API service to use to render static images. Some may require an API key.'),
    '#default_value' => variable_get('addressfield_staticmap_api', 'google_maps'),
    '#options' => $apis,
  );
  $form['addressfield_staticmap_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t("API Key"),
    '#description' => t('Some services (ex: Mapquest) require an API key to be used.'),
    '#default_value' => variable_get('addressfield_staticmap_api_key', ''),
  );
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
    '#description' => t('The resolution of the zoom level to use on the map. Can be between 0 and 21 for Google Static Maps API, and 1 and 16 for Mapquest. Default is 14.'),
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
  $form['addressfield_staticmap_gmap_type'] = array(
    '#type' => 'select',
    '#title' => t("Map Type"),
    '#description' => t('The format to use for the rendered map. Hybrid blends satellite and roadmap.'),
    '#default_value' => variable_get('addressfield_staticmap_gmap_type', 'roadmap'),
    '#options' => drupal_map_assoc(array('roadmap', 'satellite', 'terrain', 'hybrid')),
  );
  $form['addressfield_staticmap_gmap_link'] = array(
    '#type' => 'checkbox',
    '#title' => t("Link to actual Google map"),
    '#description' => t('Check this option to link the static image to a Google map.'),
    '#default_value' => variable_get('addressfield_staticmap_gmap_link', FALSE),
  );
  $form['addressfield_staticmap_gmap_icon_url'] = array(
    '#type' => 'textfield',
    '#title' => t("Custom Google Map Icon URL"),
    '#description' => t('Optional URL for custom icon to use instead of the regular Google map marker. Must be smaller than 64x64.'),
    '#default_value' => variable_get('addressfield_staticmap_gmap_icon_url', ''),
  );
  return system_settings_form($form);
}

/**
 * Admin form validation callback 
 */
function addressfield_staticmap_admin_form_validate($form, &$form_state) {
  $zoom = $form_state['values']['addressfield_staticmap_gmap_zoom'];
  $api = $form_state['values']['addressfield_staticmap_api'];
  if ($api == 'google_maps') {
    if (empty($zoom) || $zoom < 0 || $zoom > 21 || !is_numeric($zoom)) {
      form_set_error('addressfield_staticmap_gmap_zoom', t('Invalid zoom level. Please enter a value from 0 and 21.'));
      return;
    }
  }
  elseif ($api == 'mapquest') {
    if (empty($zoom) || $zoom < 1 || $zoom > 16 || !is_numeric($zoom)) {
      form_set_error('addressfield_staticmap_gmap_zoom', t('Invalid zoom level. Please enter a value from 1 and 16.'));
      return;
    }
  }
  
  $size = $form_state['values']['addressfield_staticmap_gmap_size'];
  if (empty($size) && !preg_match('/^([0-9]+)x([0-9]+)$/', $size)) {
    form_set_error('addressfield_staticmap_gmap_size', t('Invalid image size. Please enter a validly formatted dimension (ex: 400x400).'));
    return;
  }
  
  $icon_url = $form_state['values']['addressfield_staticmap_gmap_icon_url'];
  if (!empty($icon_url) && !valid_url($icon_url)) {
    form_set_error('addressfield_staticmap_gmap_icon_url', t('Invalid icon URL.'));
    return;
  }

  // Mapquest requires an API key
  $api_key = $form_state['values']['addressfield_staticmap_api_key'];
  if ($api == 'mapquest' && empty($api_key)) {
    form_set_error('addressfield_staticmap_api_key', t('Mapquest requires an API key.'));
    return;
  }
}