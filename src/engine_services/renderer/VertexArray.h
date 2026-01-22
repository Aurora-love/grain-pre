#pragma once
#include "Buffer.h"

// ---------------------------------------------------------------------
// 类: VertexArray
// 作用: 顶点数组对象 (VAO) 接口
// 描述: VertexArray 是一个容器，它封装了顶点属性的配置。
//       它绑定了 VertexBuffer（包含数据）和 IndexBuffer（包含索引），
//       以及定义了如何解析 VertexBuffer 中的数据（通过 Layout）。
//       使用 VertexArray 可以快速在不同的渲染对象之间切换。
// ---------------------------------------------------------------------

namespace GE {

class VertexArray {
public:
	virtual ~VertexArray() {}
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
	virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

	virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
	virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

	static Ref<VertexArray> Create();
};
}