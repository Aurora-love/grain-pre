#include "Application.h"
#include "core/CoreTime.h"
#include "core/Core.h"
#include "core/Log.h"
#include <glad/glad.h>


namespace GE {
    
Ref<Application> Application::s_instance = nullptr;
bool Application::s_allowConstruction = false;

Application::Application() {
    if (!s_allowConstruction) {
        ASSERT(false, "Application must be created via CreateApplication()");
    }
    if (s_instance) {
        ASSERT(false, "Application already exists!");
    }
    Time::Init();
    m_Window = IWindow::Create();

    //TODO: Renderer,Physics2D,...

    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}


Application::~Application() {
    if (s_instance && s_instance.get() == this)
        s_instance.reset();
}

void Application::SetInstance(const Ref<Application>& instance) {
    s_instance = instance;
}

void Application::Run() {
	while (m_Running) {
		Time::Update();
		Timestep timestep = Time::GetDeltaTime();
        //TEST
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Window->Update();
	}
}

void Application::OnEvent(Event& e) {
    LOG_INFO_ENGINE(e.ToString());
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
}

bool Application::OnWindowClose(WindowCloseEvent&) {
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e) {
    if(e.GetWidth() == 0 || e.GetHeight() == 0) {
        return false;
    }
    //Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}
}