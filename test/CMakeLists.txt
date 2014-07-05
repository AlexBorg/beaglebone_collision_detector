# Make sure the compiler can find include files from our Hello library. 
include_directories (${BBCD_SOURCE_DIR}/3rdparty/include) 

# FIND_LIBRARY (BBBIO_LIBRARY NAMES BBBio PATHS {$BBCD_SOURCE_DIR}"/3rdparty/lib")

# Make sure the linker can find the 3rd party libraries. 
link_directories (${BBCD_BINARY_DIR}/3rdparty/lib) 

# Add executable called "ioTest" that is built from the source files 
# "ioTest.cpp". The extensions are automatically found. 
add_executable (ioTest ioTest.cpp) 

# Link the executable to the Hello library. 
target_link_libraries (ioTest ${BBCD_SOURCE_DIR}/3rdparty/lib/libBBBio.a) 

