<?php

/**
 * @file
 * tencent_wechatuser editing UI.
 */

/**
 * UI controller.
 */
class TencentWeChatUserUIController extends EntityDefaultUIController {
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

    // Change the overview menu type for the list of Tencent WeChatUser.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Replaces default entity title.
    $items[$this->path]['title'] = 'WeChat User';

    // Extend the 'edit' path.
    $items['tencent_wechatuser/' . $wildcard . '/edit'] = array(
      'title callback' => 'tencent_wechatuser_page_title',
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

    $items['tencent_wechatuser/' . $wildcard] = array(
      'title callback' => 'tencent_wechatuser_page_title',
      'title arguments' => array(1),
      'page callback' => 'tencent_wechatuser_page_view',
      'page arguments' => array(1),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
    );

    return $items;
  }
}

/**
 * Form callback: create or edit a Tencent WeChatUser.
 */
function tencent_wechatuser_form($form, &$form_state, $tencent_wechatuser, $op = 'edit', $entity_type) {
  // Add the breadcrumb for the form's location.
  tencent_wechatuser_set_breadcrumb();

  // Add the default field elements.
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($tencent_wechatuser->label) ? $tencent_wechatuser->label : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['tencent_wechatuser'] = $tencent_wechatuser;
  field_attach_form('tencent_wechatuser', $tencent_wechatuser, $form, $form_state);

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
    '#value' => t('Save WeChat User'),
    '#submit' => $submit + array('tencent_wechatuser_edit_form_submit'),
  );

  if (!empty($tencent_wechatuser->label)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete WeChat User'),
      '#suffix' => l(t('Cancel'), 'admin/content/tencent_wechatuser'),
      '#submit' => $submit + array('tencent_wechatuser_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'] = array('tencent_wechatuser_edit_form_validate');

  return $form;
}

/**
 * Form API validate callback for the Tencent WeChatUser form.
 */
function tencent_wechatuser_edit_form_validate(&$form, &$form_state) {
  $tencent_wechatuser = $form_state['tencent_wechatuser'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('tencent_wechatuser', $tencent_wechatuser, $form, $form_state);
}

/**
 * Form API submit callback for the Tencent WeChatUser form.
 */
function tencent_wechatuser_edit_form_submit(&$form, &$form_state) {
  // Save the entity and go back to the list of Tencent WeChatUser.
  $tencent_wechatuser = entity_ui_controller('tencent_wechatuser')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  $is_new_entity = $tencent_wechatuser->is_new = isset($tencent_wechatuser->is_new) ? $tencent_wechatuser->is_new : 0;
  if ($is_new_entity) {
    $tencent_wechatuser->created = time();
  }

  $tencent_wechatuser->changed = time();

  $tencent_wechatuser->save();

  // Send feedback message to the user.
  $message = t("WeChat User :label updated.", array(':label' => $tencent_wechatuser->label));

  if ($is_new_entity) {
    $message = t("WeChat User :label created.", array(':label' => $tencent_wechatuser->label));
  }

  drupal_set_message($message);

  $form_state['redirect'] = 'admin/content/tencent_wechatuser';
}

/**
 * Form API submit callback for the delete button.
 */
function tencent_wechatuser_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/tencent_wechatuser/manage/' . $form_state['tencent_wechatuser']->tencent_wechatuser_id . '/delete';
}

/**
 * Sets the breadcrumb for administrative Tencent WeChatUser pages.
 */
function tencent_wechatuser_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('WeChat User'), 'admin/content/tencent_wechatuser'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
