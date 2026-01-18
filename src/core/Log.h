#pragma once
#include <memory>

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)
namespace GE {

class Log{
public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

}

#define LOG_TRACE(...)      ::GE::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)       ::GE::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)       ::GE::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)      ::GE::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITIVAL(...)   ::GE::Log::GetLogger()->critical(__VA_ARGS__)
