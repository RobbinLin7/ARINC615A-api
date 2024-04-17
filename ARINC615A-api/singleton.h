#pragma once
#include <memory>
#include <mutex>
#include <iostream>
#include "spdlog/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

template <typename T>
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    //template <typename... Args>
    //static T& Instance(Args&&... args)
    //{
    //    std::call_once(initInstanceFlag, [&](){
    //        instancePtr.reset(new T(std::forward<Args>(args)...));
    //    });
    //    return *instancePtr;
    //}

    static T& Instance()
    {
        std::call_once(initInstanceFlag, [&]() {
            instancePtr.reset(new T());
        });
        return *instancePtr;
    }


protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    static std::unique_ptr<T> instancePtr;
    static std::once_flag initInstanceFlag;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instancePtr;

template <typename T>
std::once_flag Singleton<T>::initInstanceFlag;

template<>
spdlog::logger& Singleton<spdlog::logger>::Instance() {
    std::call_once(initInstanceFlag, [&]() {
        auto max_size = 1048576 * 5;
        auto max_files = 3;
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S][process:%P][thread: %t][%s:%#][%^%l%$][%n], %v");

        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/log.txt", max_size, max_files);
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S][process:%P][thread: %t][%s:%#][%l][%n], %v");
        instancePtr.reset(new spdlog::logger("logger", { console_sink, file_sink }));

        });
    return *instancePtr;
}


