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
CMAKE_COMMAND = /opt/cmake-3.15.3-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.15.3-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ciprian/testtools/simpletracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ciprian/testtools/simpletracer

# Include any dependencies generated for this target.
include river.format/logger/CMakeFiles/logger.dir/depend.make

# Include the progress variables for this target.
include river.format/logger/CMakeFiles/logger.dir/progress.make

# Include the compile flags for this target's objects.
include river.format/logger/CMakeFiles/logger.dir/flags.make

river.format/logger/CMakeFiles/logger.dir/AbstractLog.cpp.o: river.format/logger/CMakeFiles/logger.dir/flags.make
river.format/logger/CMakeFiles/logger.dir/AbstractLog.cpp.o: river.format/logger/AbstractLog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ciprian/testtools/simpletracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object river.format/logger/CMakeFiles/logger.dir/AbstractLog.cpp.o"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/AbstractLog.cpp.o -c /home/ciprian/testtools/simpletracer/river.format/logger/AbstractLog.cpp

river.format/logger/CMakeFiles/logger.dir/AbstractLog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/AbstractLog.cpp.i"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ciprian/testtools/simpletracer/river.format/logger/AbstractLog.cpp > CMakeFiles/logger.dir/AbstractLog.cpp.i

river.format/logger/CMakeFiles/logger.dir/AbstractLog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/AbstractLog.cpp.s"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ciprian/testtools/simpletracer/river.format/logger/AbstractLog.cpp -o CMakeFiles/logger.dir/AbstractLog.cpp.s

river.format/logger/CMakeFiles/logger.dir/FileLog.cpp.o: river.format/logger/CMakeFiles/logger.dir/flags.make
river.format/logger/CMakeFiles/logger.dir/FileLog.cpp.o: river.format/logger/FileLog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ciprian/testtools/simpletracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object river.format/logger/CMakeFiles/logger.dir/FileLog.cpp.o"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/FileLog.cpp.o -c /home/ciprian/testtools/simpletracer/river.format/logger/FileLog.cpp

river.format/logger/CMakeFiles/logger.dir/FileLog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/FileLog.cpp.i"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ciprian/testtools/simpletracer/river.format/logger/FileLog.cpp > CMakeFiles/logger.dir/FileLog.cpp.i

river.format/logger/CMakeFiles/logger.dir/FileLog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/FileLog.cpp.s"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ciprian/testtools/simpletracer/river.format/logger/FileLog.cpp -o CMakeFiles/logger.dir/FileLog.cpp.s

river.format/logger/CMakeFiles/logger.dir/Logger.cpp.o: river.format/logger/CMakeFiles/logger.dir/flags.make
river.format/logger/CMakeFiles/logger.dir/Logger.cpp.o: river.format/logger/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ciprian/testtools/simpletracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object river.format/logger/CMakeFiles/logger.dir/Logger.cpp.o"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/logger.dir/Logger.cpp.o -c /home/ciprian/testtools/simpletracer/river.format/logger/Logger.cpp

river.format/logger/CMakeFiles/logger.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/logger.dir/Logger.cpp.i"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ciprian/testtools/simpletracer/river.format/logger/Logger.cpp > CMakeFiles/logger.dir/Logger.cpp.i

river.format/logger/CMakeFiles/logger.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/logger.dir/Logger.cpp.s"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ciprian/testtools/simpletracer/river.format/logger/Logger.cpp -o CMakeFiles/logger.dir/Logger.cpp.s

# Object files for target logger
logger_OBJECTS = \
"CMakeFiles/logger.dir/AbstractLog.cpp.o" \
"CMakeFiles/logger.dir/FileLog.cpp.o" \
"CMakeFiles/logger.dir/Logger.cpp.o"

# External object files for target logger
logger_EXTERNAL_OBJECTS =

river.format/logger/liblogger.a: river.format/logger/CMakeFiles/logger.dir/AbstractLog.cpp.o
river.format/logger/liblogger.a: river.format/logger/CMakeFiles/logger.dir/FileLog.cpp.o
river.format/logger/liblogger.a: river.format/logger/CMakeFiles/logger.dir/Logger.cpp.o
river.format/logger/liblogger.a: river.format/logger/CMakeFiles/logger.dir/build.make
river.format/logger/liblogger.a: river.format/logger/CMakeFiles/logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ciprian/testtools/simpletracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library liblogger.a"
	cd /home/ciprian/testtools/simpletracer/river.format/logger && $(CMAKE_COMMAND) -P CMakeFiles/logger.dir/cmake_clean_target.cmake
	cd /home/ciprian/testtools/simpletracer/river.format/logger && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
river.format/logger/CMakeFiles/logger.dir/build: river.format/logger/liblogger.a

.PHONY : river.format/logger/CMakeFiles/logger.dir/build

river.format/logger/CMakeFiles/logger.dir/clean:
	cd /home/ciprian/testtools/simpletracer/river.format/logger && $(CMAKE_COMMAND) -P CMakeFiles/logger.dir/cmake_clean.cmake
.PHONY : river.format/logger/CMakeFiles/logger.dir/clean

river.format/logger/CMakeFiles/logger.dir/depend:
	cd /home/ciprian/testtools/simpletracer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ciprian/testtools/simpletracer /home/ciprian/testtools/simpletracer/river.format/logger /home/ciprian/testtools/simpletracer /home/ciprian/testtools/simpletracer/river.format/logger /home/ciprian/testtools/simpletracer/river.format/logger/CMakeFiles/logger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : river.format/logger/CMakeFiles/logger.dir/depend

