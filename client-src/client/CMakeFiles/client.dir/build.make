# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mud/cProjects/comp3980ass2/client-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mud/cProjects/comp3980ass2/client-src/client

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/src/main.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/main.c.o: /Users/mud/cProjects/comp3980ass2/client-src/src/main.c
CMakeFiles/client.dir/src/main.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mud/cProjects/comp3980ass2/client-src/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/client.dir/src/main.c.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-misc-unused-parameters,-clang-diagnostic-unused-parameter,-clang-diagnostic-unused-variable,-cppcoreguidelines-init-variables,-readability-identifier-length,-clang-diagnostic-unused-but-set-variable,-clang-analyzer-deadcode.DeadStores,-altera-id-dependent-backward-branch,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-unroll-loops,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.strcpy;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/Users/mud/cProjects/comp3980ass2/client-src/src/main.c -- /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/src/main.c.o -MF CMakeFiles/client.dir/src/main.c.o.d -o CMakeFiles/client.dir/src/main.c.o -c /Users/mud/cProjects/comp3980ass2/client-src/src/main.c

CMakeFiles/client.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mud/cProjects/comp3980ass2/client-src/src/main.c > CMakeFiles/client.dir/src/main.c.i

CMakeFiles/client.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mud/cProjects/comp3980ass2/client-src/src/main.c -o CMakeFiles/client.dir/src/main.c.s

CMakeFiles/client.dir/src/error.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/error.c.o: /Users/mud/cProjects/comp3980ass2/client-src/src/error.c
CMakeFiles/client.dir/src/error.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mud/cProjects/comp3980ass2/client-src/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/client.dir/src/error.c.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-misc-unused-parameters,-clang-diagnostic-unused-parameter,-clang-diagnostic-unused-variable,-cppcoreguidelines-init-variables,-readability-identifier-length,-clang-diagnostic-unused-but-set-variable,-clang-analyzer-deadcode.DeadStores,-altera-id-dependent-backward-branch,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-unroll-loops,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.strcpy;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/Users/mud/cProjects/comp3980ass2/client-src/src/error.c -- /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/src/error.c.o -MF CMakeFiles/client.dir/src/error.c.o.d -o CMakeFiles/client.dir/src/error.c.o -c /Users/mud/cProjects/comp3980ass2/client-src/src/error.c

CMakeFiles/client.dir/src/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/src/error.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mud/cProjects/comp3980ass2/client-src/src/error.c > CMakeFiles/client.dir/src/error.c.i

CMakeFiles/client.dir/src/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/src/error.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mud/cProjects/comp3980ass2/client-src/src/error.c -o CMakeFiles/client.dir/src/error.c.s

CMakeFiles/client.dir/src/client.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/client.c.o: /Users/mud/cProjects/comp3980ass2/client-src/src/client.c
CMakeFiles/client.dir/src/client.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mud/cProjects/comp3980ass2/client-src/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/client.dir/src/client.c.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-misc-unused-parameters,-clang-diagnostic-unused-parameter,-clang-diagnostic-unused-variable,-cppcoreguidelines-init-variables,-readability-identifier-length,-clang-diagnostic-unused-but-set-variable,-clang-analyzer-deadcode.DeadStores,-altera-id-dependent-backward-branch,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-unroll-loops,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.strcpy;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/Users/mud/cProjects/comp3980ass2/client-src/src/client.c -- /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/src/client.c.o -MF CMakeFiles/client.dir/src/client.c.o.d -o CMakeFiles/client.dir/src/client.c.o -c /Users/mud/cProjects/comp3980ass2/client-src/src/client.c

CMakeFiles/client.dir/src/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/src/client.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mud/cProjects/comp3980ass2/client-src/src/client.c > CMakeFiles/client.dir/src/client.c.i

CMakeFiles/client.dir/src/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/src/client.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mud/cProjects/comp3980ass2/client-src/src/client.c -o CMakeFiles/client.dir/src/client.c.s

CMakeFiles/client.dir/src/comm.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/comm.c.o: /Users/mud/cProjects/comp3980ass2/client-src/src/comm.c
CMakeFiles/client.dir/src/comm.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mud/cProjects/comp3980ass2/client-src/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/client.dir/src/comm.c.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-misc-unused-parameters,-clang-diagnostic-unused-parameter,-clang-diagnostic-unused-variable,-cppcoreguidelines-init-variables,-readability-identifier-length,-clang-diagnostic-unused-but-set-variable,-clang-analyzer-deadcode.DeadStores,-altera-id-dependent-backward-branch,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-unroll-loops,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.strcpy;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/Users/mud/cProjects/comp3980ass2/client-src/src/comm.c -- /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/src/comm.c.o -MF CMakeFiles/client.dir/src/comm.c.o.d -o CMakeFiles/client.dir/src/comm.c.o -c /Users/mud/cProjects/comp3980ass2/client-src/src/comm.c

CMakeFiles/client.dir/src/comm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/src/comm.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mud/cProjects/comp3980ass2/client-src/src/comm.c > CMakeFiles/client.dir/src/comm.c.i

CMakeFiles/client.dir/src/comm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/src/comm.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mud/cProjects/comp3980ass2/client-src/src/comm.c -o CMakeFiles/client.dir/src/comm.c.s

CMakeFiles/client.dir/src/util.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/util.c.o: /Users/mud/cProjects/comp3980ass2/client-src/src/util.c
CMakeFiles/client.dir/src/util.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mud/cProjects/comp3980ass2/client-src/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/client.dir/src/util.c.o"
	$(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-misc-unused-parameters,-clang-diagnostic-unused-parameter,-clang-diagnostic-unused-variable,-cppcoreguidelines-init-variables,-readability-identifier-length,-clang-diagnostic-unused-but-set-variable,-clang-analyzer-deadcode.DeadStores,-altera-id-dependent-backward-branch,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-unroll-loops,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.strcpy;--quiet;--extra-arg-before=--driver-mode=gcc" --source=/Users/mud/cProjects/comp3980ass2/client-src/src/util.c -- /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/src/util.c.o -MF CMakeFiles/client.dir/src/util.c.o.d -o CMakeFiles/client.dir/src/util.c.o -c /Users/mud/cProjects/comp3980ass2/client-src/src/util.c

CMakeFiles/client.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/src/util.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mud/cProjects/comp3980ass2/client-src/src/util.c > CMakeFiles/client.dir/src/util.c.i

CMakeFiles/client.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/src/util.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mud/cProjects/comp3980ass2/client-src/src/util.c -o CMakeFiles/client.dir/src/util.c.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/main.c.o" \
"CMakeFiles/client.dir/src/error.c.o" \
"CMakeFiles/client.dir/src/client.c.o" \
"CMakeFiles/client.dir/src/comm.c.o" \
"CMakeFiles/client.dir/src/util.c.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/src/main.c.o
client: CMakeFiles/client.dir/src/error.c.o
client: CMakeFiles/client.dir/src/client.c.o
client: CMakeFiles/client.dir/src/comm.c.o
client: CMakeFiles/client.dir/src/util.c.o
client: CMakeFiles/client.dir/build.make
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mud/cProjects/comp3980ass2/client-src/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /Users/mud/cProjects/comp3980ass2/client-src/client && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mud/cProjects/comp3980ass2/client-src /Users/mud/cProjects/comp3980ass2/client-src /Users/mud/cProjects/comp3980ass2/client-src/client /Users/mud/cProjects/comp3980ass2/client-src/client /Users/mud/cProjects/comp3980ass2/client-src/client/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend
