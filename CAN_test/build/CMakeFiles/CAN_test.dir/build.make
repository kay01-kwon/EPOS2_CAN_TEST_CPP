# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kay/Documents/practice/cpp/CAN_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kay/Documents/practice/cpp/CAN_test/build

# Include any dependencies generated for this target.
include CMakeFiles/CAN_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CAN_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CAN_test.dir/flags.make

CMakeFiles/CAN_test.dir/src/CAN_test.cpp.o: CMakeFiles/CAN_test.dir/flags.make
CMakeFiles/CAN_test.dir/src/CAN_test.cpp.o: ../src/CAN_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kay/Documents/practice/cpp/CAN_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CAN_test.dir/src/CAN_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CAN_test.dir/src/CAN_test.cpp.o -c /home/kay/Documents/practice/cpp/CAN_test/src/CAN_test.cpp

CMakeFiles/CAN_test.dir/src/CAN_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CAN_test.dir/src/CAN_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kay/Documents/practice/cpp/CAN_test/src/CAN_test.cpp > CMakeFiles/CAN_test.dir/src/CAN_test.cpp.i

CMakeFiles/CAN_test.dir/src/CAN_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CAN_test.dir/src/CAN_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kay/Documents/practice/cpp/CAN_test/src/CAN_test.cpp -o CMakeFiles/CAN_test.dir/src/CAN_test.cpp.s

# Object files for target CAN_test
CAN_test_OBJECTS = \
"CMakeFiles/CAN_test.dir/src/CAN_test.cpp.o"

# External object files for target CAN_test
CAN_test_EXTERNAL_OBJECTS =

CAN_test: CMakeFiles/CAN_test.dir/src/CAN_test.cpp.o
CAN_test: CMakeFiles/CAN_test.dir/build.make
CAN_test: CMakeFiles/CAN_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kay/Documents/practice/cpp/CAN_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CAN_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CAN_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CAN_test.dir/build: CAN_test

.PHONY : CMakeFiles/CAN_test.dir/build

CMakeFiles/CAN_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CAN_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CAN_test.dir/clean

CMakeFiles/CAN_test.dir/depend:
	cd /home/kay/Documents/practice/cpp/CAN_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kay/Documents/practice/cpp/CAN_test /home/kay/Documents/practice/cpp/CAN_test /home/kay/Documents/practice/cpp/CAN_test/build /home/kay/Documents/practice/cpp/CAN_test/build /home/kay/Documents/practice/cpp/CAN_test/build/CMakeFiles/CAN_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CAN_test.dir/depend

