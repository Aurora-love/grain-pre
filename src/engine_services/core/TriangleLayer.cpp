#include "TriangleLayer.h"
#include "engine_services/renderer/Renderer.h"

namespace GE {

TriangleLayer::TriangleLayer() : Layer("TriangleLayer") {}

void TriangleLayer::OnAttach() {
    // 定义三角形的顶点数据 (位置)
    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // 创建顶点缓冲
    Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

    // 设置缓冲布局
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" }
    };
    vertexBuffer->SetLayout(layout);

    // 创建顶点数组并添加顶点缓冲
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // 不使用索引缓冲区，直接绘制顶点

    // 创建着色器
    std::string vertexSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 a_Position;
        void main() {
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core
        out vec4 color;
        void main() {
            color = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";

    m_Shader = Shader::Create("TriangleShader", vertexSrc, fragmentSrc);
}

void TriangleLayer::OnDetach() {
    // 清理资源 (智能指针会自动处理)
}

void TriangleLayer::OnRender() {
    // 提交渲染任务
    //LOG_INFO("TriangleLayer::OnRender called");
    Renderer::Submit(m_Shader, m_VertexArray);
}

}