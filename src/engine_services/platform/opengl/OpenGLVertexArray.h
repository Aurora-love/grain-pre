#pragma once
#include "engine_services/renderer/VertexArray.h"

// ---------------------------------------------------------------------
// 类: OpenGLVertexArray
// 作用: OpenGL 顶点数组对象 (VAO) 实现
// 描述: 管理顶点属性和缓冲区的绑定状态。
//       在 AddVertexBuffer 中，会根据 Buffer 的 Layout 自动调用 glVertexAttribPointer。
// ---------------------------------------------------------------------

namespace GE {

class OpenGLVertexArray : public VertexArray {
public:
	OpenGLVertexArray();
	virtual ~OpenGLVertexArray();
	virtual void Bind() const override;
	virtual void Unbind() const override;
	virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
	virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
	virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
	virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
private:
	uint32_t m_RendererID;
	uint32_t m_VertexBufferIndex = 0; // 记录下一个要启用的顶点属性索引 (Attribute Index)
	std::vector<Ref<VertexBuffer>> m_VertexBuffers;
	Ref<IndexBuffer> m_IndexBuffer;
};
}