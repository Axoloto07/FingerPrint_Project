# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build

# Include any dependencies generated for this target.
include alglib/CMakeFiles/alg.dir/depend.make

# Include the progress variables for this target.
include alglib/CMakeFiles/alg.dir/progress.make

# Include the compile flags for this target's objects.
include alglib/CMakeFiles/alg.dir/flags.make

alglib/CMakeFiles/alg.dir/alglibinternal.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/alglibinternal.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibinternal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object alglib/CMakeFiles/alg.dir/alglibinternal.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/alglibinternal.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibinternal.cpp

alglib/CMakeFiles/alg.dir/alglibinternal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/alglibinternal.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibinternal.cpp > CMakeFiles/alg.dir/alglibinternal.cpp.i

alglib/CMakeFiles/alg.dir/alglibinternal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/alglibinternal.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibinternal.cpp -o CMakeFiles/alg.dir/alglibinternal.cpp.s

alglib/CMakeFiles/alg.dir/alglibmisc.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/alglibmisc.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibmisc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object alglib/CMakeFiles/alg.dir/alglibmisc.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/alglibmisc.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibmisc.cpp

alglib/CMakeFiles/alg.dir/alglibmisc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/alglibmisc.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibmisc.cpp > CMakeFiles/alg.dir/alglibmisc.cpp.i

alglib/CMakeFiles/alg.dir/alglibmisc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/alglibmisc.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/alglibmisc.cpp -o CMakeFiles/alg.dir/alglibmisc.cpp.s

alglib/CMakeFiles/alg.dir/ap.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/ap.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/ap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object alglib/CMakeFiles/alg.dir/ap.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/ap.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/ap.cpp

alglib/CMakeFiles/alg.dir/ap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/ap.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/ap.cpp > CMakeFiles/alg.dir/ap.cpp.i

alglib/CMakeFiles/alg.dir/ap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/ap.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/ap.cpp -o CMakeFiles/alg.dir/ap.cpp.s

alglib/CMakeFiles/alg.dir/dataanalysis.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/dataanalysis.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/dataanalysis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object alglib/CMakeFiles/alg.dir/dataanalysis.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/dataanalysis.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/dataanalysis.cpp

alglib/CMakeFiles/alg.dir/dataanalysis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/dataanalysis.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/dataanalysis.cpp > CMakeFiles/alg.dir/dataanalysis.cpp.i

alglib/CMakeFiles/alg.dir/dataanalysis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/dataanalysis.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/dataanalysis.cpp -o CMakeFiles/alg.dir/dataanalysis.cpp.s

alglib/CMakeFiles/alg.dir/diffequations.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/diffequations.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/diffequations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object alglib/CMakeFiles/alg.dir/diffequations.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/diffequations.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/diffequations.cpp

alglib/CMakeFiles/alg.dir/diffequations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/diffequations.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/diffequations.cpp > CMakeFiles/alg.dir/diffequations.cpp.i

alglib/CMakeFiles/alg.dir/diffequations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/diffequations.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/diffequations.cpp -o CMakeFiles/alg.dir/diffequations.cpp.s

alglib/CMakeFiles/alg.dir/fasttransforms.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/fasttransforms.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/fasttransforms.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object alglib/CMakeFiles/alg.dir/fasttransforms.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/fasttransforms.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/fasttransforms.cpp

alglib/CMakeFiles/alg.dir/fasttransforms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/fasttransforms.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/fasttransforms.cpp > CMakeFiles/alg.dir/fasttransforms.cpp.i

alglib/CMakeFiles/alg.dir/fasttransforms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/fasttransforms.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/fasttransforms.cpp -o CMakeFiles/alg.dir/fasttransforms.cpp.s

alglib/CMakeFiles/alg.dir/integration.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/integration.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/integration.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object alglib/CMakeFiles/alg.dir/integration.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/integration.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/integration.cpp

alglib/CMakeFiles/alg.dir/integration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/integration.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/integration.cpp > CMakeFiles/alg.dir/integration.cpp.i

