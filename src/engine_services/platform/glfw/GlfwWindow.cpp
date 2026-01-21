#include "GlfwWindow.h"
#include "core/Log.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"
#include "core/events/ApplicationEvent.h"
#include "engine_services/platform/opengl/OpenGLContext.h"
#include <GLFW/glfw3.h>

namespace GE {

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description) {
    LOG_ERROR_ENGINE("GLFW Error ({0}): {1}", error, description);
}

Scope<IWindow> IWindow::Create(const WindowProps& props) {
    return CreateScope<GlfwWindow>(props);
}

GlfwWindow::GlfwWindow(const WindowProps& props) {
    Init(props);
}

GlfwWindow::~GlfwWindow() {
    Shutdown();
}

void GlfwWindow::Init(const WindowProps& props) {
    m_Data.title = props.m_Title;
    m_Data.width = props.m_Width;
    m_Data.height = props.m_Height;
    LOG_INFO_ENGINE("Creating window {0} ({1}, {2})", props.m_Title, props.m_Width, props.m_Height);

    if(s_GLFWWindowCount == 0) {
        int success = glfwInit();
        if(!success) {
            LOG_CRITIVAL_ENGINE("Could not initialize GLFW!");
            return;
        }
        glfwSetErrorCallback(GLFWErrorCallback);
    }

    m_Window = glfwCreateWindow(static_cast<int>(props.m_Width), static_cast<int>(props.m_Height), m_Data.title.c_str(), nullptr, nullptr);
    if(!m_Window) {
        LOG_CRITIVAL_ENGINE("Failed to create GLFW window!");
        return;
    }
    ++s_GLFWWindowCount;

    m_Context = CreateScope<OpenGLContext>(m_Window);
	m_Context->InitContext();
    
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.eventCallback(event);
    });

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;
        WindowResizeEvent event(width, height);
        data.eventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int, int action, int) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent event(key, 0);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.eventCallback(event);
				break;
			}
		}
	});

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t keycode) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		KeyTypedEvent event(keycode);
		data.eventCallback(event);
	});

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action) {
		    case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.eventCallback(event);
				break;
			}
		}
    });

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
		data.eventCallback(event);
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
		data.eventCallback(event);
	});
}

void GlfwWindow::Shutdown() {
    LOG_INFO_ENGINE("GlfwWindow::Shutdown begin");
    if (m_Context) {
        m_Context.reset();
    }
    if(m_Window) {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }
    if(s_GLFWWindowCount > 0) {
        --s_GLFWWindowCount;
        if(s_GLFWWindowCount == 0) {
            LOG_INFO_ENGINE("GlfwWindow::Shutdown calling glfwTerminate()");
            glfwTerminate();
            LOG_INFO_ENGINE("GlfwWindow::Shutdown glfwTerminate returned");
        }
    }
    LOG_INFO_ENGINE("GlfwWindow::Shutdown end");
}

void GlfwWindow::Update() {
    glfwPollEvents();
    if (m_Context) {
        m_Context->SwapBuffers();
    }
}

void GlfwWindow::SetVSync(bool enabled) {
    if(enabled) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }
    m_Data.VSync = enabled;
}

bool GlfwWindow::IsVSync() const {
    return m_Data.VSync;
}
}
