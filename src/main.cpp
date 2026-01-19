#include "core/Log.h"
#include "engine_services/core/Application.h"

class Sandbox : public GE::Application {
public:
    Sandbox() {
        LOG_INFO("Sandbox App Initialized!");
    }
    ~Sandbox() {
        LOG_INFO("Sandbox App Destroyed!");
    }
};

GE::Scope<GE::Application> GE::CreateApplication() {
    return GE::CreateScope<Sandbox>();
}

int main(int, char**)
{
    GE::Log::Init();
    LOG_INFO_ENGINE("log init");

    GE::Scope<GE::Application> app = GE::CreateApplication();

    app->Run();
}
