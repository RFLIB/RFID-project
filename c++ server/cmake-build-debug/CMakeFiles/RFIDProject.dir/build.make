# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Valery\CLionProjects\library

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Valery\CLionProjects\library\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RFIDProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RFIDProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RFIDProject.dir/flags.make

CMakeFiles/RFIDProject.dir/main.cpp.obj: CMakeFiles/RFIDProject.dir/flags.make
CMakeFiles/RFIDProject.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Valery\CLionProjects\library\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RFIDProject.dir/main.cpp.obj"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\RFIDProject.dir\main.cpp.obj -c C:\Users\Valery\CLionProjects\library\main.cpp

CMakeFiles/RFIDProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RFIDProject.dir/main.cpp.i"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Valery\CLionProjects\library\main.cpp > CMakeFiles\RFIDProject.dir\main.cpp.i

CMakeFiles/RFIDProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RFIDProject.dir/main.cpp.s"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Valery\CLionProjects\library\main.cpp -o CMakeFiles\RFIDProject.dir\main.cpp.s

CMakeFiles/RFIDProject.dir/SerialPort.cpp.obj: CMakeFiles/RFIDProject.dir/flags.make
CMakeFiles/RFIDProject.dir/SerialPort.cpp.obj: ../SerialPort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Valery\CLionProjects\library\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RFIDProject.dir/SerialPort.cpp.obj"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\RFIDProject.dir\SerialPort.cpp.obj -c C:\Users\Valery\CLionProjects\library\SerialPort.cpp

CMakeFiles/RFIDProject.dir/SerialPort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RFIDProject.dir/SerialPort.cpp.i"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Valery\CLionProjects\library\SerialPort.cpp > CMakeFiles\RFIDProject.dir\SerialPort.cpp.i

CMakeFiles/RFIDProject.dir/SerialPort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RFIDProject.dir/SerialPort.cpp.s"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Valery\CLionProjects\library\SerialPort.cpp -o CMakeFiles\RFIDProject.dir\SerialPort.cpp.s

CMakeFiles/RFIDProject.dir/sqlite3.c.obj: CMakeFiles/RFIDProject.dir/flags.make
CMakeFiles/RFIDProject.dir/sqlite3.c.obj: ../sqlite3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Valery\CLionProjects\library\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/RFIDProject.dir/sqlite3.c.obj"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\RFIDProject.dir\sqlite3.c.obj   -c C:\Users\Valery\CLionProjects\library\sqlite3.c

CMakeFiles/RFIDProject.dir/sqlite3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RFIDProject.dir/sqlite3.c.i"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Valery\CLionProjects\library\sqlite3.c > CMakeFiles\RFIDProject.dir\sqlite3.c.i

CMakeFiles/RFIDProject.dir/sqlite3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RFIDProject.dir/sqlite3.c.s"
	C:\PROGRA~1\mingww64\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Valery\CLionProjects\library\sqlite3.c -o CMakeFiles\RFIDProject.dir\sqlite3.c.s

# Object files for target RFIDProject
RFIDProject_OBJECTS = \
"CMakeFiles/RFIDProject.dir/main.cpp.obj" \
"CMakeFiles/RFIDProject.dir/SerialPort.cpp.obj" \
"CMakeFiles/RFIDProject.dir/sqlite3.c.obj"

# External object files for target RFIDProject
RFIDProject_EXTERNAL_OBJECTS =

RFIDProject.exe: CMakeFiles/RFIDProject.dir/main.cpp.obj
RFIDProject.exe: CMakeFiles/RFIDProject.dir/SerialPort.cpp.obj
RFIDProject.exe: CMakeFiles/RFIDProject.dir/sqlite3.c.obj
RFIDProject.exe: CMakeFiles/RFIDProject.dir/build.make
RFIDProject.exe: CMakeFiles/RFIDProject.dir/linklibs.rsp
RFIDProject.exe: CMakeFiles/RFIDProject.dir/objects1.rsp
RFIDProject.exe: CMakeFiles/RFIDProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Valery\CLionProjects\library\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable RFIDProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RFIDProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RFIDProject.dir/build: RFIDProject.exe

.PHONY : CMakeFiles/RFIDProject.dir/build

CMakeFiles/RFIDProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\RFIDProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/RFIDProject.dir/clean

CMakeFiles/RFIDProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Valery\CLionProjects\library C:\Users\Valery\CLionProjects\library C:\Users\Valery\CLionProjects\library\cmake-build-debug C:\Users\Valery\CLionProjects\library\cmake-build-debug C:\Users\Valery\CLionProjects\library\cmake-build-debug\CMakeFiles\RFIDProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RFIDProject.dir/depend

