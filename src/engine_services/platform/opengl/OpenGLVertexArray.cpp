#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace GE {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
	switch (type) {
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
	}
	ASSERT_ENGINE(false, "Unknown ShaderDataType!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
	glGenVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const {
	glBindVertexArray(0);
}
// 添加顶点缓冲区
// 核心逻辑：遍历 VertexBuffer 的 Layout，为每个属性调用 glEnableVertexAttribArray 和 glVertexAttribPointer
void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
	ASSERT_ENGINE(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout) {
		glEnableVertexAttribArray(m_VertexBufferIndex);
		glVertexAttribPointer(m_VertexBufferIndex,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.Offset);
		m_VertexBufferIndex++;
	}
	m_VertexBuffers.push_back(vertexBuffer);
}
// 设置索引缓冲区
// 注意：VAO 也会记录当前的 GL_ELEMENT_ARRAY_BUFFER 绑定状态
void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}
}