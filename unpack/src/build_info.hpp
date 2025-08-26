#pragma once
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <iostream>
#include <cstring>
#include <cstdlib>

// Detect compiler version.
#if defined(__GNUC__)
#define CXX "GCC"
#define CXXVERSION __VERSION__
#elif defined(__clang__)
#define CXX "Clang"
#define CXXVERSION __VERSION__
#elif defined(_MSC_VER)
#define CXX "MSVC"
#define CXXVERSION _MSC_FULL_VER
#else
#define CXX "???"
#define CXXVERSION "???"
#endif


// Project information.
constexpr const char PROJECT_NAME[] = "sfs-unpack";
constexpr const unsigned char PROJECT_VERSION_MAJOR = 1;
constexpr const unsigned char PROJECT_VERSION_MINOR = 0;
constexpr const unsigned char PROJECT_VERSION_PATCH = 1;

// Gets the project version as a `const char*`.
inline const char* get_version() {
	char buf[13];
	int size = std::sprintf(buf, "v%u.%u.%u", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH);
	char* out = reinterpret_cast<char*>(malloc(size));
	strcpy(out, buf);
	return out;
}

// Prints the compiler and project version.
inline void prog_info() {
	std::cout << "Built with " << CXX << ": " << CXXVERSION << "\nC++ version is: " << __cplusplus << "\nProject version is: " << PROJECT_NAME << " " << get_version() << "\n";
}
