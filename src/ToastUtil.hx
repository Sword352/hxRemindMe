package;

import cpp.ConstWCharTStar;

@:buildXml('<include name="../../build.xml" />')
@:include("NativeToastUtil.cpp")
extern class ToastUtil {
	@:native("show_toast")
	static function showToast(title:ConstWCharTStar, header:ConstWCharTStar, message:ConstWCharTStar):Void;
}
