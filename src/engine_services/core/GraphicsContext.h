#pragma once
namespace GE {
/** @brief 图形上下文接口 */
class IGraphicsContext {
public:
    virtual ~IGraphicsContext() = default;
    virtual void InitContext() = 0;
    virtual void SwapBuffers() = 0;
};
}