#pragma once
#include "core/CoreMath.h"
#include "core/Core.h"
#include <unordered_map>
#include <string>

namespace GE {
/**
 * @brief 着色器抽象基类 (Interface)
 * 
 * 定义了 IShader 的通用接口，允许引擎加载和使用着色器程序，而无需关心底层的图形 API。
 * IShader 对象代表了一个编译并链接好的 GPU 程序 (Program)。
 */
class IShader
{
public:
	virtual ~IShader() = default;
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	static Ref<IShader> Create(const std::string& filepath);
	static Ref<IShader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	
    virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
	virtual void SetFloat4(const std::string& name, const Vec4& value) = 0;
	virtual void SetMat4(const std::string& name, const Mat4& value) = 0;
	virtual const std::string& GetName() const = 0;
};
/**
 * @brief IShader 库管理类
 * 
 * 管理已加载的 IShader，防止重复加载，方便通过名称获取 IShader。
 */
class IShaderLibrary
{
public:
	void Add(const std::string& name, const Ref<IShader>& IShader);
	void Add(const Ref<IShader>& IShader);
	Ref<IShader> Load(const std::string& filepath);
	Ref<IShader> Load(const std::string& name, const std::string& filepath);
	Ref<IShader> Get(const std::string& name);
	bool IsExists(const std::string& name) const;
private:
	std::unordered_map<std::string, Ref<IShader>> m_IShaders;
};
}