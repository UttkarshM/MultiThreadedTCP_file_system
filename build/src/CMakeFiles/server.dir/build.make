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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/uttkarsh/Distributed_file_management_system/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/uttkarsh/Distributed_file_management_system/project/build

# Include any dependencies generated for this target.
include src/CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/server.dir/flags.make

src/CMakeFiles/server.dir/main.o: src/CMakeFiles/server.dir/flags.make
src/CMakeFiles/server.dir/main.o: /home/uttkarsh/Distributed_file_management_system/project/src/main.cpp
src/CMakeFiles/server.dir/main.o: src/CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/uttkarsh/Distributed_file_management_system/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/server.dir/main.o"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/server.dir/main.o -MF CMakeFiles/server.dir/main.o.d -o CMakeFiles/server.dir/main.o -c /home/uttkarsh/Distributed_file_management_system/project/src/main.cpp

src/CMakeFiles/server.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/main.i"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/uttkarsh/Distributed_file_management_system/project/src/main.cpp > CMakeFiles/server.dir/main.i

src/CMakeFiles/server.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.s"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/uttkarsh/Distributed_file_management_system/project/src/main.cpp -o CMakeFiles/server.dir/main.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

src/server: src/CMakeFiles/server.dir/main.o
src/server: src/CMakeFiles/server.dir/build.make
src/server: libs/libserver_lib.a
src/server: external/libimage_lib.a
src/server: src/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/uttkarsh/Distributed_file_management_system/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/server.dir/build: src/server
.PHONY : src/CMakeFiles/server.dir/build

src/CMakeFiles/server.dir/clean:
	cd /home/uttkarsh/Distributed_file_management_system/project/build/src && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/server.dir/clean

src/CMakeFiles/server.dir/depend:
	cd /home/uttkarsh/Distributed_file_management_system/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/uttkarsh/Distributed_file_management_system/project /home/uttkarsh/Distributed_file_management_system/project/src /home/uttkarsh/Distributed_file_management_system/project/build /home/uttkarsh/Distributed_file_management_system/project/build/src /home/uttkarsh/Distributed_file_management_system/project/build/src/CMakeFiles/server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/server.dir/depend

