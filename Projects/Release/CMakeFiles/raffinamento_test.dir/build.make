# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\matte\Desktop\Progetto_PCS\Projects\Release

# Include any dependencies generated for this target.
include CMakeFiles/raffinamento_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raffinamento_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raffinamento_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raffinamento_test.dir/flags.make

CMakeFiles/raffinamento_test.dir/main_test.cpp.obj: CMakeFiles/raffinamento_test.dir/flags.make
CMakeFiles/raffinamento_test.dir/main_test.cpp.obj: CMakeFiles/raffinamento_test.dir/includes_CXX.rsp
CMakeFiles/raffinamento_test.dir/main_test.cpp.obj: C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/main_test.cpp
CMakeFiles/raffinamento_test.dir/main_test.cpp.obj: CMakeFiles/raffinamento_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matte\Desktop\Progetto_PCS\Projects\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raffinamento_test.dir/main_test.cpp.obj"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raffinamento_test.dir/main_test.cpp.obj -MF CMakeFiles\raffinamento_test.dir\main_test.cpp.obj.d -o CMakeFiles\raffinamento_test.dir\main_test.cpp.obj -c C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\main_test.cpp

CMakeFiles/raffinamento_test.dir/main_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raffinamento_test.dir/main_test.cpp.i"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\main_test.cpp > CMakeFiles\raffinamento_test.dir\main_test.cpp.i

CMakeFiles/raffinamento_test.dir/main_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raffinamento_test.dir/main_test.cpp.s"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\main_test.cpp -o CMakeFiles\raffinamento_test.dir\main_test.cpp.s

CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj: CMakeFiles/raffinamento_test.dir/flags.make
CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj: CMakeFiles/raffinamento_test.dir/includes_CXX.rsp
CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj: C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/src/geometry_class.cpp
CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj: CMakeFiles/raffinamento_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matte\Desktop\Progetto_PCS\Projects\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj -MF CMakeFiles\raffinamento_test.dir\src\geometry_class.cpp.obj.d -o CMakeFiles\raffinamento_test.dir\src\geometry_class.cpp.obj -c C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\geometry_class.cpp

CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.i"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\geometry_class.cpp > CMakeFiles\raffinamento_test.dir\src\geometry_class.cpp.i

CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.s"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\geometry_class.cpp -o CMakeFiles\raffinamento_test.dir\src\geometry_class.cpp.s

CMakeFiles/raffinamento_test.dir/src/import.cpp.obj: CMakeFiles/raffinamento_test.dir/flags.make
CMakeFiles/raffinamento_test.dir/src/import.cpp.obj: CMakeFiles/raffinamento_test.dir/includes_CXX.rsp
CMakeFiles/raffinamento_test.dir/src/import.cpp.obj: C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/src/import.cpp
CMakeFiles/raffinamento_test.dir/src/import.cpp.obj: CMakeFiles/raffinamento_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matte\Desktop\Progetto_PCS\Projects\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/raffinamento_test.dir/src/import.cpp.obj"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raffinamento_test.dir/src/import.cpp.obj -MF CMakeFiles\raffinamento_test.dir\src\import.cpp.obj.d -o CMakeFiles\raffinamento_test.dir\src\import.cpp.obj -c C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\import.cpp

CMakeFiles/raffinamento_test.dir/src/import.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raffinamento_test.dir/src/import.cpp.i"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\import.cpp > CMakeFiles\raffinamento_test.dir\src\import.cpp.i

CMakeFiles/raffinamento_test.dir/src/import.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raffinamento_test.dir/src/import.cpp.s"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\import.cpp -o CMakeFiles\raffinamento_test.dir\src\import.cpp.s

CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj: CMakeFiles/raffinamento_test.dir/flags.make
CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj: CMakeFiles/raffinamento_test.dir/includes_CXX.rsp
CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj: C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/src/refine.cpp
CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj: CMakeFiles/raffinamento_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matte\Desktop\Progetto_PCS\Projects\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj -MF CMakeFiles\raffinamento_test.dir\src\refine.cpp.obj.d -o CMakeFiles\raffinamento_test.dir\src\refine.cpp.obj -c C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\refine.cpp

CMakeFiles/raffinamento_test.dir/src/refine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raffinamento_test.dir/src/refine.cpp.i"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\refine.cpp > CMakeFiles\raffinamento_test.dir\src\refine.cpp.i

