#include "ImGuiLayer.h"
#include <glad/glad.h> 
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "core/Log.h"
#include "engine_services/core/Application.h"
#include <filesystem>
#include <chrono>

namespace GE {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
ImGuiLayer::~ImGuiLayer() {}

// 运行时选择合适的 GLSL 版本字符串，用于 ImGui OpenGL3 后端初始化
static const char* ChooseGLSLVersion() {
	const char* default_ver = "#version 330 core";
	const GLubyte* verstr = glGetString(GL_SHADING_LANGUAGE_VERSION);
	if (!verstr) return default_ver;
	float v = 0.0f;
	if (sscanf((const char*)verstr, "%f", &v) != 1) return default_ver;
	if (v >= 4.60f) return "#version 460 core";
	if (v >= 4.10f) return "#version 410 core";
	if (v >= 3.30f) return "#version 330 core";
	return "#version 130";
}

// 初始化 ImGui
void ImGuiLayer::OnAttach() {
	// 1. 设置 Dear ImGui 上下文
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
	// 2. 配置 ImGui 功能标志
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // 启用键盘控制 (Tab切换, 方向键等)
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // 启用手柄控制
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // 启用 Docking (停靠) 功能：允许将窗口停靠在主窗口或其他窗口中
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // 启用 Multi-Viewport (多视口) 功能：允许将窗口拖出主程序窗口，成为独立的浮动窗口
	
	// io.ConfigViewportsNoAutoMerge = true;
	// io.ConfigViewportsNoTaskBarIcon = true;
	
	// 使用默认 ImGui 字体，避免依赖外部字体文件（项目当前没有字体资源）
	io.Fonts->AddFontDefault();
	// 通过 FontGlobalScale 放大（例如 1.25f = 放大 25%）
	io.FontGlobalScale = 1.25f;
	LOG_INFO_ENGINE("ImGui font: default (scaled={0})", io.FontGlobalScale);

	// 3. 设置 ImGui 样式
	ImGui::StyleColorsDark(); // 基础深色主题
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(10.0f, 10.0f);
	style.FramePadding = ImVec2(6.0f, 4.0f);
	style.ItemSpacing = ImVec2(8.0f, 6.0f);
	style.WindowRounding = 6.0f;
	style.FrameRounding = 4.0f;
	style.ScrollbarRounding = 6.0f;
	style.GrabRounding = 4.0f;
	style.TabRounding = 4.0f;
	auto& colors = style.Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.12f, 0.14f, 1.0f);
	colors[ImGuiCol_Header] = ImVec4(0.18f, 0.20f, 0.23f, 1.0f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.23f, 0.25f, 0.29f, 1.0f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.28f, 0.32f, 1.0f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.22f, 0.26f, 1.0f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.29f, 0.34f, 1.0f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.33f, 0.39f, 1.0f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.18f, 0.21f, 1.0f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.22f, 0.26f, 1.0f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.26f, 0.30f, 1.0f);
	colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.16f, 0.19f, 1.0f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.26f, 0.31f, 1.0f);
	colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.20f, 0.24f, 1.0f);

	// 4. 当 Viewports 启用时，微调样式以适应独立的平台窗口
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f; // 独立窗口取消圆角
		style.Colors[ImGuiCol_WindowBg].w = 1.0f; // 确保背景完全不透明
	}

	// 在 Application 构造期间 s_Instance 可能尚未设置，直接通过当前上下文获取 GLFW 窗口
	GLFWwindow* window = glfwGetCurrentContext();
	if (!window) {
		LOG_ERROR_ENGINE("Failed to get current GLFW context for ImGui initialization");
		return;
	}
	// 保存窗口句柄，OnDetach 时需要恢复上下文
	m_Window = window;
    
	// 5. 初始化 ImGui 的平台和渲染器后端
	// ImGui_ImplGlfw_InitForOpenGL: 处理鼠标/键盘输入、窗口大小改变等系统事件
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	// ImGui_ImplOpenGL3_Init: 使用运行时检测到的 GLSL 版本初始化渲染后端
	const char* glsl_version = ChooseGLSLVersion();
	LOG_INFO_ENGINE("Using GLSL version: {0}", glsl_version);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

// 当层被移除时调用，用于清理资源
void ImGuiLayer::OnDetach() {
	LOG_INFO_ENGINE("ImGuiLayer::OnDetach begin");

	// 确保当前 OpenGL 上下文为创建 ImGui 时的主窗口上下文，避免在无效上下文上调用后端清理
	if (m_Window) {
		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(m_Window);
		glfwMakeContextCurrent(glfwWindow);
	}

	ImGui_ImplOpenGL3_Shutdown();

	LOG_INFO_ENGINE("ImGuiLayer::OnDetach after ImGui_ImplOpenGL3_Shutdown");

	LOG_INFO_ENGINE("ImGuiLayer::OnDetach before ImGui_ImplGlfw_Shutdown");

	ImGui_ImplGlfw_Shutdown();

	LOG_INFO_ENGINE("ImGuiLayer::OnDetach after ImGui_ImplGlfw_Shutdown");

	LOG_INFO_ENGINE("ImGuiLayer::OnDetach before ImGui::DestroyContext");

	ImGui::DestroyContext();

	LOG_INFO_ENGINE("ImGuiLayer::OnDetach after ImGui::DestroyContext");
	LOG_INFO_ENGINE("ImGuiLayer::OnDetach end");
}

// 核心事件处理：决定事件是否应该被 UI 吞掉
void ImGuiLayer::OnEvent(Event& e) {
	if (m_BlockEvents) {
		ImGuiIO& io = ImGui::GetIO();
		// 如果 ImGui 当前想要捕获鼠标（例如鼠标正悬停在某个 UI 窗口上），
		// 则将该鼠标事件标记为 Handled，防止引擎的游戏逻辑层（如 CameraController）处理它。
		e.m_IsHandled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		
		// 同理，如果 ImGui 想要捕获键盘（例如正在输入文本），则拦截键盘事件。
		e.m_IsHandled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}
}

void ImGuiLayer::OnImGuiRender() {
	// 默认绘制 ImGui 的演示窗口，用于测试集成是否成功
	// TODO: 调用自己的 UI 绘制代码，或者注释掉这行
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
}

//每帧开始时调用
void ImGuiLayer::Begin() {
	// 启动各个后端的帧更新
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	// 告诉 ImGui 开始新的一帧
	ImGui::NewFrame();
}

// 每帧结束时调用
void ImGuiLayer::End() {
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::Get();
	
	// 1. 设置显示尺寸，确保 ImGui 知道窗口有多大
	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
	// 生成渲染数据
	// ImGui::Render() 不会立即执行 OpenGL 调用，而是生成 draw lists
	ImGui::Render();
	
	// 2. 执行实际的 OpenGL 渲染
	// 将生成的 draw lists 转换为 OpenGL 命令绘制到屏幕上
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// 3. 处理多视口 (Multi-Viewports)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		// 因为 Viewports 可能会创建新的原生 Win32/GLFW 窗口，
		// 备份当前的 OpenGL 上下文，处理完 Viewports 后再恢复。
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		
		// 更新和渲染所有独立的平台窗口
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		
		// 恢复主窗口的上下文，确保下一帧渲染到正确的地方
		glfwMakeContextCurrent(backup_current_context);
	}
}
}