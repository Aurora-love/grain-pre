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
	// glEnable(GL_DEPTH_TEST); // 暂时禁用深度测试以调试三角形绘制
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const Vec4& color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear() {
	// 清除颜色缓冲区和深度缓冲区 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {
	if (vertexArray->GetIndexBuffer()) {
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	} else {
		// 如果没有索引缓冲区，使用顶点缓冲区的大小计算顶点数量
		const auto& vertexBuffers = vertexArray->GetVertexBuffers();
		if (!vertexBuffers.empty()) {
			const auto& buffer = vertexBuffers[0];
			const auto& layout = buffer->GetLayout();
			uint32_t vertexCount = buffer->GetSize() / layout.GetStride();
			uint32_t count = indexCount ? indexCount : vertexCount;
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	}
}
}