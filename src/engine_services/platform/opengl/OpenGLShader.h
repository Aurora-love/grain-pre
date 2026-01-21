#pragma once
#include "engine_services/renderer/Shader.h"
#include <unordered_map>
#include <string>

namespace GE {
	
typedef unsigned int GLenum;

class OpenGLShader : public IShader {
public:
	OpenGLShader(const std::string& filepath);
	OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	virtual ~OpenGLShader();
	virtual void Bind() const override;
	virtual void Unbind() const override;
	virtual void SetInt(const std::string& name, int value) override;
	virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
	virtual void SetFloat4(const std::string& name, const Vec4& value) override;
	virtual void SetMat4(const std::string& name, const Mat4& value) override;
	virtual const std::string& GetName() const override { return m_Name; }

	void UploadUniformInt(const std::string& name, int value);
	void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
	void UploadUniformFloat(const std::string& name, float value);
	void UploadUniformFloat2(const std::string& name, const Vec2& value);
	void UploadUniformFloat3(const std::string& name, const Vec3& value);
	void UploadUniformFloat4(const std::string& name, const Vec4& value);
	void UploadUniformMat3(const std::string& name, const Mat3& matrix);
	void UploadUniformMat4(const std::string& name, const Mat4& matrix);

private:
	std::string ReadFile(const std::string& filepath);
	std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
private:
	uint32_t m_RendererID;
	std::string m_Name;
};
}