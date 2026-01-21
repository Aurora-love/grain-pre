#pragma once
#include "core/CoreMath.h"
#include "core/Core.h"

namespace GE {
class RendererAPI
{
public:
	// 支持的图形 API 类型枚举
	enum class API {
		None = 0, OpenGL = 1
	};
public:
	virtual ~RendererAPI() = default;
	virtual void Init() = 0;
	inline static API GetAPI() { return s_API; }
	
	// 静态工厂方法，根据当前 API 类型创建具体的 RendererAPI 实例
	static Scope<RendererAPI> Create();
private:
	static API s_API; // 当前选用的 API
};
}