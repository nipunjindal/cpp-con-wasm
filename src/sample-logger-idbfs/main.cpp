#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>

/**
emcc src/sample-logger-idbfs/main.cpp -o \
src/sample-logger-idbfs/sample-logger-idbfs.js --bind -std=c++17 -lidbfs.js

String.fromCharCode.apply(null, FS.readFile('/data/logs'))
**/

EM_JS(void, setupFS, (), {
    FS.mkdir('/data');
    FS.mount(IDBFS, {}, '/data');
    FS.syncfs(true, function(err) {});
});

EM_JS(void, syncFS, (), { FS.syncfs(function(err){console.log("Synced", err)}); });

EM_JS(void, js_add_label, (const char* text), {
    const jsString = UTF8ToString(text);
    console.log(jsString);
    const node = document.createElement("h2");
    node.innerHTML = jsString;
    document.getElementsByTagName("body")[0].appendChild(node);
});

class Logger {
   public:
    Logger() { setupFS(); }

    void logMessage(const std::string& str) { _log(str); }

   private:
    void _log(const std::string& str) {
        {
            const auto fileName = "/data/logs";
            std::ofstream of(fileName, std::ofstream::app);
            of << str;
            of << ", ";
        }
        syncFS();

        js_add_label(str.c_str());
    }
};

EMSCRIPTEN_BINDINGS(cppcon22) {
    emscripten::class_<Logger>("Logger").constructor<>().function(
        "logMessage", &Logger::logMessage);
}
