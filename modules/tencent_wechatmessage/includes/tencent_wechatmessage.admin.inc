<?php

/**
 * @file
 * tencent_wechatmessage editing UI.
 */

/**
 * UI controller.
 */
class TencentWeChatMessageUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   *
   * Main reason for doing this is that parent class hook_menu() is, optimized
   * for entity type administration.
   */
  public function hook_menu() {
    // TODO: EntityDefaultUIController controller automatically adds the menu
    // to import entities, but there is a bug with this action and can not work
    // with the version of your entity_api module, track the issue # 2112755
    // https://www.drupal.org/node/2112755
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $items = parent::hook_menu();

    // Change the overview menu type for the list of Tencent WeChatMessage.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Replaces default entity title.
    $items[$this->path]['title'] = 'WeChat Message';

    // Extend the 'edit' path.
    $items['tencent_wechatmessage/' . $wildcard . '/edit'] = array(
      'title callback' => 'tencent_wechatmessage_page_title',
      'title arguments' => array(1),
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array($this->entityType, 1),
      'access callback' => 'entity_access',
      'access arguments' => array('edit', $this->entityType),
    );

    // Extend the 'add' path.
    $items[$this->path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'entity_ui_bundle_add_page',
      'page arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items[$this->path . '/add/%'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType, $this->id_count + 1),
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array($this->entityType, $this->id_count + 1),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items['tencent_wechatmessage/' . $wildcard] = array(
      'title callback' => 'tencent_wechatmessage_page_title',
      'title arguments' => array(1),
      'page callback' => 'tencent_wechatmessage_page_view',
      'page arguments' => array(1),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
    );

    return $items;
  }
}

/**
 * Form callback: create or edit a Tencent WeChatMessage.
 */
function tencent_wechatmessage_form($form, &$form_state, $tencent_wechatmessage, $op = 'edit', $entity_type) {
  // Add the breadcrumb for the form's location.
  tencent_wechatmessage_set_breadcrumb();

  // Add the default field elements.
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('WeChat Message Label'),
    '#default_value' => isset($tencent_wechatmessage->label) ? $tencent_wechatmessage->label : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['tencent_wechatmessage'] = $tencent_wechatmessage;
  field_attach_form('tencent_wechatmessage', $tencent_wechatmessage, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save WeChat Message'),
    '#submit' => $submit + array('tencent_wechatmessage_edit_form_submit'),
  );

  if (!empty($tencent_wechatmessage->label)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete WeChat Message'),
      '#suffix' => l(t('Cancel'), 'admin/content/tencent_wechatmessage'),
      '#submit' => $submit + array('tencent_wechatmessage_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'] = array('tencent_wechatmessage_edit_form_validate');

  return $form;
}

/**
 * Form API validate callback for the Tencent WeChatMessage form.
 */
function tencent_wechatmessage_edit_form_validate(&$form, &$form_state) {
  $tencent_wechatmessage = $form_state['tencent_wechatmessage'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('tencent_wechatmessage', $tencent_wechatmessage, $form, $form_state);
}

/**
 * Form API submit callback for the Tencent WeChatMessage form.
 */
function tencent_wechatmessage_edit_form_submit(&$form, &$form_state) {
  // Save the entity and go back to the list of Tencent WeChatMessage.
  $tencent_wechatmessage = entity_ui_controller('tencent_wechatmessage')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  $is_new_entity = $tencent_wechatmessage->is_new = isset($tencent_wechatmessage->is_new) ? $tencent_wechatmessage->is_new : 0;
  if ($is_new_entity) {
    $tencent_wechatmessage->created = time();
  }

  $tencent_wechatmessage->changed = time();

  $tencent_wechatmessage->save();

  // Send feedback message to the user.
  $message = t("WeChat Message :label updated.", array(':label' => $tencent_wechatmessage->label));

  if ($is_new_entity) {
    $message = t("WeChat Message :label created.", array(':label' => $tencent_wechatmessage->label));
  }

  drupal_set_message($message);

  $form_state['redirect'] = 'admin/content/tencent_wechatmessage';
}

/**
 * Form API submit callback for the delete button.
 */
function tencent_wechatmessage_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/tencent_wechatmessage/manage/' . $form_state['tencent_wechatmessage']->tencent_wechatmessage_id . '/delete';
}

/**
 * Sets the breadcrumb for administrative Tencent WeChatMessage pages.
 */
function tencent_wechatmessage_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Tencent WeChatMessage'), 'admin/content/tencent_wechatmessage'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
