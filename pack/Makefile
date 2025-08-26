# Detect platform.
ifeq ($(OS),Windows_NT)
UNAME := Windows
else
UNAME := $(shell uname -s)
endif

# Executables.
ifeq ($(UNAME),Windows)
CXX := g++
else
CXX := g++-15
endif
PKGCONFIG := pkg-config
# Compiler flags.
CXXFLAGS := -Wall -std=c++20 -I../shared
ifeq ($(UNAME),Windows)
CXXFLAGS += -DWINDOWS -static
endif
CXXOBJFLAGS := -MMD
ifneq ($(UNAME),Windows)
CXXTARGETFLAGS := -rpath @executable_path/libs
endif
CXXDEBUGFLAGS := -DDEBUG
CXXRELEASEFLAGS := -O3 -flto=auto -march=native -mtune=native
ifneq ($(UNAME),Windows)
CXXLIBFLAGS := -static-libgcc -static-libstdc++
endif
CXXLIBFLAGS :=
# 'pkg-config'-searchable libs.
PKGLIBS :=
# Binary directory.
BINDIR := bin
# Target executable name.
TARGETNAME := sfs-pack
ifeq ($(UNAME),Windows)
TARGETNAME := $(TARGETNAME).exe
endif
# Object directory.
OBJDIR := obj
# Source directory.
SRCDIR := src

TARGET := $(BINDIR)/$(TARGETNAME) # Target executable.
SRCSUBDIRS := $(filter %/,$(wildcard $(SRCDIR)/*/)) # Source subdirectories.
SRCDIRS := $(SRCDIR)/ $(SRCSUBDIRS) # All source directories.
ifeq ($(PKGLIBS),)
LIBFLAGS := $(CXXLIBFLAGS)
else
LIBFLAGS := $(shell $(PKGCONFIG) $(PKGLIBS) --cflags --libs) $(CXXLIBFLAGS) # All compiler flags related to libraries/including.
endif
BUILDDIRS := $(BINDIR) $(OBJDIR) $(SRCSUBDIRS:$(SRCDIR)/%=$(OBJDIR)/%) # Directories to create before building.
SRCS := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)*.cpp)) # Source files.
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o) # Corresponding object files for source files.
DEPS := $(OBJS:%.o=%.d) # Corresponding dependency files for source files.

# Default target.
all: debug

# Build the executable with debug flags.
debug: CXXFLAGS += $(CXXDEBUGFLAGS)
debug: $(TARGET)

# Build the executable with release flags.
release: CXXFLAGS += $(CXXRELEASEFLAGS)
release: $(TARGET)

# Remove all build files.
clean:
ifeq ($(UNAME),Windows)
	del $(subst /,\,$(TARGET))
	del /S /Q $(subst /,\,$(OBJDIR))\*
else
	rm $(TARGET)||:
	rm -r $(OBJDIR)/*||:
endif

$(TARGET): $(BUILDDIRS) $(OBJS) # Build the target executable.
	$(CXX) $(LIBFLAGS) $(CXXTARGETFLAGS) $(CXXFLAGS) -o $(TARGET) $(OBJS)
ifeq ($(UNAME),Darwin)
	-install_name_tool -delete_rpath "@loader_path" -delete_rpath "/usr/local/Cellar/gcc/15.1.0/lib/gcc/current/gcc/x86_64-apple-darwin24/15" -delete_rpath "/usr/local/Cellar/gcc/15.1.0/lib/gcc/current/gcc" -delete_rpath "/usr/local/Cellar/gcc/15.1.0/lib/gcc/current" -change "/usr/local/opt/gcc/lib/gcc/current/libstdc++.6.dylib" "@rpath/libstdc++.6.dylib" -change "/usr/local/opt/gcc/lib/gcc/current/libgcc_s.1.1.dylib" "@rpath/libgcc_s.1.1.dylib" $(TARGET)
endif

$(BUILDDIRS): # Make any build directories that don't exist.
ifeq ($(UNAME),Windows)
	mkdir $(subst /,\,$(BUILDDIRS))
else
	mkdir -p $(BUILDDIRS)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp # Build an object file from a source file.
	$(CXX) $(LIBFLAGS) $(CXXOBJFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)
