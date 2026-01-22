#include "Shader.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "engine_services/platform/opengl/OpenGLShader.h"
#include "core/Log.h"
#include "core/Core.h"

namespace GE {

Ref<Shader> Shader::Create(const std::string& filepath) {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
	switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    ASSERT_ENGINE(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}
	ASSERT_ENGINE(false, "Unknown RendererAPI!");
	return nullptr;
}

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& Shader) {
	ASSERT_ENGINE(!IsExists(name), "Shader already exists!");
	m_Shaders[name] = Shader;
}

void ShaderLibrary::Add(const Ref<Shader>& Shader) {
	auto& name = Shader->GetName();
	Add(name, Shader);
}

Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
	auto Shader = Shader::Create(filepath);
	Add(Shader);
	return Shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
	auto Shader = Shader::Create(filepath);
	Add(name, Shader);
	return Shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& name) {
	ASSERT_ENGINE(IsExists(name), "Shader not found!");
	return m_Shaders[name];
}

bool ShaderLibrary::IsExists(const std::string& name) const {
	return m_Shaders.find(name) != m_Shaders.end();
}
}
