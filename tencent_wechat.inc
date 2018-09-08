<?php

/**
 * @file
 * The tencent_wechat.inc file.
 */

/**
 * Helper function return the default config.
 *
 * @return array
 *   The default config.
 */
function tencent_wechat_get_default_config() {

  $config = [
    'debug'  => variable_get('tencent_wechat_debug') == 1 ? TRUE : FALSE,
    'app_id' => variable_get('tencent_wechat_app_id'),
    'secret' => variable_get('tencent_wechat_secret'),
    'token'  => variable_get('tencent_wechat_token'),
    'aes_key' => variable_get('tencent_wechat_aes_key'),
    'log' => [
      'level' => 'debug',
      'file'  => variable_get('tencent_wechat_debug_file_path'),
    ],
    'response_type' => 'array',
  ];

  return $config;
}
