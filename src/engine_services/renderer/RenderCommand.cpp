#include "engine_services/renderer/RenderCommand.h"
#include "engine_services/platform/opengl/OpenGLRendererAPI.h"

// ---------------------------------------------------------------------
// 文件: RenderCommand.cpp
// 作用: RenderCommand 类的静态成员初始化
// ---------------------------------------------------------------------

namespace GE {

	// 初始化静态的 RendererAPI 实例
	Scope<RendererAPI> RenderCommand::s_RendererAPI = nullptr;

	void RenderCommand::Init()
	{
		s_RendererAPI = RendererAPI::Create();
		s_RendererAPI->Init();
	}

}
