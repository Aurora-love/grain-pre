#pragma once
#include "RendererAPI.h"

// ---------------------------------------------------------------------
// 类: RenderCommand
// 作用: 渲染命令队列 / 代理 (Facade)
// 描述: 提供了一个静态接口来执行渲染命令。
//       实际上它并不直接执行逻辑，而是将请求转发给内部持有的 s_RendererAPI 实例。
//       这种设计允许我们在未来轻松添加多线程渲染或渲染命令队列（Render Queue）功能，
//       而不必修改上层调用代码。
// ---------------------------------------------------------------------

namespace GE {

class RenderCommand {
public:
	// 初始化渲染系统
	static void Init();
	// 设置视口区域
	inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		s_RendererAPI->SetViewport(x, y, width, height);
	}
	// 设置清屏颜色
	inline static void SetClearColor(const Vec4& color) {
		s_RendererAPI->SetClearColor(color);
	}
	// 执行清屏
	inline static void Clear() {
		s_RendererAPI->Clear();
	}
	// 执行索引绘制
	// 自动绑定 VertexArray，然后调用底层 API 的绘制命令
	inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) {
		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray, indexCount);
	}

private:
	// 全局唯一的渲染 API 实例指针
	static Scope<RendererAPI> s_RendererAPI;
};

}
