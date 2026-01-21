#pragma once
#include "core/Core.h"
#include "engine_services/core/Layer.h"
#include <vector>
#include <unordered_map>

namespace GE {
/**
 * @brief LayerStack 管理所有的 Layer 实例。
 *
 * - 层的所有权由 LayerStack 内部使用 `Scope<Layer>`（即 `std::unique_ptr<Layer>`）独占管理。
 * - 为了避免把裸指针暴露给外部导致的悬垂风险，使用基于 `LayerID` 的受控观察接口：
 *   PushLayerGetID / PushOverlayerGetID 返回一个 `LayerID`，外部可以保存该 ID 作为句柄。
 *   使用 `IsValid(id)` 或 `GetLayer(id)` 在使用前检查对象是否依然存在。
 * - 保留原有的 Push/Pop 接口以保持向后兼容。外部可根据需要选择使用裸指针短期访问或 ID 长期观察。
 *
 * 线程与生命周期说明：
 * - 本类没有内置线程同步；在多线程环境中，调用者需自行保证并发安全（例如外层加锁）。
 * - 当通过 `PopLayer`/`PopOverlayer` 移除 Layer 时，会调用 `OnDetach()`，随后 `unique_ptr` 释放对象，
 *   对应的 `LayerID` 在内部映射中被删除，因此 `IsValid(oldId)` 将返回 false。
 */
class LayerStack {
public:
	LayerStack() = default;
	~LayerStack();
/**
 * @brief 将一个普通层插入到层栈中（在 Layer 部分末尾插入）。
 * @param layer 通过 `Scope<Layer>`（unique_ptr）传入，调用后所有权会被移动到 LayerStack。
 */
	void PushLayer(Scope<Layer> layer);

/**
 * @brief 将一个覆盖层（Overlayer）添加到层栈末尾（覆盖层位于普通层之后）。
 * @param overlayer 通过 `Scope<Layer>`（unique_ptr）传入，调用后所有权会被移动到 LayerStack。
 */
	void PushOverlayer(Scope<Layer> overlayer);

// --------- 受控观察（ID 句柄）接口 ---------
/**
 * @brief Layer 的句柄类型（用于外部安全持有引用）。
 * 外部可以保存 `LayerID` 而不是裸指针，以便在 Layer 被移除后通过 `IsValid` 检查有效性。
 */
	using LayerID = uint32_t;

/**
 * @brief 插入普通层并返回其 `LayerID`。
 * 返回值为非零的唯一 ID；如果返回 0 表示未成功。
 */
	LayerID PushLayerGetID(Scope<Layer> layer);

/**
 * @brief 插入覆盖层并返回其 `LayerID`。
 */
	LayerID PushOverlayerGetID(Scope<Layer> overlayer);

/**
 * @brief 检查给定 `LayerID` 对应的 Layer 是否仍然存在（未被弹出或销毁）。
 * @param id 要检查的句柄。
 * @return true 如果句柄有效且能通过 `GetLayer` 获取到指针；否则返回 false。
 */
	bool IsValid(LayerID id) const;

/**
 * @brief 通过 `LayerID` 获取裸指针（非拥有者）。
 * @param id 要查询的句柄。
 * @return 指向 Layer 的裸指针；若句柄无效则返回 nullptr。
 * 返回的裸指针仅供短期使用；若需要长期保存引用，请在每次使用前调用 `IsValid`。
 */
	Layer* GetLayer(LayerID id) const;

/**
 * @brief 通过 ID 弹出并销毁对应的普通层（等价于按指针版本）。
 * @param id 要弹出的 Layer 的句柄。
 */
	void PopLayer(LayerID id);

/**
 * @brief 通过 ID 弹出并销毁对应的覆盖层（等价于按指针版本）。
 */
	void PopOverlayer(LayerID id);

// --------- 兼容旧 API（指针版本） ---------
/**
 * @brief 通过裸指针弹出普通层。
 * 这是兼容接口：若外部在短期内持有裸指针可以直接调用此函数。调用后会清理与该层关联的 ID 映射。
 */
	void PopLayer(Layer* layer);
    
/**
 * @brief 通过裸指针弹出覆盖层（兼容接口）。
 */
	void PopOverlayer(Layer* overlayer);

	void Clear();

// 迭代器接口，允许遍历当前存储的 Layer（返回的元素为 Scope<Layer>）
	std::vector<Scope<Layer>>::iterator begin() { return m_Layers.begin(); }
	std::vector<Scope<Layer>>::iterator end() { return m_Layers.end(); }
	std::vector<Scope<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
	std::vector<Scope<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

	std::vector<Scope<Layer>>::const_iterator begin() const { return m_Layers.begin(); }
	std::vector<Scope<Layer>>::const_iterator end()	const { return m_Layers.end(); }
	std::vector<Scope<Layer>>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
	std::vector<Scope<Layer>>::const_reverse_iterator rend() const { return m_Layers.rend(); }

private:
	// Layer 的独占所有权容器：保留插入索引以区分普通层与覆盖层
	std::vector<Scope<Layer>> m_Layers;
	uint32_t m_LayerInsertIndex = 0;

	// ---------- ID 管理 ----------
	// 下一个分配的 LayerID（从 1 开始，0 表示无效）
	LayerID m_NextLayerID = 1;
	// 从 ID 到裸指针的映射（用于快速通过 ID 获取指针）
	std::unordered_map<LayerID, Layer*> m_IdToPtr;
	// 从裸指针到 ID 的反向映射（用于在按指针弹出时清理对应 ID）
	std::unordered_map<Layer*, LayerID> m_PtrToId;
};
}