(function ($) {
  Drupal.behaviors.tencentWeChatBinding = {
    attach: function (context, settings) {
      var basePath = settings.basePath;
      var postUrl = basePath + 'tencent-wechatbinding/bind/result';
      settings.tencent_wechatbinding.intervalId = window.setInterval(bindingPolling, 2000);
      function bindingPolling() {
        $.post(postUrl, {}, function(result) {
          if (result > 0) {
            var successful_message = Drupal.t("微信绑定成功！");
            $("#tencent-wechatuser-bind-qr-code").remove();
            $("#tencent-wechatuser-binding-message").html(successful_message);
            clearTimeout(settings.tencent_wechatbinding.intervalId);
          }
        }, "json");
      }
      setTimeout(function () {
        clearTimeout(settings.tencent_wechatbinding.intervalId);
        var warning_message = Drupal.t("操作超时，请刷新页面，导入新的二维码，扫描二维码绑定微信。");
        $("#tencent-wechatuser-binding-message").html(warning_message);
        $("#tencent-wechatuser-bind-qr-code").remove();
      }, 60 * 1000);
    }
  };
})(jQuery);
