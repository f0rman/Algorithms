# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jonathan/Documents/Algolab/CGAL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonathan/Documents/Algolab/CGAL

# Include any dependencies generated for this target.
include CMakeFiles/graypes.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/graypes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graypes.dir/flags.make

CMakeFiles/graypes.dir/graypes.cpp.o: CMakeFiles/graypes.dir/flags.make
CMakeFiles/graypes.dir/graypes.cpp.o: graypes.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jonathan/Documents/Algolab/CGAL/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/graypes.dir/graypes.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/graypes.dir/graypes.cpp.o -c /home/jonathan/Documents/Algolab/CGAL/graypes.cpp

CMakeFiles/graypes.dir/graypes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graypes.dir/graypes.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jonathan/Documents/Algolab/CGAL/graypes.cpp > CMakeFiles/graypes.dir/graypes.cpp.i

CMakeFiles/graypes.dir/graypes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graypes.dir/graypes.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jonathan/Documents/Algolab/CGAL/graypes.cpp -o CMakeFiles/graypes.dir/graypes.cpp.s

CMakeFiles/graypes.dir/graypes.cpp.o.requires:
.PHONY : CMakeFiles/graypes.dir/graypes.cpp.o.requires

CMakeFiles/graypes.dir/graypes.cpp.o.provides: CMakeFiles/graypes.dir/graypes.cpp.o.requires
	$(MAKE) -f CMakeFiles/graypes.dir/build.make CMakeFiles/graypes.dir/graypes.cpp.o.provides.build
.PHONY : CMakeFiles/graypes.dir/graypes.cpp.o.provides

CMakeFiles/graypes.dir/graypes.cpp.o.provides.build: CMakeFiles/graypes.dir/graypes.cpp.o

# Object files for target graypes
graypes_OBJECTS = \
"CMakeFiles/graypes.dir/graypes.cpp.o"

# External object files for target graypes
graypes_EXTERNAL_OBJECTS =

graypes: CMakeFiles/graypes.dir/graypes.cpp.o
graypes: CMakeFiles/graypes.dir/build.make
graypes: /usr/lib/x86_64-linux-gnu/libmpfr.so
graypes: /usr/lib/x86_64-linux-gnu/libgmp.so
graypes: /usr/local/lib/libCGAL_Core.so
graypes: /usr/local/lib/libCGAL.so
graypes: /usr/lib/x86_64-linux-gnu/libboost_thread.so
graypes: /usr/lib/x86_64-linux-gnu/libboost_system.so
graypes: /usr/lib/x86_64-linux-gnu/libpthread.so
graypes: /usr/local/lib/libCGAL_Core.so
graypes: /usr/local/lib/libCGAL.so
graypes: /usr/lib/x86_64-linux-gnu/libboost_thread.so
graypes: /usr/lib/x86_64-linux-gnu/libboost_system.so
graypes: /usr/lib/x86_64-linux-gnu/libpthread.so
graypes: CMakeFiles/graypes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable graypes"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graypes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graypes.dir/build: graypes
.PHONY : CMakeFiles/graypes.dir/build

CMakeFiles/graypes.dir/requires: CMakeFiles/graypes.dir/graypes.cpp.o.requires
.PHONY : CMakeFiles/graypes.dir/requires

CMakeFiles/graypes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graypes.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graypes.dir/clean

CMakeFiles/graypes.dir/depend:
	cd /home/jonathan/Documents/Algolab/CGAL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonathan/Documents/Algolab/CGAL /home/jonathan/Documents/Algolab/CGAL /home/jonathan/Documents/Algolab/CGAL /home/jonathan/Documents/Algolab/CGAL /home/jonathan/Documents/Algolab/CGAL/CMakeFiles/graypes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graypes.dir/depend
