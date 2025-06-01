package;

@:cppInclude("NativeToastUtil.cpp")
class ToastUtil {
    public static function showToast(title: String, header: String, message: String): Void {
        untyped show_toast(untyped title.wchar_str(), untyped header.wchar_str(), untyped message.wchar_str());
    }
}
