<?php

/**
 * @file
 * Tencent WeChatUser class.
 */

/**
 * The class used for tencent_wechatuser entities.
 */
class TencentWeChatUser extends Entity {
  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'tencent_wechatuser');
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
    return array('path' => 'tencent_wechatuser/' . $this->tencent_wechatuser_id);
  }
}

/**
 * The class used for Tencent WeChatUser type entities.
 */
class TencentWeChatUserType extends Entity {
  public $type;
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'tencent_wechatuser_type');
  }
}
