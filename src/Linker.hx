import sys.io.File;
import sys.FileSystem;

class Linker {
    #if macro
    public static function includeNativeCode(): Void {
        // not very practical but shrug
        #if !display
        if (!FileSystem.exists("bin/src/")) {
            FileSystem.createDirectory("bin/src/");
        } else if (FileSystem.exists("bin/src/ToastUtil.cpp")) {
            // forces recompilation
            FileSystem.deleteFile("bin/src/ToastUtil.cpp");
        }
        File.copy("src/NativeToastUtil.cpp", "bin/src/NativeToastUtil.cpp");
        #end
    }
    #end
}
