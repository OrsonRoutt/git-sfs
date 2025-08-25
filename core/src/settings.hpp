#pragma once

#include <filesystem>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>

namespace core {
	constexpr const std::streamsize SETTING_SIZE = 128;

	inline void read_setting(std::ifstream& file, char* buf, std::filesystem::path& path) {
		file.getline(buf, SETTING_SIZE);
		if (file.fail()) throw std::runtime_error("Failed to read line of settings file at '" + path.string() + "'.");
	}

	struct sfs_settings {
		std::filesystem::path dir;
		std::string git_filename;
		std::streamsize git_line_size;
		char* git_delim;
		std::streamsize filesize;
		std::string extension;

		inline sfs_settings(std::filesystem::path& dir, std::string& git_filename, std::streamsize git_line_size, char* git_delim, std::streamsize filesize, std::string extension) : dir(dir), git_filename(git_filename), git_line_size(git_line_size), git_delim(git_delim), filesize(filesize), extension(extension) {}

		inline ~sfs_settings() {
			std::free(git_delim);
		}
	};

	inline sfs_settings load_settings(std::filesystem::path& dir, const char* filename) {
		std::filesystem::path path = dir / filename;
		std::ifstream file(path);
		if (!file.is_open()) throw std::runtime_error("Failed to open settings file at '" + path.string() + "'.");
		char buf[SETTING_SIZE];
		read_setting(file, buf, path);
		std::string git_filename = buf;
		read_setting(file, buf, path);
		std::streamsize git_line_size;
		try {
			git_line_size = std::stol(buf);
		} catch (std::exception const&) {
			throw std::runtime_error("Failed to convert git line size setting to long, '" + std::string(buf) + "' at '" + path.string() + "', line 2.");
		}
		read_setting(file, buf, path);
		char* git_delim = static_cast<char*>(std::malloc(std::strlen(buf) + 1));
		std::strcpy(git_delim, buf);
		read_setting(file, buf, path);
		std::streamsize filesize;
		try {
			filesize = std::stol(buf);
		} catch (std::exception const&) {
			throw std::runtime_error("Failed to convert filesize setting to long, '" + std::string(buf) + "' at '" + path.string() + "', line 4.");
		}
		read_setting(file, buf, path);
		std::string extension = buf;
		file.close();
		return sfs_settings(dir, git_filename, git_line_size, git_delim, filesize, extension);
	}
}
