#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <string>

/**
emcc src/sample-c++/main.cpp -o src/sample-c++/sample-c++.js  --bind
**/

class CppClass {
   public:
    CppClass(int _member) : member(_member){};
    int member;
};

template <typename T>
class TemplateCppClass {
   public:
    TemplateCppClass(T a, T b, T c) {
        members[0] = a;
        members[1] = b;
        members[2] = c;
    };

    const T getMember(int n) { return members[n]; }

   protected:
    T members[3];
};

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
    void _log(const std::string& str) { js_add_label(str.c_str()); }
};

EMSCRIPTEN_BINDINGS(cppcon22) {
    emscripten::class_<CppClass>("CppClass")
        .constructor<int>()
        .property("member", &CppClass::member);

    emscripten::class_<TemplateCppClass<int>>("IntTemplateCppClass")
        .constructor<int, int, int>()
        .function("getMember", &TemplateCppClass<int>::getMember);

    emscripten::class_<Logger>("Logger").constructor<>().function(
        "logMessage", &Logger::logMessage);
}