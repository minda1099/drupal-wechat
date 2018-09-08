<?php

/**
 * @file
 * Tencent WeChatMessage class.
 */

/**
 * The class used for tencent_wechatmessage entities.
 */
class TencentWeChatMessage extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'tencent_wechatmessage');
  }

  /**
   * Defines the default entity label.
   */
  protected function defaultLabel() {
    return $this->label;
  }

  /**
   * Defines the default entity URI.
   */
  protected function defaultUri() {
    return array('path' => 'tencent_wechatmessage/' . $this->tencent_wechatmessage_id);
  }
}

/**
 * The class used for Tencent WeChatMessage type entities.
 */
class TencentWeChatMessageType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'tencent_wechatmessage_type');
  }
}
