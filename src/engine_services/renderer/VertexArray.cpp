#include "engine_services/renderer/VertexArray.h"
#include "engine_services/renderer/Renderer.h"
#include "engine_services/platform/opengl/OpenGLVertexArray.h"

namespace GE {
// 工厂方法实现：根据当前 API 创建对应的 VAO 实现
Ref<VertexArray> VertexArray::Create() {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}
}