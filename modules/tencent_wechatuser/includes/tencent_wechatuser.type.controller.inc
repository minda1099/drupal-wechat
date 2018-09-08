<?php

/**
 * @file
 * Tencent WeChatUser controller class.
 */

/**
 * The Controller for Tencent WeChatUser entities.
 */
class TencentWeChatUserTypeController extends EntityAPIControllerExportable {
  /**
   * Create a Tencent WeChatUser type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Tencent WeChatUser.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }
}
