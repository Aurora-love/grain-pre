#pragma once
#include <chrono>

namespace Grain {

class Time {
public:
    static void Init();
    static void Update();
    inline static float GetDeltaTime() { return s_DeltaTime * s_TimeScale;}
    inline static float GetUnscaledDeltaTime() { return s_DeltaTime;}
    inline static double GetTotalTime() { return s_TotalTime;}
    inline static float GetTimeScale() { return s_TimeScale;}
    inline static void SetTimeScale(float scale) { s_TimeScale = scale;}
private:
    static float s_DeltaTime;
    static double s_TotalTime;
    static float s_TimeScale;
    static std::chrono::steady_clock::time_point s_StartTime;
    static std::chrono::steady_clock::time_point s_LastFrameTime;
    static bool s_Initialized;
};
}