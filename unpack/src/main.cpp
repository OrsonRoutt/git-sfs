#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <iostream>

#include "build_info.hpp"
#include "core/demangle.hpp"
#include "core/gitignore.hpp"
#include "unpack_file.hpp"

int main(int argc, char *argv[]) {
	try {
		if (argc < 1) throw std::runtime_error("Did not recieve application path in argv.");
		std::filesystem::path dir = argv[0];
		dir.remove_filename();

		#ifdef DEBUG
		prog_info();
		#endif

		core::sfs_settings settings = core::load_settings(dir, "sfs_settings.txt");

		std::vector<std::filesystem::path> paths = core::gitignore_get_paths(settings);
		for (std::filesystem::path path : paths) {
			std::uint32_t count = unpack_file(settings, path);
			if (count > 0) std::cout << "Unpacked '" << path.string() << "' into " << count << " chunks.\n";
		}

		std::cout << "Done.\n";
		#ifdef WINDOWS
		std::cin.get();
		#endif
		return EXIT_SUCCESS;
	} catch (std::exception const& e) {
		std::cerr << "'" << core::demangle(typeid(e).name()) << "': " << e.what() << '\n';
		#ifdef WINDOWS
		std::cin.get();
		#endif
		return EXIT_FAILURE;
	}
}
