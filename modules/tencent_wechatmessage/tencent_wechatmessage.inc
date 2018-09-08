<?php

/**
 * @file
 * Hooks implementation.
 */

/**
 * Implements hook_tencent_wechat_response_alter().
 */
function tencent_wechatmessage_tencent_wechat_response_alter(&$response_message, $context) {

  $request_message = $context["request_message"];

  // Suppress location event.
  if ($request_message->MsgType === "event" && $request_message->Event === "LOCATION") {
    $response_message = NULL;
  }
  $queue = DrupalQueue::get('tencent_wechatmessage');
  $queue->createItem([$request_message, $response_message]);
}

/**
 * Implements hook_cron_queue_info().
 */
function tencent_wechatmessage_cron_queue_info() {
  $queues['tencent_wechatmessage'] = array(
    'worker callback' => 'tencent_wechatmessage_worker',
    'time' => 60,
  );
  return $queues;
}

/**
 * Message worker.
 *
 * @param array $item
 *   The request message and response message.
 */
function tencent_wechatmessage_worker(array $item) {
  list($request_message, $response_message) = $item;
  watchdog("tencent_wechatmessage",
    "A message from: %openid %time [%type]",
    [
      "%openid" => $request_message->FromUserName,
      "%time" => REQUEST_TIME,
      "%type" => $request_message->MsgType,
    ]
  );
}
