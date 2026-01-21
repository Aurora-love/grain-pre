#include "Shader.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "engine_services/platform/opengl/OpenGLShader.h"
#include "core/Log.h"
#include "core/Core.h"

namespace GE {

Ref<IShader> IShader::Create(const std::string& filepath) {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<IShader> IShader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}

void IShaderLibrary::Add(const std::string& name, const Ref<IShader>& IShader) {
	ASSERT_ENGINE(!IsExists(name), "IShader already exists!");
	m_IShaders[name] = IShader;
}

void IShaderLibrary::Add(const Ref<IShader>& IShader) {
	auto& name = IShader->GetName();
	Add(name, IShader);
}

Ref<IShader> IShaderLibrary::Load(const std::string& filepath) {
	auto IShader = IShader::Create(filepath);
	Add(IShader);
	return IShader;
}

Ref<IShader> IShaderLibrary::Load(const std::string& name, const std::string& filepath) {
	auto IShader = IShader::Create(filepath);
	Add(name, IShader);
	return IShader;
}

Ref<IShader> IShaderLibrary::Get(const std::string& name) {
	ASSERT_ENGINE(IsExists(name), "IShader not found!");
	return m_IShaders[name];
}

bool IShaderLibrary::IsExists(const std::string& name) const {
	return m_IShaders.find(name) != m_IShaders.end();
}
}
