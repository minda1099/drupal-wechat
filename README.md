CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Recommended modules
 * Installation
 * Configuration
 * Troubleshooting
 * FAQ
 * Maintainers

INTRODUCTION
------------

The Tencent WeChat module integrates WeChat Official Account Admin Platform
(https://mp.weixin.qq.com/) with Drupal.

 * For a full description of the module, visit the project page:
   https://drupal.org/project/tencent_wechat

 * To submit bug reports and feature suggestions, or to track changes:
   https://drupal.org/project/issues/tencent_wechat


REQUIREMENTS
------------

[Multi-byte UTF-8 support in Drupal 7](https://www.drupal.org/node/2754539)


This module/submodules requires the following modules:

 * Entity API (https://drupal.org/project/enttiy)
 * Date (https://drupal.org/project/date)
 * EntityReference (https://drupal.org/project/entityreference)
 * Composer Vendor Autoload (https://www.drupal.org/project/composer_autoloader)

Make sure Multi-byte UTF-8 support (https://www.drupal.org/node/2754539) is
available. The WeChat user may uses emoji in Nickname, if Multi-byte UTF-8 is
not supported, an error will be thrown when sync/update the
WeChat Public Platform user account.

RECOMMENDED MODULES
-------------------

 * Markdown filter (https://www.drupal.org/project/markdown):
   When enabled, display of the project's README.md help will be rendered
   with markdown.

INSTALLATION
------------

 * Install as you would normally install a contributed Drupal module. Visit:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information. And the steps next for loading the WeChat SDK
   have different options. Which steps to follow totally depends on your
   own favor.

 Option #1

 * If you start project with this: https://github.com/drupal-composer/drupal-project
   Just run `composer require "overtrue/wechat:3.3.9" -vvv`
   and enable the Composer Vendor Autoload (https://www.drupal.org/project/composer_autoloader) module.

 Option #2

 * Install the Tencent WeChat SDK submodule.


CONFIGURATION
-------------

 * Configure Tencent WeChat settings in
   Administration » Configuration » Tencent WeChat.

 * Customize the Tencent WeChat menu settings in
   Administration » Taxonomy » WeChat Menu or
   Administration » Taxonomy » WeChat Personalized Menu

 * Access Tencent WeChat Binding page in
   My Account » WeChat Binding.

TROUBLESHOOTING
---------------

 * If encounter error with errcode 40164 and error message contains
   `invalid ip x.x.x.x`

   - Are you added your/the server's IP address x.x.x.x in whitelist by
   logged in https://mp.weixin.qq.com/?

FAQ
---

TODO.

MAINTAINERS
-----------

Current maintainers:
 * Qiangjun Ran (jungle) - https://drupal.org/user/2919723

This project has been sponsored by:

 * [InterGreat.com](http://www.intergreat.com/)
   InterGreat develops products for international students. Visit the website to find out more.

 * [ITife.com](https://www.itife.com/)
   ITife is a small Drupal Shop in Chongqing, China.