alglib/CMakeFiles/alg.dir/integration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/integration.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/integration.cpp -o CMakeFiles/alg.dir/integration.cpp.s

alglib/CMakeFiles/alg.dir/interpolation.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/interpolation.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/interpolation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object alglib/CMakeFiles/alg.dir/interpolation.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/interpolation.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/interpolation.cpp

alglib/CMakeFiles/alg.dir/interpolation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/interpolation.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/interpolation.cpp > CMakeFiles/alg.dir/interpolation.cpp.i

alglib/CMakeFiles/alg.dir/interpolation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/interpolation.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/interpolation.cpp -o CMakeFiles/alg.dir/interpolation.cpp.s

alglib/CMakeFiles/alg.dir/kernels_avx2.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/kernels_avx2.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_avx2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object alglib/CMakeFiles/alg.dir/kernels_avx2.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/kernels_avx2.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_avx2.cpp

alglib/CMakeFiles/alg.dir/kernels_avx2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/kernels_avx2.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_avx2.cpp > CMakeFiles/alg.dir/kernels_avx2.cpp.i

alglib/CMakeFiles/alg.dir/kernels_avx2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/kernels_avx2.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_avx2.cpp -o CMakeFiles/alg.dir/kernels_avx2.cpp.s

alglib/CMakeFiles/alg.dir/kernels_fma.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/kernels_fma.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_fma.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object alglib/CMakeFiles/alg.dir/kernels_fma.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/kernels_fma.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_fma.cpp

alglib/CMakeFiles/alg.dir/kernels_fma.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/kernels_fma.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_fma.cpp > CMakeFiles/alg.dir/kernels_fma.cpp.i

alglib/CMakeFiles/alg.dir/kernels_fma.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/kernels_fma.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_fma.cpp -o CMakeFiles/alg.dir/kernels_fma.cpp.s

alglib/CMakeFiles/alg.dir/kernels_sse2.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/kernels_sse2.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_sse2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object alglib/CMakeFiles/alg.dir/kernels_sse2.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/kernels_sse2.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_sse2.cpp

alglib/CMakeFiles/alg.dir/kernels_sse2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/kernels_sse2.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_sse2.cpp > CMakeFiles/alg.dir/kernels_sse2.cpp.i

alglib/CMakeFiles/alg.dir/kernels_sse2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/kernels_sse2.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/kernels_sse2.cpp -o CMakeFiles/alg.dir/kernels_sse2.cpp.s

alglib/CMakeFiles/alg.dir/linalg.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/linalg.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/linalg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object alglib/CMakeFiles/alg.dir/linalg.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/linalg.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/linalg.cpp

alglib/CMakeFiles/alg.dir/linalg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/linalg.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/linalg.cpp > CMakeFiles/alg.dir/linalg.cpp.i

alglib/CMakeFiles/alg.dir/linalg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/linalg.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/linalg.cpp -o CMakeFiles/alg.dir/linalg.cpp.s

alglib/CMakeFiles/alg.dir/optimization.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/optimization.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/optimization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object alglib/CMakeFiles/alg.dir/optimization.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/optimization.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/optimization.cpp

alglib/CMakeFiles/alg.dir/optimization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/optimization.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/optimization.cpp > CMakeFiles/alg.dir/optimization.cpp.i

alglib/CMakeFiles/alg.dir/optimization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/optimization.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/optimization.cpp -o CMakeFiles/alg.dir/optimization.cpp.s

alglib/CMakeFiles/alg.dir/solvers.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/solvers.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/solvers.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object alglib/CMakeFiles/alg.dir/solvers.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/solvers.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/solvers.cpp

alglib/CMakeFiles/alg.dir/solvers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/solvers.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/solvers.cpp > CMakeFiles/alg.dir/solvers.cpp.i

alglib/CMakeFiles/alg.dir/solvers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/solvers.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/solvers.cpp -o CMakeFiles/alg.dir/solvers.cpp.s

