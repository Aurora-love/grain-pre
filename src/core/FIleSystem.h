#pragma once
#include <string>
#include <filesystem>
#include <optional>
#include "core/Buffer.h"

namespace GE {

class FileSystem {
public:
	static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	static std::string ReadFileText(const std::filesystem::path& filepath);
	static bool WriteFileText(const std::filesystem::path& filepath, const std::string& content);
};
}
