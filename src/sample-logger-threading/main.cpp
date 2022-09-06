#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>

#ifdef __EMSCRIPTEN_PTHREADS__
#include <chrono>
#include <mutex>
#include <queue>
#include <thread>
#endif

/**
emcc src/sample-logger-threading/main.cpp -o \
src/sample-logger-threading/sample-logger-threading.js  --bind -std=c++17 -s \
USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=1
**/

EM_JS(void, js_console, (const char* text), {
    const jsString = UTF8ToString(text);
    console.log(jsString);
});

class Logger {
   public:
#ifdef __EMSCRIPTEN_PTHREADS__

    Logger() { this->t1 = std::thread(&Logger::waitForMessagesToLog, this); }

    void waitForMessagesToLog() {
        while (true) {
            {
                std::unique_lock lck(messages_mutex);
                if (!messages.empty()) {
                    auto str = messages.front();
                    messages.pop();
                    lck.unlock();
                    _log(str);
                }
            }
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(500ms);
        }
    }
#endif

    void logMessage(const std::string& str) {
#ifdef __EMSCRIPTEN_PTHREADS__
        std::lock_guard g(messages_mutex);
        messages.push({str});
#else
        _log(str);
#endif
    }

   private:
    void _log(const std::string& str) { js_console(str.c_str()); }

#ifdef __EMSCRIPTEN_PTHREADS__
    std::queue<std::string> messages;
    std::mutex messages_mutex;
    std::thread t1;
#endif
};

EMSCRIPTEN_BINDINGS(cppcon22) {
    emscripten::class_<Logger>("Logger").constructor<>().function(
        "logMessage", &Logger::logMessage);
}