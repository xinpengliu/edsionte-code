# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/edsionte/hlfs/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/edsionte/hlfs/build

# Include any dependencies generated for this target.
include CMakeFiles/segclean.hlfs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/segclean.hlfs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/segclean.hlfs.dir/flags.make

CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o: CMakeFiles/segclean.hlfs.dir/flags.make
CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o: /home/edsionte/hlfs/src/tools/hlfs_seg_clean.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/edsionte/hlfs/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -g -Wstrict-prototypes -o CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o   -c /home/edsionte/hlfs/src/tools/hlfs_seg_clean.c

CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -g -Wstrict-prototypes -E /home/edsionte/hlfs/src/tools/hlfs_seg_clean.c > CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.i

CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -g -Wstrict-prototypes -S /home/edsionte/hlfs/src/tools/hlfs_seg_clean.c -o CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.s

CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.requires:
.PHONY : CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.requires

CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.provides: CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.requires
	$(MAKE) -f CMakeFiles/segclean.hlfs.dir/build.make CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.provides.build
.PHONY : CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.provides

CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.provides.build: CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o

# Object files for target segclean.hlfs
segclean_hlfs_OBJECTS = \
"CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o"

# External object files for target segclean.hlfs
segclean_hlfs_EXTERNAL_OBJECTS =

/home/edsionte/hlfs/output/bin/segclean.hlfs: CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o
/home/edsionte/hlfs/output/bin/segclean.hlfs: /home/edsionte/hlfs/output/lib32/libhlfs.so
/home/edsionte/hlfs/output/bin/segclean.hlfs: CMakeFiles/segclean.hlfs.dir/build.make
/home/edsionte/hlfs/output/bin/segclean.hlfs: CMakeFiles/segclean.hlfs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable /home/edsionte/hlfs/output/bin/segclean.hlfs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/segclean.hlfs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/segclean.hlfs.dir/build: /home/edsionte/hlfs/output/bin/segclean.hlfs
.PHONY : CMakeFiles/segclean.hlfs.dir/build

CMakeFiles/segclean.hlfs.dir/requires: CMakeFiles/segclean.hlfs.dir/tools/hlfs_seg_clean.c.o.requires
.PHONY : CMakeFiles/segclean.hlfs.dir/requires

CMakeFiles/segclean.hlfs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/segclean.hlfs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/segclean.hlfs.dir/clean

CMakeFiles/segclean.hlfs.dir/depend:
	cd /home/edsionte/hlfs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/edsionte/hlfs/src /home/edsionte/hlfs/src /home/edsionte/hlfs/build /home/edsionte/hlfs/build /home/edsionte/hlfs/build/CMakeFiles/segclean.hlfs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/segclean.hlfs.dir/depend

