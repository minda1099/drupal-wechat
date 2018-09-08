<?php

/**
 * Allow response message to be altered.
 *
 * @param \EasyWeChat\Message\AbstractMessage $response_message
 *   The response message to be altered.
 * @param array $context
 *   Keys:
 *     - request_message, \EasyWeChat\Support\Collection.
 */
function hook_tencent_wechat_response_alter(\EasyWeChat\Message\AbstractMessage &$response_message, array $context) {
  $request_message = $context["request_message"];
  if ($response_message instanceof \EasyWeChat\Message\Text) {
    $message = "Hi, " . $request_message->FromUserName;
    $message .= ", This message is altered and responsed from " . __FUNCTION__;
    $response_message->content = $message;
  }
}

/**
 * Allow request message to be processed by extend modules.
 *
 * @param \EasyWeChat\Support\Collection $request_message
 *   The request message to be handled further.
 */
function hook_tencent_wechat_message(\EasyWeChat\Support\Collection $request_message) {
  watchdog("tencent_wechat config",
    "A message from @openid",
    ["@openid" => $request_message->FromUserName]
  );
}
