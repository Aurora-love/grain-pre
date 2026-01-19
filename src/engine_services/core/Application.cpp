#include "Application.h"
#include "core/CoreTime.h"
#include "core/Core.h"
#include <glad/glad.h>

namespace GE {

Application::Application() {
    Time::Init();
    m_Window = IWindow::Create();

    //TODO: Renderer,Physics2D,...

    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() {
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
    return false;
}
}