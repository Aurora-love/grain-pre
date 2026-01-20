#pragma once
#include "engine_services/core/Window.h"
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
    //void Shutdown();
    
    void OnEvent(Event& e);
    static void SetInstance(const Ref<Application>& instance);
    inline static Application& Get() { return *s_instance; }
    inline IWindow& GetWindow() { return *m_Window; }
private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);
private:
    friend Ref<Application> CreateApplication();
    static bool s_allowConstruction;
    static Ref<Application> s_instance;
    Scope<IWindow> m_Window;
    bool m_Running = true;
};

Ref<Application> CreateApplication();
}