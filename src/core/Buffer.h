#pragma once
#include <cstdint>
#include <cstring>
#include <numeric>

namespace GE {
/**
 * @brief 二进制数据缓冲区
 * 
 * 代表一块原始内存数据。用于替代 void*，以此更安全地管理资产加载（如读取图片文件的二进制流）。
 * 该结构体拥有数据的所有权 (Ownership)。
 */
struct Buffer {
	uint8_t* Data = nullptr;
	uint64_t Size = 0;
	Buffer() = default;
	// 分配内存
	Buffer(uint64_t size) {
		Allocate(size);
	}
	// 拷贝构造 (深拷贝)
	Buffer(const Buffer& other) {
		Allocate(other.Size);
		if (other.Data)
			memcpy(Data, other.Data, Size);
	}
	// 移动构造
	Buffer(Buffer&& other) noexcept : Data(other.Data), Size(other.Size) {
		other.Data = nullptr;
		other.Size = 0;
	}
	~Buffer() {
		Release();
	}
	// 允许深拷贝赋值
	Buffer& operator=(const Buffer& other) {
		if (this != &other) {
			Release();
			Allocate(other.Size);
			if (other.Data) memcpy(Data, other.Data, Size);
		}
		return *this;
	}
	// 允许移动赋值
	Buffer& operator=(Buffer&& other) noexcept {
		if (this != &other) {
			Release();
			Data = other.Data;
			Size = other.Size;
			other.Data = nullptr;
			other.Size = 0;
		}
		return *this;
	}
	static Buffer Copy(const void* data, uint64_t size) {
		Buffer buffer;
		buffer.Allocate(size);
		memcpy(buffer.Data, data, size);
		return buffer;
	}
	void Allocate(uint64_t size) {
		Release();
		if (size == 0) return;
		Data = new uint8_t[size];
		Size = size;
	}
	void Release() {
		delete[] Data;
		Data = nullptr;
		Size = 0;
	}
	void ZeroInitialize() {
		if (Data)
			memset(Data, 0, Size);
	}
	template<typename T>
	T* As() {
		return (T*)Data;
	}
	operator bool() const {
		return Data;
	}
};
}