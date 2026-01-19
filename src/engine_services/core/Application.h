#pragma once
#include "engine_services/core/Window.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/Event.h"
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

    inline Application& Get() { return *m_application; }
    inline IWindow& GetWindow() { return *m_Window; }
private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);
private:
    Scope<Application> m_application;
    Scope<IWindow> m_Window;
    bool m_Running = true;
};

Scope<Application> CreateApplication();
}