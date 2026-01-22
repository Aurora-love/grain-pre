#pragma once
#include "engine_services/core/Layer.h"
#include "engine_services/renderer/Shader.h"
#include "engine_services/renderer/VertexArray.h"
#include "engine_services/renderer/Buffer.h"

namespace GE {

class TriangleLayer : public Layer {
public:
    TriangleLayer();
    virtual ~TriangleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnRender() override;

private:
    Ref<Shader> m_Shader;
    Ref<VertexArray> m_VertexArray;
};

}