#include "OpenGLContext.h"
#include "core/Core.h"
#include "core/Log.h"
#ifdef PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GE {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		ASSERT_ENGINE(windowHandle, "Window handle is null!")
}

void OpenGLContext::InitContext() {
	// 将当前上下文设置为此线程的主上下文
	glfwMakeContextCurrent(m_WindowHandle);
		
	// 初始化 GLAD (加载 OpenGL 函数指针)
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!status) {
		LOG_ERROR_ENGINE("Failed to initialize Glad!");
	}
	//ASSERT_ENGINE(status, "Failed to initialize Glad!");

	// 打印显卡和驱动信息
	LOG_INFO_ENGINE("OpenGL Info:");
	LOG_INFO_ENGINE("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	LOG_INFO_ENGINE("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	LOG_INFO_ENGINE("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void OpenGLContext::SwapBuffers() {
	// 交换前后缓冲区，呈现图像
	glfwSwapBuffers(m_WindowHandle);
}

}