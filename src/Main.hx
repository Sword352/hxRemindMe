package;

class Main {
    static function main(): Void {
        while (true) {
            Sys.sleep(3600);
            ToastUtil.showToast(getNextTitle(), "hxRemindMe", "Take a 5-10 minutes break from programming.");
        }
    }

    static function getNextTitle(): String {
        var output: Int = -1;

        do {
            output = Std.random(_randomTitles.length - 1);
        } while (output == _lastTitle);

        _lastTitle = output;

        return _randomTitles[output];
    }

    static final _randomTitles: Array<String> = [
        "You know what time it is?",
        "Stay hydrated",
        "Keep it up",
        "Some breath of fresh air might be nice",
        "Isn't the sky beautiful?",
        "Let your brain rest for a bit"
    ];
    static var _lastTitle: Int = -1;
}
