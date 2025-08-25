#pragma once

// Taken from https://stackoverflow.com/a/4541470/20911317.

#include <string>

#ifdef __GNUG__

#include <cstdlib>
#include <memory>
#include <cxxabi.h>

namespace core {
	inline std::string demangle(const char* name) {
		int status = -4;
		std::unique_ptr<char, void(*)(void*)> res {
			abi::__cxa_demangle(name, NULL, NULL, &status),
			std::free
		};
		return (status==0) ? res.get() : name;
	}
}

#else

namespace core {
	inline std::string demangle(const char* name) {
		return name;
	}
}

#endif
