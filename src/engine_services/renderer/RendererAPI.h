#pragma once
#include "VertexArray.h"
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
	virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	inline static API GetAPI() { return s_API; }
	virtual void SetClearColor(const Vec4& color) = 0;
	virtual void Clear() = 0;
	// 执行索引绘制 (Indexed Draw Call)
	// vertexArray: 包含顶点数据和索引数据的顶点数组对象
	// indexCount: 如果为0 (默认)，则绘制整个 IndexBuffer，否则绘制指定数量的索引 (用于批处理)
	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

	// 静态工厂方法，根据当前 API 类型创建具体的 RendererAPI 实例
	static Scope<RendererAPI> Create();
private:
	static API s_API; // 当前选用的 API
};
}