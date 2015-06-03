<?php

/**
 * @file
 * Administration callbacks for the module.
 */

/**
 * Menu callback function for label_maker administration.
 */
function label_maker_admin($form, &$form_state) {
  $vget = variable_get('label_maker', '');
  $entity_info = entity_get_info();
  
  // Make form a tree.
  $form['#tree'] = TRUE;

  // Show tokens available.
  $form['tokens'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array_keys($entity_info),
    '#global_types' => TRUE,
    '#click_insert' => TRUE,
  );

  foreach ($entity_info as $type => $info) {
    $form['label_maker'][$type] = array(
      '#type' => 'fieldset',
      '#title' => $info['label'],
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['label_maker'][$type]['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable label maker for this entity type'),
      '#default_value' => isset($vget[$type]['enable']) ? $vget[$type]['enable'] : 0,
    );
    
    // Allow different labels per bundle.
    foreach ($info['bundles'] as $bundle => $detail) {
      $form['label_maker'][$type][$bundle] = array(
        '#type' => 'textfield',
        '#title' => t('Label for @bundle', array('@bundle' => $detail['label'])),
        '#default_value' => isset($vget[$type][$bundle]) ? $vget[$type][$bundle] : $detail['label'],
      );
    }
  }
  
  return system_settings_form($form);
}
