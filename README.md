# beaglebone collision dector

A project to accept input from stereoscopic cameras in order to determine if objects will collide with the camera mounting.Designed to work for the beagelbone black.

### Resources


### Compiling
It is highly reccomended that you create a build subdirectory at the top level of the source and run cmake from there.

On the beagleboard: requires cmake
	cmake <target source dir>
	make

On x86 Linux system (tested using ubuntu 14.4): requires cmake and gnueabihf
	cmake -DGCC_COMPILER_VERSION=4.8 <target source dir>
	make
replace 4.8 with the version of the gnueabihf compiler installed

### authors
Alex Borg
Robert Sebastian

