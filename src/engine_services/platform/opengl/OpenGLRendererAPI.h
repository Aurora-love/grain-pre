#pragma once
#include "engine_services/renderer/RendererAPI.h"

namespace GE {
class OpenGLRendererAPI : public RendererAPI {
public:
	virtual void Init() override;
	virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	virtual void SetClearColor(const Vec4& color) override;
	virtual void Clear() override;
	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
};
}
