<?php

interface TencentWeChatMenuItemInterface {

  public function __construct($wrapper);

  public function getData();

}

class TencentWeChatMenuItemClick implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $key = $this->wrapper->tencent_menu_key->value();
    return [
      'type' => 'click',
      'name' => $name,
      'key' => $key,
    ];
  }

}

class TencentWeChatMenuItemView implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $url = $this->wrapper->tencent_menu_url->value();
    return [
      'type' => 'view',
      'name' => $name,
      'url' => $url,
    ];
  }
}

class TencentWeChatMenuItemScanCodePush implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $key = $this->wrapper->tencent_menu_key->value();
    return [
      'type' => 'scancode_push',
      'name' => $name,
      'key' => $key,
    ];
  }
}

class TencentWeChatMenuItemScanCodeWaitMsg implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $key = $this->wrapper->tencent_menu_key->value();
    return [
      'type' => 'scancode_waitmsg',
      'name' => $name,
      'key' => $key,
    ];
  }
}

class TencentWeChatMenuItemPicSysPhoto implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $key = $this->wrapper->tencent_menu_key->value();
    return [
      'type' => 'pic_sysphoto',
      'name' => $name,
      'key' => $key,
    ];
  }
}

class TencentWeChatMenuItemPicPhotoOrAlbum implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $key = $this->wrapper->tencent_menu_key->value();
    return [
      'type' => 'pic_photo_or_album',
      'name' => $name,
      'key' => $key,
    ];
  }
}

class TencentWeChatMenuItemPicWeixin implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $key = $this->wrapper->tencent_menu_key->value();

    return [
      'type' => 'pic_weixin',
      'name' => $name,
      'key' => $key,
    ];
  }
}

class TencentWeChatMenuItemLocationSelect implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $key = $this->wrapper->tencent_menu_key->value();

    return [
      'type' => 'location_select',
      'name' => $name,
      'key' => $key,
    ];
  }
}

class TencentWeChatMenuItemMediaId implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $mediaid = $this->wrapper->tencent_menu_media_id->value();
    return [
      'type' => 'media_id',
      'name' => $name,
      'media_id' => $mediaid,
    ];
  }
}

class TencentWeChatMenuItemViewLimited implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $mediaid = $this->wrapper->tencent_menu_media_id->value();
    return [
      'type' => 'view_limited',
      'name' => $name,
      'media_id' => $mediaid,
    ];
  }
}
class TencentWeChatMenuItemMiniProgram implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    $url = $this->wrapper->tencent_menu_url->value();
    $appid = $this->wrapper->tencent_menu_app_id->value();
    $pagepath = $this->wrapper->tencent_menu_page_path->value();

    return [
      'type' => 'miniprogram',
      'name' => $name,
      'url' => $url,
      'appid' => $appid,
      'pagepath' => $pagepath
    ];
  }
}

class TencentWeChatMenuItemDefault implements TencentWeChatMenuItemInterface {

  private $wrapper = NULL;
  public function __construct($wrapper) {
    $this->wrapper = $wrapper;
  }

  public function getData() {
    $name = $this->wrapper->name->value();
    return [
      'name' => $name,
    ];
  }
}


class TencentWeChatMenuTree {

  public function getTree ($vocabulary="tencent_wechat_menu"){
    $vocabularies = taxonomy_vocabulary_get_names();


    $vocabulary = array_filter($vocabularies, function ($item) use ($vocabulary) {
      return $item->machine_name === $vocabulary;
    });

    if (empty($vocabulary)) {
      drupal_set_message("WeChat Menu not found.");
      return;
    }

    $vocabulary = reset($vocabulary);
    $vid = $vocabulary->vid;
    $level1 = taxonomy_get_tree($vid, 0, 1);

    $buttons =[];
    foreach ($level1 as $level1_item) {
      $level1_tid = $level1_item->tid;

      $level1_data = $this->getData($level1_tid);

      $level2 = taxonomy_get_tree($vid, $level1_tid, 1);

      $sub_buttons = [];

      foreach (array_reverse($level2) as $level2_item) {
        $level2_tid = $level2_item->tid;
        $sub_buttons[] = $this->getData($level2_tid);
      }
      if (!empty($sub_buttons)) {
        $buttons[] = array_merge($level1_data, ["sub_button"=>$sub_buttons]);
      }
      else {
        $buttons[] = $level1_data;
      }
    }

    return $buttons;

  }

  public function getData($tid) {
    $wrapper = entity_metadata_wrapper('taxonomy_term', $tid);

    $type = $wrapper->tencent_menu_type->value();

    $class = NUll;

    switch ($type) {
      case 'click':
        $class = new TencentWeChatMenuItemClick($wrapper);
        break;
      case 'view':
        $class = new TencentWeChatMenuItemView($wrapper);
        break;
      case 'scancode_push':
        $class = new TencentWeChatMenuItemScanCodePush($wrapper);
        break;
      case 'scancode_waitmsg':
        $class = new TencentWeChatMenuItemScanCodeWaitMsg($wrapper);
        break;
      case 'pic_sysphoto':
        $class = new TencentWeChatMenuItemPicSysPhoto($wrapper);
        break;
      case 'pic_photo_or_album':
        $class = new TencentWeChatMenuItemPicPhotoOrAlbum($wrapper);
        break;
      case 'pic_weixin':
        $class = new TencentWeChatMenuItemPicWeixin($wrapper);
        break;
      case 'location_select':
        $class = new TencentWeChatMenuItemLocationSelect($wrapper);
        break;
      case 'media_id':
        $class = new TencentWeChatMenuItemMediaId($wrapper);
        break;
      case 'view_limited':
        $class = new TencentWeChatMenuItemViewLimited($wrapper);
        break;
      case 'miniprogram':
        $class = new TencentWeChatMenuItemMiniProgram($wrapper);
        break;

      default:
        $class = new TencentWeChatMenuItemDefault($wrapper);
        break;
    }

    return $class->getData();

  }
}
