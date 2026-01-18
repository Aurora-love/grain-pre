#pragma once
#include "Core.h"
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)
namespace GE {

class Log {
public:
    static void Init();
    inline static Ref<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
    inline static Ref<spdlog::logger>& GetLogger() { return s_Logger; }
private:
    static Ref<spdlog::logger> s_EngineLogger;
    static Ref<spdlog::logger> s_Logger;
};

}

#define LOG_TRACE_ENGINE(...)      ::GE::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define LOG_INFO_ENGINE(...)       ::GE::Log::GetEngineLogger()->info(__VA_ARGS__)
#define LOG_WARN_ENGINE(...)       ::GE::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define LOG_ERROR_ENGINE(...)      ::GE::Log::GetEngineLogger()->error(__VA_ARGS__)
#define LOG_CRITIVAL_ENGINE(...)   ::GE::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...)             ::GE::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)              ::GE::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)              ::GE::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)             ::GE::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITIVAL(...)          ::GE::Log::GetLogger()->critical(__VA_ARGS__)
