#pragma once
#include <memory>

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)
namespace Grain {

class Log{
public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

}

#define LOG_TRACE(...)      ::Grain::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)       ::Grain::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)       ::Grain::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)      ::Grain::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITIVAL(...)   ::Grain::Log::GetLogger()->critical(__VA_ARGS__)
