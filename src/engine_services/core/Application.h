#pragma once
#include "engine_services/core/Window.h"
#include "engine_services/core/LayerStack.h"
#include "engine_services/platform/imgui/ImGuiLayer.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/Event.h"
#include "core/Core.h"
namespace GE {

class Application {
protected:
    Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;
public:
    virtual ~Application();
    void Run();
    void Shutdown();
    
    void OnEvent(Event& e);
    void PushLayer(Scope<Layer> layer);
    void PushOverlayer(Scope<Layer> overlayer);

    static void SetInstance(const Ref<Application>& instance);
    inline static Application& Get() { return *s_Instance; }
    inline IWindow& GetWindow() { return *m_Window; }
private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);
private:
    friend Ref<Application> CreateApplication();
    static bool s_allowConstruction;
    static Ref<Application> s_Instance;
    bool m_Running = true;
    Scope<IWindow> m_Window;
    LayerStack m_LayerStack;
    ImGuiLayer* m_ImGuiLayer;
};

Ref<Application> CreateApplication();
}