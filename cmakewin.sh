# Create the 'build' folder
mkdir build

# Change into the 'build' folder
cd build

# Run cmake with the specified toolchain file
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-mingw.cmake

# Change back to the previous directory
cd ..
