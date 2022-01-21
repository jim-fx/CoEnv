# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/jim/COCO/CoEnv/scanner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jim/COCO/CoEnv/scanner/build

# Include any dependencies generated for this target.
include CMakeFiles/scanner.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/scanner.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/scanner.dir/flags.make

CMakeFiles/scanner.dir/src/main.cpp.o: CMakeFiles/scanner.dir/flags.make
CMakeFiles/scanner.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jim/COCO/CoEnv/scanner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/scanner.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scanner.dir/src/main.cpp.o -c /home/jim/COCO/CoEnv/scanner/src/main.cpp

CMakeFiles/scanner.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scanner.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jim/COCO/CoEnv/scanner/src/main.cpp > CMakeFiles/scanner.dir/src/main.cpp.i

CMakeFiles/scanner.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scanner.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jim/COCO/CoEnv/scanner/src/main.cpp -o CMakeFiles/scanner.dir/src/main.cpp.s

# Object files for target scanner
scanner_OBJECTS = \
"CMakeFiles/scanner.dir/src/main.cpp.o"

# External object files for target scanner
scanner_EXTERNAL_OBJECTS =

scanner: CMakeFiles/scanner.dir/src/main.cpp.o
scanner: CMakeFiles/scanner.dir/build.make
scanner: /usr/local/lib/libopencv_gapi.so.4.5.4
scanner: /usr/local/lib/libopencv_stitching.so.4.5.4
scanner: /usr/local/lib/libopencv_aruco.so.4.5.4
scanner: /usr/local/lib/libopencv_barcode.so.4.5.4
scanner: /usr/local/lib/libopencv_bgsegm.so.4.5.4
scanner: /usr/local/lib/libopencv_bioinspired.so.4.5.4
scanner: /usr/local/lib/libopencv_ccalib.so.4.5.4
scanner: /usr/local/lib/libopencv_dnn_objdetect.so.4.5.4
scanner: /usr/local/lib/libopencv_dnn_superres.so.4.5.4
scanner: /usr/local/lib/libopencv_dpm.so.4.5.4
scanner: /usr/local/lib/libopencv_face.so.4.5.4
scanner: /usr/local/lib/libopencv_freetype.so.4.5.4
scanner: /usr/local/lib/libopencv_fuzzy.so.4.5.4
scanner: /usr/local/lib/libopencv_hfs.so.4.5.4
scanner: /usr/local/lib/libopencv_img_hash.so.4.5.4
scanner: /usr/local/lib/libopencv_intensity_transform.so.4.5.4
scanner: /usr/local/lib/libopencv_line_descriptor.so.4.5.4
scanner: /usr/local/lib/libopencv_mcc.so.4.5.4
scanner: /usr/local/lib/libopencv_quality.so.4.5.4
scanner: /usr/local/lib/libopencv_rapid.so.4.5.4
scanner: /usr/local/lib/libopencv_reg.so.4.5.4
scanner: /usr/local/lib/libopencv_rgbd.so.4.5.4
scanner: /usr/local/lib/libopencv_saliency.so.4.5.4
scanner: /usr/local/lib/libopencv_stereo.so.4.5.4
scanner: /usr/local/lib/libopencv_structured_light.so.4.5.4
scanner: /usr/local/lib/libopencv_superres.so.4.5.4
scanner: /usr/local/lib/libopencv_surface_matching.so.4.5.4
scanner: /usr/local/lib/libopencv_tracking.so.4.5.4
scanner: /usr/local/lib/libopencv_videostab.so.4.5.4
scanner: /usr/local/lib/libopencv_wechat_qrcode.so.4.5.4
scanner: /usr/local/lib/libopencv_xfeatures2d.so.4.5.4
scanner: /usr/local/lib/libopencv_xobjdetect.so.4.5.4
scanner: /usr/local/lib/libopencv_xphoto.so.4.5.4
scanner: /usr/local/lib/libopencv_shape.so.4.5.4
scanner: /usr/local/lib/libopencv_highgui.so.4.5.4
scanner: /usr/local/lib/libopencv_datasets.so.4.5.4
scanner: /usr/local/lib/libopencv_plot.so.4.5.4
scanner: /usr/local/lib/libopencv_text.so.4.5.4
scanner: /usr/local/lib/libopencv_ml.so.4.5.4
scanner: /usr/local/lib/libopencv_phase_unwrapping.so.4.5.4
scanner: /usr/local/lib/libopencv_optflow.so.4.5.4
scanner: /usr/local/lib/libopencv_ximgproc.so.4.5.4
scanner: /usr/local/lib/libopencv_video.so.4.5.4
scanner: /usr/local/lib/libopencv_videoio.so.4.5.4
scanner: /usr/local/lib/libopencv_imgcodecs.so.4.5.4
scanner: /usr/local/lib/libopencv_objdetect.so.4.5.4
scanner: /usr/local/lib/libopencv_calib3d.so.4.5.4
scanner: /usr/local/lib/libopencv_dnn.so.4.5.4
scanner: /usr/local/lib/libopencv_features2d.so.4.5.4
scanner: /usr/local/lib/libopencv_flann.so.4.5.4
scanner: /usr/local/lib/libopencv_photo.so.4.5.4
scanner: /usr/local/lib/libopencv_imgproc.so.4.5.4
scanner: /usr/local/lib/libopencv_core.so.4.5.4
scanner: CMakeFiles/scanner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jim/COCO/CoEnv/scanner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable scanner"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scanner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/scanner.dir/build: scanner

.PHONY : CMakeFiles/scanner.dir/build

CMakeFiles/scanner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/scanner.dir/cmake_clean.cmake
.PHONY : CMakeFiles/scanner.dir/clean

CMakeFiles/scanner.dir/depend:
	cd /home/jim/COCO/CoEnv/scanner/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jim/COCO/CoEnv/scanner /home/jim/COCO/CoEnv/scanner /home/jim/COCO/CoEnv/scanner/build /home/jim/COCO/CoEnv/scanner/build /home/jim/COCO/CoEnv/scanner/build/CMakeFiles/scanner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/scanner.dir/depend

