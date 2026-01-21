#include "LayerStack.h"
#include "core/Log.h"
namespace GE {

LayerStack::~LayerStack() {
	LOG_INFO_ENGINE("LayerStack::~LayerStack begin (detach {} layers)", m_Layers.size());
	if(m_Layers.size()) {
    	for(const auto& layer : m_Layers) {
        	layer->OnDetach();
    	}
		m_IdToPtr.clear();
		m_PtrToId.clear();
	}
	LOG_INFO_ENGINE("LayerStack::~LayerStack end");
}


void LayerStack::PushLayer(Scope<Layer> layer) {
    Layer* rawLayer = layer.get();
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
    m_LayerInsertIndex++;
	// 注册 id 映射
	if (rawLayer) {
		LayerID id = m_NextLayerID++;
		m_IdToPtr[id] = rawLayer;
		m_PtrToId[rawLayer] = id;
	}
    rawLayer->OnAttach();
}

void LayerStack::PushOverlayer(Scope<Layer> overlayer) {
	Layer* rawOverlayer = overlayer.get();
	m_Layers.emplace_back(std::move(overlayer));
	if (rawOverlayer) {
		LayerID id = m_NextLayerID++;
		m_IdToPtr[id] = rawOverlayer;
		m_PtrToId[rawOverlayer] = id;
	}
	rawOverlayer->OnAttach();    
}

void LayerStack::PopLayer(Layer *layer) {
    auto it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex,
        [layer](const Scope<Layer>& entry) { return entry.get() == layer; });
    if (it != m_Layers.begin() + m_LayerInsertIndex) {
        (*it)->OnDetach();
        // 清理 id 映射
        auto pit = m_PtrToId.find(layer);
        if (pit != m_PtrToId.end()) {
            m_IdToPtr.erase(pit->second);
            m_PtrToId.erase(pit);
        }
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void LayerStack::PopOverlayer(Layer *overlayer) {
    auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(),
        [overlayer](const Scope<Layer>& entry) { return entry.get() == overlayer; });
    if (it != m_Layers.end()) {
        (*it)->OnDetach();
        auto pit = m_PtrToId.find(overlayer);
        if (pit != m_PtrToId.end()) {
            m_IdToPtr.erase(pit->second);
            m_PtrToId.erase(pit);
        }
        m_Layers.erase(it);
    }
}

LayerStack::LayerID LayerStack::PushLayerGetID(Scope<Layer> layer) {
	Layer* rawLayer = layer.get();
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
	m_LayerInsertIndex++;
	LayerID id = 0;
	if (rawLayer) {
		id = m_NextLayerID++;
		m_IdToPtr[id] = rawLayer;
		m_PtrToId[rawLayer] = id;
	}
	rawLayer->OnAttach();
	return id;
}

LayerStack::LayerID LayerStack::PushOverlayerGetID(Scope<Layer> overlayer) {
	Layer* rawOverlayer = overlayer.get();
	m_Layers.emplace_back(std::move(overlayer));
	LayerID id = 0;
	if (rawOverlayer) {
		id = m_NextLayerID++;
		m_IdToPtr[id] = rawOverlayer;
		m_PtrToId[rawOverlayer] = id;
	}
	rawOverlayer->OnAttach();
	return id;
}

bool LayerStack::IsValid(LayerID id) const {
	return m_IdToPtr.find(id) != m_IdToPtr.end();
}

Layer* LayerStack::GetLayer(LayerID id) const {
	auto it = m_IdToPtr.find(id);
	return it != m_IdToPtr.end() ? it->second : nullptr;
}


void LayerStack::PopLayer(LayerID id) {
	auto it = m_IdToPtr.find(id);
	if (it == m_IdToPtr.end()) return;
	Layer* ptr = it->second;
	PopLayer(ptr);
}

void LayerStack::PopOverlayer(LayerID id) {
	auto it = m_IdToPtr.find(id);
	if (it == m_IdToPtr.end()) return;
	Layer* ptr = it->second;
	PopOverlayer(ptr);
}

void LayerStack::Clear() {
	LOG_INFO_ENGINE("LayerStack::Clear begin (detach {} layers)", m_Layers.size());
	for (const auto& layer : m_Layers) {
		layer->OnDetach();
	}
	// 显式清理容器
	m_Layers.clear();
	m_LayerInsertIndex = 0;
	m_IdToPtr.clear();
	m_PtrToId.clear();
	LOG_INFO_ENGINE("LayerStack::Clear end");
}
}