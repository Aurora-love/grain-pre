#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace GE {

Ref<spdlog::logger> Log::s_EngineLogger;
Ref<spdlog::logger> Log::s_Logger;

void Log::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_EngineLogger = spdlog::stdout_color_mt("grain-pre");
    s_EngineLogger->set_level(spdlog::level::trace);
    s_Logger = spdlog::stdout_color_mt("app");
    s_Logger->set_level(spdlog::level::trace); 
}
}