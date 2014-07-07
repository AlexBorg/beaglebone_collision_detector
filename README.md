# beaglebone collision dector

A project to accept input from stereoscopic cameras in order to determine if objects will collide with the camera mounting.Designed to work for the beagelbone black.

### Resources


### Compiling
It is highly reccomended that you create a build subdirectory at the top level of the source and run cmake from there.

On the beagleboard: requires cmake, opencv, and xenomai
	cmake <target source dir>
	make

options that can be added:
	cmake -DGCC_COMPILER_VERSION=4.8 -DXENOMAI_BASE_DIR=<copy of /usr/xenomai> <target source dir>

### authors
Alex Borg
Robert Sebastian

