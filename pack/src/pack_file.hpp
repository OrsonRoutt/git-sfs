#pragma once

#include <iostream>

#include "core/settings.hpp"

inline std::uint32_t pack_file(core::sfs_settings& settings, std::filesystem::path& path) {
	std::uint32_t count = 1;
	std::filesystem::path chunk_path = path;
	chunk_path += ("." + std::to_string(count) + "." + settings.extension);
	std::ifstream chunk_file;
	chunk_file.open(chunk_path);
	if (!chunk_file.is_open()) {
		std::cout << "Failed to open first chunk file for '" << path.string() << "', skipping.\n";
		return 0;
	}
	std::filesystem::remove(path);
	std::ofstream file(path);
	if (!file.is_open()) throw std::runtime_error("Failed to open new SFS file at '" + path.string() + "'.");
	char* buf = static_cast<char*>(std::malloc(settings.filesize));
	while (chunk_file.is_open()) {
		std::streamsize size = chunk_file.readsome(buf, settings.filesize);
		if (chunk_file.fail()) throw std::runtime_error("Failed reading chunk file at '" + chunk_path.string() + "'.");
		if (chunk_file.rdbuf()->in_avail() > 0) throw std::runtime_error("Chunk file at '" + chunk_path.string() + "' is larger than filesize setting allows.");
		file.write(buf, size);
		chunk_file.close();
		count += 1;
		chunk_path = path;
		chunk_path += ("." + std::to_string(count) + "." + settings.extension);
		chunk_file.open(chunk_path);
	}
	file.close();
	std::free(buf);
	return count - 1;
}
