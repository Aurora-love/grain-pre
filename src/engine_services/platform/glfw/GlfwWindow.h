#pragma once
#include "engine_services/core/Window.h"
#include "engine_services/core/GraphicsContext.h"
struct GLFWwindow;
namespace GE {

class GlfwWindow : public IWindow {
public:
    GlfwWindow(const WindowProps& props);
    ~GlfwWindow();
    void Update() override;
    inline uint32_t GetWidth() const override { return m_Data.width; }
    inline uint32_t GetHeight() const override { return m_Data.height; }
    inline void* GetNativeWindow() const override { return m_Window; }
    inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback;}
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;
private:
    void Init(const WindowProps& props);
    void Shutdown();
    GLFWwindow* m_Window;
    Scope<IGraphicsContext> m_Context;
    struct WindowData {
        std::string title;
        uint32_t width, height;
        bool VSync;
        EventCallbackFn eventCallback;
    };
    WindowData m_Data;
};
}