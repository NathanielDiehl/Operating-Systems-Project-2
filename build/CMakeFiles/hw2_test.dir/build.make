# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:/Users/yswang/Desktop/CIS 520/hw2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:/Users/yswang/Desktop/CIS 520/hw2/build"

# Include any dependencies generated for this target.
include CMakeFiles/hw2_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hw2_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hw2_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw2_test.dir/flags.make

CMakeFiles/hw2_test.dir/test/tests.cpp.obj: CMakeFiles/hw2_test.dir/flags.make
CMakeFiles/hw2_test.dir/test/tests.cpp.obj: CMakeFiles/hw2_test.dir/includes_CXX.rsp
CMakeFiles/hw2_test.dir/test/tests.cpp.obj: C:/Users/yswang/Desktop/CIS\ 520/hw2/test/tests.cpp
CMakeFiles/hw2_test.dir/test/tests.cpp.obj: CMakeFiles/hw2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:/Users/yswang/Desktop/CIS 520/hw2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw2_test.dir/test/tests.cpp.obj"
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw2_test.dir/test/tests.cpp.obj -MF CMakeFiles/hw2_test.dir/test/tests.cpp.obj.d -o CMakeFiles/hw2_test.dir/test/tests.cpp.obj -c "C:/Users/yswang/Desktop/CIS 520/hw2/test/tests.cpp"

CMakeFiles/hw2_test.dir/test/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/hw2_test.dir/test/tests.cpp.i"
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:/Users/yswang/Desktop/CIS 520/hw2/test/tests.cpp" > CMakeFiles/hw2_test.dir/test/tests.cpp.i

CMakeFiles/hw2_test.dir/test/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/hw2_test.dir/test/tests.cpp.s"
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:/Users/yswang/Desktop/CIS 520/hw2/test/tests.cpp" -o CMakeFiles/hw2_test.dir/test/tests.cpp.s

CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj: CMakeFiles/hw2_test.dir/flags.make
CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj: CMakeFiles/hw2_test.dir/includes_C.rsp
CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj: C:/Users/yswang/Desktop/CIS\ 520/hw2/src/process_scheduling.c
CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj: CMakeFiles/hw2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:/Users/yswang/Desktop/CIS 520/hw2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj"
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj -MF CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj.d -o CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj -c "C:/Users/yswang/Desktop/CIS 520/hw2/src/process_scheduling.c"

CMakeFiles/hw2_test.dir/src/process_scheduling.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/hw2_test.dir/src/process_scheduling.c.i"
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:/Users/yswang/Desktop/CIS 520/hw2/src/process_scheduling.c" > CMakeFiles/hw2_test.dir/src/process_scheduling.c.i

CMakeFiles/hw2_test.dir/src/process_scheduling.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/hw2_test.dir/src/process_scheduling.c.s"
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:/Users/yswang/Desktop/CIS 520/hw2/src/process_scheduling.c" -o CMakeFiles/hw2_test.dir/src/process_scheduling.c.s

# Object files for target hw2_test
hw2_test_OBJECTS = \
"CMakeFiles/hw2_test.dir/test/tests.cpp.obj" \
"CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj"

# External object files for target hw2_test
hw2_test_EXTERNAL_OBJECTS =

hw2_test.exe: CMakeFiles/hw2_test.dir/test/tests.cpp.obj
hw2_test.exe: CMakeFiles/hw2_test.dir/src/process_scheduling.c.obj
hw2_test.exe: CMakeFiles/hw2_test.dir/build.make
hw2_test.exe: libdyn_array.a
hw2_test.exe: CMakeFiles/hw2_test.dir/linkLibs.rsp
hw2_test.exe: CMakeFiles/hw2_test.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:/Users/yswang/Desktop/CIS 520/hw2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable hw2_test.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/hw2_test.dir/objects.a
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/ar.exe qc CMakeFiles/hw2_test.dir/objects.a @CMakeFiles/hw2_test.dir/objects1.rsp
	C:/Users/yswang/Documents/Compiler/w64devkit/bin/g++.exe -std=c++11 -Wall -Wextra -Wshadow -Werror -g -Wl,--whole-archive CMakeFiles/hw2_test.dir/objects.a -Wl,--no-whole-archive -o hw2_test.exe -Wl,--out-implib,libhw2_test.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/hw2_test.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/hw2_test.dir/build: hw2_test.exe
.PHONY : CMakeFiles/hw2_test.dir/build

CMakeFiles/hw2_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw2_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw2_test.dir/clean

CMakeFiles/hw2_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "C:/Users/yswang/Desktop/CIS 520/hw2" "C:/Users/yswang/Desktop/CIS 520/hw2" "C:/Users/yswang/Desktop/CIS 520/hw2/build" "C:/Users/yswang/Desktop/CIS 520/hw2/build" "C:/Users/yswang/Desktop/CIS 520/hw2/build/CMakeFiles/hw2_test.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/hw2_test.dir/depend
