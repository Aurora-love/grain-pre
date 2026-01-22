#pragma once
#include "core/events/Event.h"
#include "core/CoreTime.h"
#include <string>
namespace GE {

class Layer {
public:
    Layer(const std::string& name = "layer");
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(Timestep) {}
    virtual void OnRender() {}
    virtual void OnEvent(Event&) {}
    virtual void OnImGuiRender() {}
    
    inline const std::string& GetName() const { return m_DebugName; } 
protected:
    std::string m_DebugName;
};
}