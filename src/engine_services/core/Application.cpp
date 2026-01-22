#include "Application.h"
#include "core/CoreTime.h"
#include "core/Core.h"
#include "core/Log.h"
#include "engine_services/renderer/Renderer.h"
#include <glad/glad.h>

namespace GE {
    
Ref<Application> Application::s_Instance = nullptr;
bool Application::s_allowConstruction = false;

Application::Application() {
    if (!s_allowConstruction) {
        ASSERT_ENGINE(false, "Application must be created via CreateApplication()");
    }
    if (s_Instance) {
        ASSERT_ENGINE(false, "Application already exists!");
    }
    Time::Init();
    m_Window = IWindow::Create();

    //TODO: Renderer,Physics2D,...
    Renderer::Init();

    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    auto imguiLayer = CreateScope<ImGuiLayer>();
	m_ImGuiLayer = imguiLayer.get();
	PushOverlayer(std::move(imguiLayer));
}


Application::~Application() {
    LOG_INFO_ENGINE("Application::~Application begin");
    if (s_Instance && s_Instance.get() == this)
        s_Instance.reset();
    LOG_INFO_ENGINE("Application::~Application end");
}

void Application::SetInstance(const Ref<Application>& instance) {
    s_Instance = instance;
}

void Application::Run() {
	while (m_Running) {
		Time::Update();
		Timestep timestep = Time::GetDeltaTime();

        for(const auto& layer : m_LayerStack) {
            layer->OnUpdate(timestep);
        }

        // 渲染更新
        Renderer::BeginScene();
        for(const auto& layer : m_LayerStack) {
            layer->OnRender();
        }
        Renderer::EndScene();

        //TODO: Render thread, ImGuiRender
        m_ImGuiLayer->Begin();
        for(const auto& layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();
        // PollEvents + SwapBuffers
		m_Window->Update();
	}
}

void Application::OnEvent(Event& e) {
    //LOG_INFO_ENGINE(e.ToString());

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

	for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
		if (e.m_IsHandled) {
			break;
        }
		(*it)->OnEvent(e);
	}
}

void Application::PushLayer(Scope<Layer> layer) {
	m_LayerStack.PushLayer(std::move(layer));
}

void Application::PushOverlayer(Scope<Layer> layer) {
	m_LayerStack.PushOverlayer(std::move(layer));
}

bool Application::OnWindowClose(WindowCloseEvent&) {
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e) {
    if(e.GetWidth() == 0 || e.GetHeight() == 0) {
        return false;
    }
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}

void Application::Shutdown() {
	LOG_INFO_ENGINE("Application::Shutdown begin");
	m_Running = false;
	// 先显式清理所有 Layer，确保 ImGui 等依赖的系统在窗口销毁前已被卸载
	m_LayerStack.Clear();
	LOG_INFO_ENGINE("Application::Shutdown end");
}
}