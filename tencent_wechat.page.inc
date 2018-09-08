<?php

/**
 * @file
 * Pages for tencent_wechat module.
 */

use EasyWeChat\Factory;

/**
 * The main and only endpoint's callback page.
 */
function tencent_wechat_page() {

  module_load_include('inc', 'tencent_wechat', 'tencent_wechat');

  $config = tencent_wechat_get_default_config();

  $app = Factory::officialAccount($config);

  $app->server->push(function ($request_message) {

    /*
     * Allow modules to handle messages further.
     *
     * It's better to handle it asynchronously.
     */
    module_invoke_all("tencent_wechat_message", $request_message);

    /*
     * Response will be sent via custom service API.
     */
    module_invoke_all("tencent_wechat_custom_service", $request_message);

    $modules = module_implements('tencent_wechat_custom_service');

    /*
     * Requests handled by custom service should not send the default response.
     */
    if (empty($modules)) {
      $response_message = variable_get('tencent_wechat_default_message');
    }
    else {
      $response_message = $request_message['MsgType'] === 'event' && $request_message['Event'] === 'subscribe' ? variable_get('tencent_wechat_default_message') : NULL;
    }

    // Suppress location event by default.
    if ($request_message['MsgType'] === "event" && $request_message['Event'] === "LOCATION") {
      $response_message = NULL;
    }

    /*
     * Allow extend modules to alter the response message before it send to user.
     */
    $context = ['request_message' => $request_message];


    // Modules implement this hook must response in less 5s in all.
    drupal_alter("tencent_wechat_response", $response_message, $context);

    return $response_message;

  });

  $response = $app->server->serve();
  $response->send();

  exit;
}

/**
 * The main settings form.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function tencent_wechat_form($form, &$form_state) {
  $form['tencent_wechat_app_id'] = array(
    '#title' => t('AppId'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tencent_wechat_app_id', ''),
    '#description' => t('AppId, Which can be got your WeChat Public Platform accout.'),
    '#weight' => -100,

  );
  $form['tencent_wechat_secret'] = [
    '#title' => t('Secret'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tencent_wechat_secret', ''),
    '#description' => t('Secret, Which can be got your WeChat Public Platform accout.'),
    '#weight' => -99,
  ];
  $form['tencent_wechat_token'] = [
    '#title' => t('Token'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tencent_wechat_token', ''),
    '#description' => t('Any string can be used as Token which is the same as Token set on https://mp.weixin.qq.com.'),
    '#weight' => -98,
  ];
  $form['tencent_wechat_aes_key'] = [
    '#title' => t('AES Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tencent_wechat_aes_key', ''),
    '#description' => t('Optional'),
    '#weight' => -97,

  ];
  $form['tencent_wechat_debug'] = array(
    '#title' => t('Debug'),
    '#type' => 'radios',
    '#options' => [
      0 => t('Disable'),
      1   => t('Enable'),
    ],
    '#default_value' => variable_get('tencent_wechat_debug', 0),
    '#description' => t('Debug mode.'),
    '#weight' => 0,

  );
  $form['tencent_wechat_debug_file_path'] = [
    '#title' => t('Debug file path'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tencent_wechat_debug_file_path', '/var/www/html/tencent.wechat.development.log'),
    '#description' => t('Make sure the file is writable.'),
    '#states' => [
      'visible' => [
        ':input[name="tencent_wechat_debug"]' => ['value' => 1],
      ],
      'required' => [
        ':input[name="tencent_wechat_debug"]' => ['value' => 1],
      ],
    ],
    '#weight' => 1,
  ];

  $form['tencent_wechat_default_message'] = [
    '#title' => t('Default response message'),
    '#type' => 'textarea',
    '#required' => TRUE,
    '#default_value' => variable_get('tencent_wechat_default_message', 'Hello, this is WeChat.'),
    '#description' => t('The default response message if no response returned.'),
    '#weight' => 10,

  ];
  return system_settings_form($form);
}

function tencent_wechat_form_validate($form, &$form_state) {

  if (!empty($form_state['values']['tencent_wechat_debug'])) {
    $file_path = isset($form_state['values']['tencent_wechat_debug_file_path']) ? $form_state['values']['tencent_wechat_debug_file_path'] : "";

    if (empty($file_path)) {
      form_set_error("tencent_wechat_debug_file_path", "File path is empty.");
    }
    if (!file_exists($file_path)) {
      form_set_error("tencent_wechat_debug_file_path", "File not exists.");
    }
    if (!is_writable($file_path)) {
      form_set_error("tencent_wechat_debug_file_path", "File not writable.");
    }
  }
}
