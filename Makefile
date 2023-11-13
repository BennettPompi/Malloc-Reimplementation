# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bip7/bip7-malloc-indexed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bip7/bip7-malloc-indexed

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/local/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/bip7/bip7-malloc-indexed/CMakeFiles /home/bip7/bip7-malloc-indexed//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/bip7/bip7-malloc-indexed/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named bip7-malloc-indexed

# Build rule for target.
bip7-malloc-indexed: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 bip7-malloc-indexed
.PHONY : bip7-malloc-indexed

# fast build rule for target.
bip7-malloc-indexed/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/build
.PHONY : bip7-malloc-indexed/fast

TestEntry.o: TestEntry.cpp.o
.PHONY : TestEntry.o

# target to build an object file
TestEntry.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/TestEntry.cpp.o
.PHONY : TestEntry.cpp.o

TestEntry.i: TestEntry.cpp.i
.PHONY : TestEntry.i

# target to preprocess a source file
TestEntry.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/TestEntry.cpp.i
.PHONY : TestEntry.cpp.i

TestEntry.s: TestEntry.cpp.s
.PHONY : TestEntry.s

# target to generate assembly for a file
TestEntry.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/TestEntry.cpp.s
.PHONY : TestEntry.cpp.s

allocMap.o: allocMap.cpp.o
.PHONY : allocMap.o

# target to build an object file
allocMap.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/allocMap.cpp.o
.PHONY : allocMap.cpp.o

allocMap.i: allocMap.cpp.i
.PHONY : allocMap.i

# target to preprocess a source file
allocMap.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/allocMap.cpp.i
.PHONY : allocMap.cpp.i

allocMap.s: allocMap.cpp.s
.PHONY : allocMap.s

# target to generate assembly for a file
allocMap.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/allocMap.cpp.s
.PHONY : allocMap.cpp.s

largeMalloc.o: largeMalloc.cpp.o
.PHONY : largeMalloc.o

# target to build an object file
largeMalloc.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/largeMalloc.cpp.o
.PHONY : largeMalloc.cpp.o

largeMalloc.i: largeMalloc.cpp.i
.PHONY : largeMalloc.i

# target to preprocess a source file
largeMalloc.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/largeMalloc.cpp.i
.PHONY : largeMalloc.cpp.i

largeMalloc.s: largeMalloc.cpp.s
.PHONY : largeMalloc.s

# target to generate assembly for a file
largeMalloc.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/largeMalloc.cpp.s
.PHONY : largeMalloc.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/main.cpp.s
.PHONY : main.cpp.s

malloc.o: malloc.cpp.o
.PHONY : malloc.o

# target to build an object file
malloc.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/malloc.cpp.o
.PHONY : malloc.cpp.o

malloc.i: malloc.cpp.i
.PHONY : malloc.i

# target to preprocess a source file
malloc.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/malloc.cpp.i
.PHONY : malloc.cpp.i

malloc.s: malloc.cpp.s
.PHONY : malloc.s

# target to generate assembly for a file
malloc.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/malloc.cpp.s
.PHONY : malloc.cpp.s

smallMalloc.o: smallMalloc.cpp.o
.PHONY : smallMalloc.o

# target to build an object file
smallMalloc.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/smallMalloc.cpp.o
.PHONY : smallMalloc.cpp.o

smallMalloc.i: smallMalloc.cpp.i
.PHONY : smallMalloc.i

# target to preprocess a source file
smallMalloc.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/smallMalloc.cpp.i
.PHONY : smallMalloc.cpp.i

smallMalloc.s: smallMalloc.cpp.s
.PHONY : smallMalloc.s

# target to generate assembly for a file
smallMalloc.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/smallMalloc.cpp.s
.PHONY : smallMalloc.cpp.s

timer.o: timer.cpp.o
.PHONY : timer.o

# target to build an object file
timer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/timer.cpp.o
.PHONY : timer.cpp.o

timer.i: timer.cpp.i
.PHONY : timer.i

# target to preprocess a source file
timer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/timer.cpp.i
.PHONY : timer.cpp.i

timer.s: timer.cpp.s
.PHONY : timer.s

# target to generate assembly for a file
timer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bip7-malloc-indexed.dir/build.make CMakeFiles/bip7-malloc-indexed.dir/timer.cpp.s
.PHONY : timer.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... bip7-malloc-indexed"
	@echo "... TestEntry.o"
	@echo "... TestEntry.i"
	@echo "... TestEntry.s"
	@echo "... allocMap.o"
	@echo "... allocMap.i"
	@echo "... allocMap.s"
	@echo "... largeMalloc.o"
	@echo "... largeMalloc.i"
	@echo "... largeMalloc.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... malloc.o"
	@echo "... malloc.i"
	@echo "... malloc.s"
	@echo "... smallMalloc.o"
	@echo "... smallMalloc.i"
	@echo "... smallMalloc.s"
	@echo "... timer.o"
	@echo "... timer.i"
	@echo "... timer.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

