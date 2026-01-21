#include "core/FileSystem.h"
#include "core/Log.h"
#include <fstream>
#include <sstream>

namespace GE {
Buffer FileSystem::ReadFileBinary(const std::filesystem::path& filepath) {
	std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
	if (!stream) {
		// TODO: Log error?
		return Buffer();
	}
	std::streampos end = stream.tellg();
	stream.seekg(0, std::ios::beg);
	uint64_t size = end - stream.tellg();
	if (size == 0) {
		// File is empty
		return Buffer();
	}
	Buffer buffer(size);
	stream.read(buffer.As<char>(), size);
	stream.close();
	return buffer;
}

std::string FileSystem::ReadFileText(const std::filesystem::path& filepath) {
	std::string result;
	// 以二进制模式打开以获取准确的文件大小，防止 Windows 下 \r\n 转换导致的大小不匹配问题
	std::ifstream in(filepath, std::ios::in | std::ios::binary); 
	
	if (in) {
		// 获取文件大小
		in.seekg(0, std::ios::end);
		std::streampos pos = in.tellg();
		
		if (pos != std::streampos(-1)) {
			size_t size = static_cast<size_t>(pos);
			result.resize(size);
			// 回到文件开头读取
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
		}
		else {
			LOG_ERROR_ENGINE("Could not read from file '{0}'", filepath.string());
		}
		in.close();
	}
	else {
		LOG_ERROR_ENGINE("Could not open file '{0}'", filepath.string());
	}
	return result;
}

bool FileSystem::WriteFileText(const std::filesystem::path& filepath, const std::string& content) {
	std::ofstream out(filepath, std::ios::out | std::ios::binary);
	if (!out) {
		LOG_ERROR_ENGINE("Could not open file '{0}' for writing", filepath.string());
		return false;
	}
	out.write(content.data(), content.size());
	if (!out) {
		LOG_ERROR_ENGINE("Could not write to file '{0}'", filepath.string());
		return false;
	}
	return true;
}
}