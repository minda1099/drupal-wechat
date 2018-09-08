<?php

/**
 * @file
 * Tencent WeChatMessage type editing UI.
 */

/**
 * UI controller.
 */
class TencentWeChatMessageTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Tencent WeChatMessage entity types, including adding and removing fields and the display of fields.';

    return $items;
  }
}

/**
 * Generates the Tencent WeChatMessage type editing form.
 */
function tencent_wechatmessage_type_form($form, &$form_state, $tencent_wechatmessage_type, $op = 'edit') {
  if ($op == 'clone') {
    $tencent_wechatmessage_type->label .= ' (cloned)';
    $tencent_wechatmessage_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $tencent_wechatmessage_type->label,
    '#description' => t('The human-readable name of this Tencent WeChatMessage type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($tencent_wechatmessage_type->type) ? $tencent_wechatmessage_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'tencent_wechatmessage_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Tencent WeChatMessage type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save WeChat Message type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function tencent_wechatmessage_type_form_submit(&$form, &$form_state) {
  $tencent_wechatmessage_type = entity_ui_form_submit_build_entity($form, $form_state);
  $tencent_wechatmessage_type->save();
  $form_state['redirect'] = 'admin/structure/tencent_wechatmessage_types';
}

/**
 * Form API submit callback for the delete button.
 */
function tencent_wechatmessage_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/tencent_wechatmessage_types/manage/' . $form_state['tencent_wechatmessage_type']->type . '/delete';
}
