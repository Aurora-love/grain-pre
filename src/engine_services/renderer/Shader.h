#pragma once
#include "core/CoreMath.h"
#include "core/Core.h"
#include <unordered_map>
#include <string>

namespace GE {
/**
 * @brief 着色器抽象基类 (Interface)
 * 
 * 定义了 Shader 的通用接口，允许引擎加载和使用着色器程序，而无需关心底层的图形 API。
 * Shader 对象代表了一个编译并链接好的 GPU 程序 (Program)。
 */
class Shader
{
public:
	virtual ~Shader() = default;
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	static Ref<Shader> Create(const std::string& filepath);
	static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	
    virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
	virtual void SetFloat4(const std::string& name, const Vec4& value) = 0;
	virtual void SetMat4(const std::string& name, const Mat4& value) = 0;
	virtual const std::string& GetName() const = 0;
};
/**
 * @brief Shader 库管理类
 * 
 * 管理已加载的 Shader，防止重复加载，方便通过名称获取 Shader。
 */
class ShaderLibrary
{
public:
	void Add(const std::string& name, const Ref<Shader>& Shader);
	void Add(const Ref<Shader>& Shader);
	Ref<Shader> Load(const std::string& filepath);
	Ref<Shader> Load(const std::string& name, const std::string& filepath);
	Ref<Shader> Get(const std::string& name);
	bool IsExists(const std::string& name) const;
private:
	std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};
}