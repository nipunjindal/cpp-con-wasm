#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>

/**
emcc src/sample-logger-server/main.cpp -o \
src/sample-logger-server/sample-logger-server.js --bind -std=c++17 -s FETCH=1
**/

void post_to_server(const std::string& log) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

    attr.requestData = log.c_str();
    attr.requestDataSize = log.size();

    emscripten_fetch(&attr, "/log/");
}

EM_JS(void, js_add_label, (const char* text), {
    const jsString = UTF8ToString(text);
    console.log(jsString);
    const node = document.createElement("h2");
    node.innerHTML = jsString;
    document.getElementsByTagName("body")[0].appendChild(node);
});

class Logger {
   public:
    Logger() {}

    void logMessage(const std::string& str) { _log(str); }

   private:
    void _log(const std::string& str) {
        post_to_server(str);

        js_add_label(str.c_str());
    }
};

EMSCRIPTEN_BINDINGS(cppcon22) {
    emscripten::class_<Logger>("Logger").constructor<>().function(
        "logMessage", &Logger::logMessage);
}
