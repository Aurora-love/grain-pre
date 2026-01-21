#include "RendererAPI.h"
#include "engine_services/platform/opengl/OpenGLRendererAPI.h"
#include "core/Core.h"
#include "core/Log.h"
namespace GE {

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
// 工厂方法实现：根据 s_API 创建对应的实例
Scope<RendererAPI> RendererAPI::Create() {
	switch (s_API) {
		case RendererAPI::API::None: {
            ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); 
            return nullptr;
        }
		case RendererAPI::API::OpenGL:  
            return CreateScope<OpenGLRendererAPI>();
	}
	return nullptr;
}
}