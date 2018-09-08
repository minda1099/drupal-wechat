<?php

/**
 * @file
 * Tencent WeChatMessage controller class.
 */

/**
 * The Controller for Tencent WeChatMessage entities.
 */
class TencentWeChatMessageController extends EntityAPIController {
  /**
   * Create a Tencent WeChatMessage.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our entity.
    $values += array(
      'tencent_wechatmessage_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
