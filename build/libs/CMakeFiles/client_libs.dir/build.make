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
include libs/CMakeFiles/client_libs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libs/CMakeFiles/client_libs.dir/compiler_depend.make

# Include the progress variables for this target.
include libs/CMakeFiles/client_libs.dir/progress.make

# Include the compile flags for this target's objects.
include libs/CMakeFiles/client_libs.dir/flags.make

libs/CMakeFiles/client_libs.dir/Client.o: libs/CMakeFiles/client_libs.dir/flags.make
libs/CMakeFiles/client_libs.dir/Client.o: /home/uttkarsh/Distributed_file_management_system/project/libs/Client.cpp
libs/CMakeFiles/client_libs.dir/Client.o: libs/CMakeFiles/client_libs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/uttkarsh/Distributed_file_management_system/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libs/CMakeFiles/client_libs.dir/Client.o"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/libs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libs/CMakeFiles/client_libs.dir/Client.o -MF CMakeFiles/client_libs.dir/Client.o.d -o CMakeFiles/client_libs.dir/Client.o -c /home/uttkarsh/Distributed_file_management_system/project/libs/Client.cpp

libs/CMakeFiles/client_libs.dir/Client.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/client_libs.dir/Client.i"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/libs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/uttkarsh/Distributed_file_management_system/project/libs/Client.cpp > CMakeFiles/client_libs.dir/Client.i

libs/CMakeFiles/client_libs.dir/Client.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/client_libs.dir/Client.s"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/libs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/uttkarsh/Distributed_file_management_system/project/libs/Client.cpp -o CMakeFiles/client_libs.dir/Client.s

# Object files for target client_libs
client_libs_OBJECTS = \
"CMakeFiles/client_libs.dir/Client.o"

# External object files for target client_libs
client_libs_EXTERNAL_OBJECTS =

libs/libclient_libs.a: libs/CMakeFiles/client_libs.dir/Client.o
libs/libclient_libs.a: libs/CMakeFiles/client_libs.dir/build.make
libs/libclient_libs.a: libs/CMakeFiles/client_libs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/uttkarsh/Distributed_file_management_system/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libclient_libs.a"
	cd /home/uttkarsh/Distributed_file_management_system/project/build/libs && $(CMAKE_COMMAND) -P CMakeFiles/client_libs.dir/cmake_clean_target.cmake
	cd /home/uttkarsh/Distributed_file_management_system/project/build/libs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_libs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/CMakeFiles/client_libs.dir/build: libs/libclient_libs.a
.PHONY : libs/CMakeFiles/client_libs.dir/build

libs/CMakeFiles/client_libs.dir/clean:
	cd /home/uttkarsh/Distributed_file_management_system/project/build/libs && $(CMAKE_COMMAND) -P CMakeFiles/client_libs.dir/cmake_clean.cmake
.PHONY : libs/CMakeFiles/client_libs.dir/clean

libs/CMakeFiles/client_libs.dir/depend:
	cd /home/uttkarsh/Distributed_file_management_system/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/uttkarsh/Distributed_file_management_system/project /home/uttkarsh/Distributed_file_management_system/project/libs /home/uttkarsh/Distributed_file_management_system/project/build /home/uttkarsh/Distributed_file_management_system/project/build/libs /home/uttkarsh/Distributed_file_management_system/project/build/libs/CMakeFiles/client_libs.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : libs/CMakeFiles/client_libs.dir/depend