alglib/CMakeFiles/alg.dir/specialfunctions.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/specialfunctions.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/specialfunctions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object alglib/CMakeFiles/alg.dir/specialfunctions.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/specialfunctions.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/specialfunctions.cpp

alglib/CMakeFiles/alg.dir/specialfunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/specialfunctions.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/specialfunctions.cpp > CMakeFiles/alg.dir/specialfunctions.cpp.i

alglib/CMakeFiles/alg.dir/specialfunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/specialfunctions.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/specialfunctions.cpp -o CMakeFiles/alg.dir/specialfunctions.cpp.s

alglib/CMakeFiles/alg.dir/statistics.cpp.o: alglib/CMakeFiles/alg.dir/flags.make
alglib/CMakeFiles/alg.dir/statistics.cpp.o: /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/statistics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object alglib/CMakeFiles/alg.dir/statistics.cpp.o"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/statistics.cpp.o -c /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/statistics.cpp

alglib/CMakeFiles/alg.dir/statistics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/statistics.cpp.i"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/statistics.cpp > CMakeFiles/alg.dir/statistics.cpp.i

alglib/CMakeFiles/alg.dir/statistics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/statistics.cpp.s"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib/statistics.cpp -o CMakeFiles/alg.dir/statistics.cpp.s

# Object files for target alg
alg_OBJECTS = \
"CMakeFiles/alg.dir/alglibinternal.cpp.o" \
"CMakeFiles/alg.dir/alglibmisc.cpp.o" \
"CMakeFiles/alg.dir/ap.cpp.o" \
"CMakeFiles/alg.dir/dataanalysis.cpp.o" \
"CMakeFiles/alg.dir/diffequations.cpp.o" \
"CMakeFiles/alg.dir/fasttransforms.cpp.o" \
"CMakeFiles/alg.dir/integration.cpp.o" \
"CMakeFiles/alg.dir/interpolation.cpp.o" \
"CMakeFiles/alg.dir/kernels_avx2.cpp.o" \
"CMakeFiles/alg.dir/kernels_fma.cpp.o" \
"CMakeFiles/alg.dir/kernels_sse2.cpp.o" \
"CMakeFiles/alg.dir/linalg.cpp.o" \
"CMakeFiles/alg.dir/optimization.cpp.o" \
"CMakeFiles/alg.dir/solvers.cpp.o" \
"CMakeFiles/alg.dir/specialfunctions.cpp.o" \
"CMakeFiles/alg.dir/statistics.cpp.o"

# External object files for target alg
alg_EXTERNAL_OBJECTS =

alglib/libalg.a: alglib/CMakeFiles/alg.dir/alglibinternal.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/alglibmisc.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/ap.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/dataanalysis.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/diffequations.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/fasttransforms.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/integration.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/interpolation.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/kernels_avx2.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/kernels_fma.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/kernels_sse2.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/linalg.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/optimization.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/solvers.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/specialfunctions.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/statistics.cpp.o
alglib/libalg.a: alglib/CMakeFiles/alg.dir/build.make
alglib/libalg.a: alglib/CMakeFiles/alg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking CXX static library libalg.a"
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && $(CMAKE_COMMAND) -P CMakeFiles/alg.dir/cmake_clean_target.cmake
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
alglib/CMakeFiles/alg.dir/build: alglib/libalg.a

.PHONY : alglib/CMakeFiles/alg.dir/build

alglib/CMakeFiles/alg.dir/clean:
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib && $(CMAKE_COMMAND) -P CMakeFiles/alg.dir/cmake_clean.cmake
.PHONY : alglib/CMakeFiles/alg.dir/clean

alglib/CMakeFiles/alg.dir/depend:
	cd /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/Project_Infra/alglib /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib /home/artim436/2A/project_modelling/axel/FingerPrint_Project/Fing_Project_Final/build/alglib/CMakeFiles/alg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : alglib/CMakeFiles/alg.dir/depend

