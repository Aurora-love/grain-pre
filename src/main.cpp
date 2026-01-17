#include "core/Log.h"
int main(int, char**)
{
    Grain::Log::Init();
    
    LOG_INFO("log init");
}