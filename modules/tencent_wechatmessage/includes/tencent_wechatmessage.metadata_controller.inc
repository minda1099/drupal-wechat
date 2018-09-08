<?php

/**
 * @file
 * Wechat User Metadata Controller.
 */

/**
 * Wechat User Metadata Controller.
 */
class TencentWeChatMessageMetadataController extends EntityDefaultMetadataController {

  /**
   * Entity Property Info.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info['tencent_wechatmessage']['properties'];

    $properties['label'] = array(
      'type' => 'text',
      'label' => t('WeChat Message Label'),
      'description' => t('Label for Tencent WeChat Message.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer tencent wechatmessage',
      'schema field' => 'label',
      'required' => TRUE,
    );
    return $info;
  }

}
