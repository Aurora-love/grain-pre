#include "CoreTime.h"
namespace GE {

float Time::s_DeltaTime = 0.0f;
double Time::s_TotalTime = 0.0;
float Time::s_TimeScale = 1.0f;
std::chrono::steady_clock::time_point Time::s_StartTime;
std::chrono::steady_clock::time_point Time::s_LastFrameTime;

void Time::Init()
{
    s_StartTime = std::chrono::steady_clock::now();
    s_LastFrameTime = s_StartTime;
    s_DeltaTime = 0.0f;
    s_TotalTime = 0.0;
    s_TimeScale = 1.0f;
}

void Time::Update()
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> delta = currentTime - s_LastFrameTime;
    s_DeltaTime = delta.count();

    s_LastFrameTime = currentTime;
    std::chrono::duration<double> total = currentTime - s_StartTime;
    s_TotalTime = total.count();
}
}