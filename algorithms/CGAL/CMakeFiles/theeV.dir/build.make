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
CMAKE_SOURCE_DIR = /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms

# Include any dependencies generated for this target.
include CMakeFiles/theeV.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/theeV.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/theeV.dir/flags.make

CMakeFiles/theeV.dir/theeV.cpp.o: CMakeFiles/theeV.dir/flags.make
CMakeFiles/theeV.dir/theeV.cpp.o: theeV.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/theeV.dir/theeV.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/theeV.dir/theeV.cpp.o -c /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms/theeV.cpp

CMakeFiles/theeV.dir/theeV.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/theeV.dir/theeV.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms/theeV.cpp > CMakeFiles/theeV.dir/theeV.cpp.i

CMakeFiles/theeV.dir/theeV.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/theeV.dir/theeV.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms/theeV.cpp -o CMakeFiles/theeV.dir/theeV.cpp.s

CMakeFiles/theeV.dir/theeV.cpp.o.requires:
.PHONY : CMakeFiles/theeV.dir/theeV.cpp.o.requires

CMakeFiles/theeV.dir/theeV.cpp.o.provides: CMakeFiles/theeV.dir/theeV.cpp.o.requires
	$(MAKE) -f CMakeFiles/theeV.dir/build.make CMakeFiles/theeV.dir/theeV.cpp.o.provides.build
.PHONY : CMakeFiles/theeV.dir/theeV.cpp.o.provides

CMakeFiles/theeV.dir/theeV.cpp.o.provides.build: CMakeFiles/theeV.dir/theeV.cpp.o

# Object files for target theeV
theeV_OBJECTS = \
"CMakeFiles/theeV.dir/theeV.cpp.o"

# External object files for target theeV
theeV_EXTERNAL_OBJECTS =

theeV: CMakeFiles/theeV.dir/theeV.cpp.o
theeV: CMakeFiles/theeV.dir/build.make
theeV: /usr/lib/x86_64-linux-gnu/libmpfr.so
theeV: /usr/lib/x86_64-linux-gnu/libgmp.so
theeV: /usr/local/lib/libCGAL_Core.so
theeV: /usr/local/lib/libCGAL.so
theeV: /usr/lib/x86_64-linux-gnu/libboost_thread.so
theeV: /usr/lib/x86_64-linux-gnu/libboost_system.so
theeV: /usr/lib/x86_64-linux-gnu/libpthread.so
theeV: /usr/local/lib/libCGAL_Core.so
theeV: /usr/local/lib/libCGAL.so
theeV: /usr/lib/x86_64-linux-gnu/libboost_thread.so
theeV: /usr/lib/x86_64-linux-gnu/libboost_system.so
theeV: /usr/lib/x86_64-linux-gnu/libpthread.so
theeV: CMakeFiles/theeV.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable theeV"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/theeV.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/theeV.dir/build: theeV
.PHONY : CMakeFiles/theeV.dir/build

CMakeFiles/theeV.dir/requires: CMakeFiles/theeV.dir/theeV.cpp.o.requires
.PHONY : CMakeFiles/theeV.dir/requires

CMakeFiles/theeV.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/theeV.dir/cmake_clean.cmake
.PHONY : CMakeFiles/theeV.dir/clean

CMakeFiles/theeV.dir/depend:
	cd /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms /home/jonathan/Documents/Algolab/tutorialprograms/cgalprograms/CMakeFiles/theeV.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/theeV.dir/depend
