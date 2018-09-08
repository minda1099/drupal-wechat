<?php

/**
 * @file
 * Hooks implementation.
 */

/**
 * Implements hook_tencent_wechat_message().
 */
function tencent_wechatmessage_tencent_wechat_message($request_message) {
  $queue = DrupalQueue::get('tencent_wechatmessage_request_message');
  $queue->createItem($request_message);
}

/**
 * Implements hook_cron_queue_info().
 */
function tencent_wechatmessage_cron_queue_info() {
  $queues['tencent_wechatmessage_request_message'] = array(
    'worker callback' => 'tencent_wechatmessage_request_message_worker',
    'time' => 60,
  );
  return $queues;
}

/**
 * Request message worker.
 *
 * @param array $request_message
 *   The request message.
 */
function tencent_wechatmessage_request_message_worker(array $request_message) {
  watchdog("tencent_wechatmessage",
    "1. Request message: <br/> !result",
    ["!result" => '<pre>' . var_export($request_message, TRUE) . '</pre>']
  );
}
