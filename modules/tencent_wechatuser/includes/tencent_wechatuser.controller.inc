<?php

/**
 * @file
 * Tencent WeChatUser controller class.
 */

/**
 * The Controller for Tencent WeChatUser entities.
 */
class TencentWeChatUserController extends EntityAPIController {
  /**
   * Create a Tencent WeChatUser.
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
      'tencent_wechatuser_id' => '',
      'is_new' => TRUE,
      'label' => '',
    );

    $entity = parent::create($values);

    return $entity;
  }
}
