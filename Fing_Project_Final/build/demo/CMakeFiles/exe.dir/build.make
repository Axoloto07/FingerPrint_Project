# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/axel/Documents/M1/Fing_Project_Final/Project_Infra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/axel/Documents/M1/Fing_Project_Final/build

# Include any dependencies generated for this target.
include demo/CMakeFiles/exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include demo/CMakeFiles/exe.dir/compiler_depend.make

# Include the progress variables for this target.
include demo/CMakeFiles/exe.dir/progress.make

# Include the compile flags for this target's objects.
include demo/CMakeFiles/exe.dir/flags.make

demo/CMakeFiles/exe.dir/test_patch.cpp.o: demo/CMakeFiles/exe.dir/flags.make
demo/CMakeFiles/exe.dir/test_patch.cpp.o: /home/axel/Documents/M1/Fing_Project_Final/Project_Infra/demo/test_patch.cpp
demo/CMakeFiles/exe.dir/test_patch.cpp.o: demo/CMakeFiles/exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axel/Documents/M1/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object demo/CMakeFiles/exe.dir/test_patch.cpp.o"
	cd /home/axel/Documents/M1/Fing_Project_Final/build/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT demo/CMakeFiles/exe.dir/test_patch.cpp.o -MF CMakeFiles/exe.dir/test_patch.cpp.o.d -o CMakeFiles/exe.dir/test_patch.cpp.o -c /home/axel/Documents/M1/Fing_Project_Final/Project_Infra/demo/test_patch.cpp

demo/CMakeFiles/exe.dir/test_patch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exe.dir/test_patch.cpp.i"
	cd /home/axel/Documents/M1/Fing_Project_Final/build/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axel/Documents/M1/Fing_Project_Final/Project_Infra/demo/test_patch.cpp > CMakeFiles/exe.dir/test_patch.cpp.i

demo/CMakeFiles/exe.dir/test_patch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exe.dir/test_patch.cpp.s"
	cd /home/axel/Documents/M1/Fing_Project_Final/build/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axel/Documents/M1/Fing_Project_Final/Project_Infra/demo/test_patch.cpp -o CMakeFiles/exe.dir/test_patch.cpp.s

# Object files for target exe
exe_OBJECTS = \
"CMakeFiles/exe.dir/test_patch.cpp.o"

# External object files for target exe
exe_EXTERNAL_OBJECTS =

demo/exe: demo/CMakeFiles/exe.dir/test_patch.cpp.o
demo/exe: demo/CMakeFiles/exe.dir/build.make
demo/exe: src/libFingerPrint.a
demo/exe: /usr/local/lib/libopencv_gapi.so.4.7.0
demo/exe: /usr/local/lib/libopencv_highgui.so.4.7.0
demo/exe: /usr/local/lib/libopencv_ml.so.4.7.0
demo/exe: /usr/local/lib/libopencv_objdetect.so.4.7.0
demo/exe: /usr/local/lib/libopencv_photo.so.4.7.0
demo/exe: /usr/local/lib/libopencv_stitching.so.4.7.0
demo/exe: /usr/local/lib/libopencv_video.so.4.7.0
demo/exe: /usr/local/lib/libopencv_videoio.so.4.7.0
demo/exe: alglib/libalg.a
demo/exe: /usr/local/lib/libopencv_imgcodecs.so.4.7.0
demo/exe: /usr/local/lib/libopencv_dnn.so.4.7.0
demo/exe: /usr/local/lib/libopencv_calib3d.so.4.7.0
demo/exe: /usr/local/lib/libopencv_features2d.so.4.7.0
demo/exe: /usr/local/lib/libopencv_flann.so.4.7.0
demo/exe: /usr/local/lib/libopencv_imgproc.so.4.7.0
demo/exe: /usr/local/lib/libopencv_core.so.4.7.0
demo/exe: demo/CMakeFiles/exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/axel/Documents/M1/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exe"
	cd /home/axel/Documents/M1/Fing_Project_Final/build/demo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demo/CMakeFiles/exe.dir/build: demo/exe
.PHONY : demo/CMakeFiles/exe.dir/build

demo/CMakeFiles/exe.dir/clean:
	cd /home/axel/Documents/M1/Fing_Project_Final/build/demo && $(CMAKE_COMMAND) -P CMakeFiles/exe.dir/cmake_clean.cmake
.PHONY : demo/CMakeFiles/exe.dir/clean

demo/CMakeFiles/exe.dir/depend:
	cd /home/axel/Documents/M1/Fing_Project_Final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/axel/Documents/M1/Fing_Project_Final/Project_Infra /home/axel/Documents/M1/Fing_Project_Final/Project_Infra/demo /home/axel/Documents/M1/Fing_Project_Final/build /home/axel/Documents/M1/Fing_Project_Final/build/demo /home/axel/Documents/M1/Fing_Project_Final/build/demo/CMakeFiles/exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demo/CMakeFiles/exe.dir/depend

