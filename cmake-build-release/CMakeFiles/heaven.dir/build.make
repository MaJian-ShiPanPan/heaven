# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/x64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mac/CLionProjects/heaven

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mac/CLionProjects/heaven/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/heaven.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/heaven.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/heaven.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/heaven.dir/flags.make

CMakeFiles/heaven.dir/main.cpp.o: CMakeFiles/heaven.dir/flags.make
CMakeFiles/heaven.dir/main.cpp.o: /Users/mac/CLionProjects/heaven/main.cpp
CMakeFiles/heaven.dir/main.cpp.o: CMakeFiles/heaven.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mac/CLionProjects/heaven/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/heaven.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/heaven.dir/main.cpp.o -MF CMakeFiles/heaven.dir/main.cpp.o.d -o CMakeFiles/heaven.dir/main.cpp.o -c /Users/mac/CLionProjects/heaven/main.cpp

CMakeFiles/heaven.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/heaven.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mac/CLionProjects/heaven/main.cpp > CMakeFiles/heaven.dir/main.cpp.i

CMakeFiles/heaven.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/heaven.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mac/CLionProjects/heaven/main.cpp -o CMakeFiles/heaven.dir/main.cpp.s

# Object files for target heaven
heaven_OBJECTS = \
"CMakeFiles/heaven.dir/main.cpp.o"

# External object files for target heaven
heaven_EXTERNAL_OBJECTS =

heaven: CMakeFiles/heaven.dir/main.cpp.o
heaven: CMakeFiles/heaven.dir/build.make
heaven: CMakeFiles/heaven.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mac/CLionProjects/heaven/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable heaven"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/heaven.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/heaven.dir/build: heaven
.PHONY : CMakeFiles/heaven.dir/build

CMakeFiles/heaven.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/heaven.dir/cmake_clean.cmake
.PHONY : CMakeFiles/heaven.dir/clean

CMakeFiles/heaven.dir/depend:
	cd /Users/mac/CLionProjects/heaven/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mac/CLionProjects/heaven /Users/mac/CLionProjects/heaven /Users/mac/CLionProjects/heaven/cmake-build-release /Users/mac/CLionProjects/heaven/cmake-build-release /Users/mac/CLionProjects/heaven/cmake-build-release/CMakeFiles/heaven.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/heaven.dir/depend