CMakeFiles/raffinamento_test.dir/src/refine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raffinamento_test.dir/src/refine.cpp.s"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\refine.cpp -o CMakeFiles\raffinamento_test.dir\src\refine.cpp.s

CMakeFiles/raffinamento_test.dir/src/output.cpp.obj: CMakeFiles/raffinamento_test.dir/flags.make
CMakeFiles/raffinamento_test.dir/src/output.cpp.obj: CMakeFiles/raffinamento_test.dir/includes_CXX.rsp
CMakeFiles/raffinamento_test.dir/src/output.cpp.obj: C:/Users/matte/Desktop/Progetto_PCS/Projects/Raffinamento/src/output.cpp
CMakeFiles/raffinamento_test.dir/src/output.cpp.obj: CMakeFiles/raffinamento_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matte\Desktop\Progetto_PCS\Projects\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/raffinamento_test.dir/src/output.cpp.obj"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raffinamento_test.dir/src/output.cpp.obj -MF CMakeFiles\raffinamento_test.dir\src\output.cpp.obj.d -o CMakeFiles\raffinamento_test.dir\src\output.cpp.obj -c C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\output.cpp

CMakeFiles/raffinamento_test.dir/src/output.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raffinamento_test.dir/src/output.cpp.i"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\output.cpp > CMakeFiles\raffinamento_test.dir\src\output.cpp.i

CMakeFiles/raffinamento_test.dir/src/output.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raffinamento_test.dir/src/output.cpp.s"
	C:\Qt\Tools\mingw1120_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento\src\output.cpp -o CMakeFiles\raffinamento_test.dir\src\output.cpp.s

# Object files for target raffinamento_test
raffinamento_test_OBJECTS = \
"CMakeFiles/raffinamento_test.dir/main_test.cpp.obj" \
"CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj" \
"CMakeFiles/raffinamento_test.dir/src/import.cpp.obj" \
"CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj" \
"CMakeFiles/raffinamento_test.dir/src/output.cpp.obj"

# External object files for target raffinamento_test
raffinamento_test_EXTERNAL_OBJECTS =

raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/main_test.cpp.obj
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/src/geometry_class.cpp.obj
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/src/import.cpp.obj
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/src/refine.cpp.obj
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/src/output.cpp.obj
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/build.make
raffinamento_test.exe: C:/Users/matte/Desktop/Progetto_PCS/externals/Main_Install/googletest/lib/libgtest.a
raffinamento_test.exe: C:/Users/matte/Desktop/Progetto_PCS/externals/Main_Install/googletest/lib/libgtest_main.a
raffinamento_test.exe: C:/Users/matte/Desktop/Progetto_PCS/externals/Main_Install/googletest/lib/libgmock.a
raffinamento_test.exe: C:/Users/matte/Desktop/Progetto_PCS/externals/Main_Install/googletest/lib/libgmock_main.a
raffinamento_test.exe: C:/Users/matte/Desktop/Progetto_PCS/externals/Main_Install/googletest/lib/libgmock.a
raffinamento_test.exe: C:/Users/matte/Desktop/Progetto_PCS/externals/Main_Install/googletest/lib/libgtest.a
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/linklibs.rsp
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/objects1.rsp
raffinamento_test.exe: CMakeFiles/raffinamento_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\matte\Desktop\Progetto_PCS\Projects\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable raffinamento_test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\raffinamento_test.dir\link.txt --verbose=$(VERBOSE)
	C:\Qt\Tools\CMake_64\bin\cmake.exe -D TEST_TARGET=raffinamento_test -D TEST_EXECUTABLE=C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe -D TEST_EXECUTOR= -D TEST_WORKING_DIR=C:/Users/matte/Desktop/Progetto_PCS/Projects/Release -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=raffinamento_test_TESTS -D CTEST_FILE=C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P C:/Qt/Tools/CMake_64/share/cmake-3.24/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/raffinamento_test.dir/build: raffinamento_test.exe
.PHONY : CMakeFiles/raffinamento_test.dir/build

CMakeFiles/raffinamento_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\raffinamento_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/raffinamento_test.dir/clean

CMakeFiles/raffinamento_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento C:\Users\matte\Desktop\Progetto_PCS\Projects\Raffinamento C:\Users\matte\Desktop\Progetto_PCS\Projects\Release C:\Users\matte\Desktop\Progetto_PCS\Projects\Release C:\Users\matte\Desktop\Progetto_PCS\Projects\Release\CMakeFiles\raffinamento_test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raffinamento_test.dir/depend

