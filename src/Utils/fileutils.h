#pragma once

#include <fstream>
#include <string>

struct Utils {

	static std::string read_file(const std::string& filepath) {
		return {
		std::istreambuf_iterator<char>(std::ifstream(filepath).rdbuf()),
		std::istreambuf_iterator<char>()
		};
	}
};
