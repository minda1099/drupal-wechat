<?php

/**
 * @file
 * Tencent WeChatUser type editing UI.
 */

/**
 * UI controller.
 */
class TencentWeChatUserTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Tencent WeChatUser entity types, including adding and removing fields and the display of fields.';

    return $items;
  }
}

/**
 * Generates the Tencent WeChatUser type editing form.
 */
function tencent_wechatuser_type_form($form, &$form_state, $tencent_wechatuser_type, $op = 'edit') {
  if ($op == 'clone') {
    $tencent_wechatuser_type->label .= ' (cloned)';
    $tencent_wechatuser_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $tencent_wechatuser_type->label,
    '#description' => t('The human-readable name of this Tencent WeChatUser type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($tencent_wechatuser_type->type) ? $tencent_wechatuser_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'tencent_wechatuser_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Tencent WeChatUser type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save WeChat User type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function tencent_wechatuser_type_form_submit(&$form, &$form_state) {
  $tencent_wechatuser_type = entity_ui_form_submit_build_entity($form, $form_state);
  $tencent_wechatuser_type->save();
  $form_state['redirect'] = 'admin/structure/tencent_wechatuser_types';
}

/**
 * Form API submit callback for the delete button.
 */
function tencent_wechatuser_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/tencent_wechatuser_types/manage/' . $form_state['tencent_wechatuser_type']->type . '/delete';
}
