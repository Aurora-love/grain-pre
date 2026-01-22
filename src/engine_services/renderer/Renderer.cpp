#include "Renderer.h"
#include "engine_services/platform/opengl/OpenGLShader.h" // 暂时用于 dynamic_cast，未来应该优化 Shader 接口
#include "RenderCommand.h"
// ---------------------------------------------------------------------
// 文件: Renderer.cpp
// 作用: 高级渲染器逻辑实现
// ---------------------------------------------------------------------

namespace GE {

void Renderer::Init() {
    RenderCommand::Init();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
	// 调整渲染视口以匹配新的窗口尺寸
	RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene() {
	// 设置清屏颜色并清屏
	RenderCommand::SetClearColor({0.2f, 0.3f, 0.3f, 1.0f});
	RenderCommand::Clear();
}

void Renderer::EndScene() {
	// 结束场景，目前为空
}

void Renderer::Submit(const Ref<Shader>& shader, 
                      const Ref<VertexArray>& vertexArray, 
                      const Mat4& transform) {
	// 1. 绑定 Shader
	shader->Bind();
	// 2. 上传矩阵 Uniforms
	// 使用抽象接口，无需转换类型
	// 3. 绑定 VertexArray
	vertexArray->Bind();
	
	// 4. 发送绘制命令
	RenderCommand::DrawIndexed(vertexArray);
}
}