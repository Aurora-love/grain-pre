#pragma once
#include "engine_services/core/GraphicsContext.h"

struct GLFWwindow;

namespace GE {

class OpenGLContext : public IGraphicsContext {
public:
    OpenGLContext(GLFWwindow* windowHandle);
    virtual void InitContext() override;
    virtual void SwapBuffers() override;
private:
    GLFWwindow* m_WindowHandle;
};
}