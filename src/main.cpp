#include "core/Log.h"
#include "engine_services/core/Application.h"
#include "engine_services/core/Layer.h"

class Sandbox : public GE::Application {
public:
    Sandbox() {
        LOG_INFO("Sandbox App Initialized!");
        //PushOverlayer(GE::CreateScope<GE::ImGuiLayer>());
    }
    ~Sandbox() {
        LOG_INFO("Sandbox App Destroyed!");
    }
};

GE::Ref<GE::Application> GE::CreateApplication() {
    static GE::Ref<GE::Application> instance = nullptr;
    if (!instance) {
        GE::Application::s_allowConstruction = true;
        instance = GE::CreateRef<Sandbox>();
        GE::Application::s_allowConstruction = false;
        GE::Application::SetInstance(instance);
    }
    return instance;
}

int main(int, char**)
{
    GE::Log::Init();

    GE::Ref<GE::Application> app = GE::CreateApplication();

    app->Run();
    
    app->Shutdown();
}
