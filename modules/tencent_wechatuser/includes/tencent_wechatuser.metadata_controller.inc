<?php

/**
 * @file
 * Wechat User Metadata Controller.
 */

/**
 * Wechat User Metadata Controller.
 */
class TencentWeChatUserMetadataController extends EntityDefaultMetadataController {

  /**
   * Entity Property Info.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info['tencent_wechatuser']['properties'];

    $properties['label'] = array(
      'type' => 'text',
      'label' => t('Tencent WeChat User Label'),
      'description' => t('Label for Tencent WeChat user.'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer tencent wechatuser',
      'schema field' => 'label',
      'required' => TRUE,
    );
    return $info;
  }

}
