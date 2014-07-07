# Make sure the compiler can find include files from our 3rd party library. 
include_directories (${BBCD_SOURCE_DIR}/3rdparty/include/BBBIO ${OPENCV_INC_DIR} ${XENOMAI_INC_DIR}) 

# Make sure the linker can find the 3rd party libraries. 
link_directories (${BBCD_SOURCE_DIR}/3rdparty/lib/ ${XENOMAI_LIB_DIR}) 

# Add executable called "bbcd" that is built from the source files 
# "ioTest.cpp". The extensions are automatically found. 
add_executable (bbcd main.cpp) 

# Link the executable to the 3rdparty library. 
target_link_libraries (bbcd BBBio opencv_highgui opencv_core native rt rtdm xenomai ) 

