#pragma once

#include <iostream>

#include "core/clean_file.hpp"

inline std::uint32_t unpack_file(core::sfs_settings& settings, std::filesystem::path& path) {
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Failed to open SFS file at '" << path.string() << "', skipping.\n";
		file.close();
		return 0;
	}
	core::clean_file(settings, path);
	char* buf = static_cast<char*>(std::malloc(settings.filesize));
	std::ofstream out_file;
	std::uint32_t count = 0;
	std::streamsize size = file.readsome(buf, settings.filesize);
	while (size > 0) {
		++count;
		std::filesystem::path out_path = path;
		out_path += ("." + std::to_string(count) + "." + settings.extension);
		out_file.open(out_path, std::ios::binary);
		out_file.write(buf, size);
		out_file.close();
		size = file.readsome(buf, settings.filesize);
	}
	std::free(buf);
	file.close();
	return count;
}
