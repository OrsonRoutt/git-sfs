#pragma once

#include <vector>

#include "settings.hpp"

namespace core {
	inline std::vector<std::filesystem::path> gitignore_get_paths(sfs_settings& settings) {
		std::filesystem::path path = settings.dir / settings.git_filename;
		std::ifstream file(path);
		if (!file.is_open()) throw std::runtime_error("Failed to open gitignore at '" + path.string() + "'.");
		std::vector<std::filesystem::path> paths;
		bool found = false;
		char* buf = static_cast<char*>(std::malloc(settings.git_line_size));
		while (!file.eof()) {
			file.getline(buf, settings.git_line_size);
			if (file.fail()) throw std::runtime_error("Failed to read line of gitignore at '" + path.string() + "'.");
			if (found) {
				paths.emplace_back(settings.dir / buf);
			} else {
				if (std::strcmp(buf, settings.git_delim) == 0) {
					found = true;
				}
			}
		}
		std::free(buf);
		file.close();
		return paths;
	}
}
