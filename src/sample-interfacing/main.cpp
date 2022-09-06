#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <string>

/**
emcc src/sample-interfacing/main.cpp -o \
src/sample-interfacing/sample-interfacing.js --bind
**/

EM_JS(void, js_add_label, (const char* text), {
    const jsString = UTF8ToString(text);
    const node = document.createElement("h2");
    node.innerHTML = jsString;
    document.getElementsByTagName("body")[0].appendChild(node);
});

void add_label(const std::string& text) {
    js_add_label(text.c_str());
}

EMSCRIPTEN_BINDINGS(cppcon22) {
    emscripten::function("add_label", &add_label);
}