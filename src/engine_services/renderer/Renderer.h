#pragma once
#include "Shader.h"
#include "RendererAPI.h"

namespace GE {
/**
 * @brief 高级渲染器 (High-Level Renderer)
 * 
 * 这是引擎渲染系统的对外主要接口。负责管理渲染场景、提交渲染任务。
 * 相比于 RendererAPI (底层绘图命令)，Renderer 更关注“画什么”和“怎么画”的流程控制。
 * 例如：BeginScene（开始场景，设置相机），Submit（提交物体绘制），EndScene（结束场景）。
 */
class Renderer {
public:
	static void Init();
	/**
	 * @brief 获取当前使用的图形 API
	 */
	inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};
}