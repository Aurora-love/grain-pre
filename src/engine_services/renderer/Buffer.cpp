#include "Buffer.h"
#include "Renderer.h"
#include "engine_services/platform/opengl/OpenGLBuffer.h"

namespace GE {

// VertexBuffer 工厂方法实现
Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}

// IndexBuffer 工厂方法实现
Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}
}