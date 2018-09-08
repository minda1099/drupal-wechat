<?php

/**
 * @file
 * Pages for tencent_wechat module.
 */

use EasyWeChat\Foundation\Application;
use EasyWeChat\Message\Text;
use Symfony\Component\EventDispatcher\Event;
use Symfony\Component\EventDispatcher\EventDispatcher;

/**
 * The main and only endpoint's callback page.
 */
function tencent_wechat_page() {
  $options = [
    'debug'  => variable_get('tencent_wechat_debug') == 1 ? TRUE : FALSE,
    'app_id' => variable_get('tencent_wechat_app_id'),
    'secret' => variable_get('tencent_wechat_secret'),
    'token'  => variable_get('tencent_wechat_token'),
    'aes_key' => variable_get('tencent_wechat_aes_key'),
    'log' => [
      'level' => 'debug',
      'file'  => variable_get('tencent_wechat_debug_file_path'),
    ],
  ];
  $app = new Application($options);
  $accessToken = $app->access_token;

  $server = $app->server;
  $server->setMessageHandler(function ($request_message) use ($accessToken) {

    $response_message = variable_get('tencent_wechat_default_message');
    /*
     * Allow modules to handle messages further.
     *
     * Better handle this asynchronously.
     *
     */
    module_invoke_all("tencent_wechat_message", $request_message);

    /*
     * Allow extend modules to alter the response message before it send to user.
     */
    $context = ['request_message' => clone $request_message];

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
  $form['tencent_wechat_secret'] = array(
    '#title' => t('Secret'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tencent_wechat_secret', ''),
    '#description' => t('Secret, Which can be got your WeChat Public Platform accout.'),
    '#weight' => -99,
  );
  $form['tencent_wechat_token'] = array(
    '#title' => t('Token'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('tencent_wechat_token', ''),
    '#description' => t('Any string can be used as Token which is the same as Token set on https://mp.weixin.qq.com.'),
    '#weight' => -98,
  );
  $form['tencent_wechat_aes_key'] = array(
    '#title' => t('AES Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tencent_wechat_aes_key', ''),
    '#description' => t('Optional'),
    '#weight' => -97,

  );
  $form['tencent_wechat_debug'] = array(
    '#title' => t('Debug'),
    '#type' => 'radios',
    '#options' => array(
      0 => t('Disable'),
      1   => t('Enable'),
    ),
    '#default_value' => variable_get('tencent_wechat_debug', 0),
    '#description' => t('Debug mode.'),
    '#weight' => 0,

  );
  $form['tencent_wechat_debug_file_path'] = array(
    '#title' => t('Debug file path'),
    '#type' => 'textfield',
    '#default_value' => variable_get('tencent_wechat_debug_file_path', '/var/www/html/tencent.wechat.development.log'),
    '#description' => t('Make sure the file is writable.'),
    '#states' => array(
      'visible' => array(
        ':input[name="tencent_wechat_debug"]' => array('value' => 1),
      ),
      'required' => array(
        ':input[name="tencent_wechat_debug"]' => array('value' => 1),
      ),
    ),
    '#weight' => 1,
  );

  $form['tencent_wechat_default_message'] = array(
    '#title' => t('Default response message'),
    '#type' => 'textarea',
    '#required' => TRUE,
    '#default_value' => variable_get('tencent_wechat_default_message', 'Hello, this is WeChat.'),
    '#description' => t('The default response message if no response returned.'),
    '#weight' => 10,

  );
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
