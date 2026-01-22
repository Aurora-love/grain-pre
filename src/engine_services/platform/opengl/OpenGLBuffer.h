#pragma once
#include "engine_services/renderer/Buffer.h"

// ---------------------------------------------------------------------
// 类: OpenGLVertexBuffer / OpenGLIndexBuffer
// 作用: OpenGL 缓冲区的具体实现
// 描述: 分别实现了 VertexBuffer 和 IndexBuffer 接口。
//       内部维护了 OpenGL 的 Buffer ID (m_RendererID)，并调用 glGenBuffers, glBufferData 等 API。
// ---------------------------------------------------------------------

namespace GE {

class OpenGLVertexBuffer : public VertexBuffer {
public:
	OpenGLVertexBuffer(uint32_t size);
	OpenGLVertexBuffer(float* vertices, uint32_t size);
	virtual ~OpenGLVertexBuffer();
	virtual void Bind() const override;
	virtual void Unbind() const override;
	virtual void SetData(const void* data, uint32_t size) override;
	virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	virtual uint32_t GetSize() const override { return m_Size; }
private:
	uint32_t m_RendererID;
	BufferLayout m_Layout;
	uint32_t m_Size;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
	OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	virtual ~OpenGLIndexBuffer();
	virtual void Bind() const override;
	virtual void Unbind() const override;
	virtual uint32_t GetCount() const override { return m_Count; }
private:
	uint32_t m_RendererID;
	uint32_t m_Count;
};
}