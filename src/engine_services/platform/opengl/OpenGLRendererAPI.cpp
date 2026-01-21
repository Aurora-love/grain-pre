#include "engine_services/platform/opengl/OpenGLRendererAPI.h"

#include <glad/glad.h>

// ---------------------------------------------------------------------
// 文件: OpenGLRendererAPI.cpp
// 作用: OpenGL 渲染后端具体实现
// ---------------------------------------------------------------------
namespace GE {

void OpenGLRendererAPI::Init() {
	// 开启混合模式 (Alpha Blending)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 开启深度测试 (Depth Test)
	// 确保 Z 轴坐标能正确影响遮挡关系 (Z 越小越靠前/或 Z 越大越靠前，取决于投影矩阵)
	glEnable(GL_DEPTH_TEST);
}
}