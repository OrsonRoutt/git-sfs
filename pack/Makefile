# Detect platform.
ifeq ($(OS),Windows_NT)
UNAME := Windows
else
UNAME := $(shell uname -s)
endif

# Executables.
ifeq ($(UNAME),Darwin)
CXX := g++-15
else
CXX := g++
endif
PKGCONFIG := pkg-config
# Compiler flags.
CXXFLAGS := -Wall -std=c++20 -I../shared
ifeq ($(UNAME),Windows) # Platform defines
CXXFLAGS += -DWindows -static
else ifeq ($(UNAME),Darwin)
CXXFLAGS += -DDarwin
else ifeq ($(UNAME),Linux)
CXXFLAGS += -DLinux
endif
CXXOBJFLAGS := -MMD
CXXTARGETFLAGS :=
CXXDEBUGFLAGS := -DDEBUG
CXXRELEASEFLAGS := -O3 -flto=auto -march=native -mtune=native
ifneq ($(UNAME),Windows)
CXXLIBFLAGS := -static-libgcc -static-libstdc++
endif
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

$(BUILDDIRS): # Make any build directories that don't exist.
ifeq ($(UNAME),Windows)
	mkdir $(subst /,\,$(BUILDDIRS))
else
	mkdir -p $(BUILDDIRS)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp # Build an object file from a source file.
	$(CXX) $(LIBFLAGS) $(CXXOBJFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)
