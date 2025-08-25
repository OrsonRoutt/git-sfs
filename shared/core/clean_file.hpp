#pragma once

#include "settings.hpp"

namespace core {
	inline void clean_file(core::sfs_settings& settings, std::filesystem::path& path) {
		uint32_t count = 1;
		std::filesystem::path chunk = path;
		chunk += ("." + std::to_string(count) + "." + settings.extension);
		while (std::filesystem::remove(chunk)) {
			count += 1;
			chunk = path;
			chunk += ("." + std::to_string(count) + "." + settings.extension);
		}
	}
}
