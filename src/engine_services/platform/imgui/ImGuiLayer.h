#pragma once
#include "engine_services/core/Layer.h"
#include "core/events/Event.h"

namespace GE {
//ImGui 的初始化、样式/fonts、输入阻塞、Begin/End、最终提交（引擎级、平台绑定、保证在最上层）
class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Event&) override;
    //绘制 ImGuiLayer 自身的 UI（UI声明）
    virtual void OnImGuiRender() override;
    //NewFrame
    void Begin();
    //渲染指令提交和多视口窗口更新
    void End();
    void BlockEvents(bool block) { m_BlockEvents = block; }
private:
    float m_Time = 0.0f;
    bool m_BlockEvents = true;
    // 保存初始化时的 GLFW 窗口指针，用于在 OnDetach 恢复上下文
    void* m_Window = nullptr;
};
}