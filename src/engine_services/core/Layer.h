#pragma once
#include "core/events/Event.h"
#include <string>
namespace GE {

class Layer {
public:
    Layer(const std::string& name = "layer");
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(Event&) {}
    
    inline const std::string& GetName() const { return m_DebugName; } 
protected:
    std::string m_DebugName;
};
}