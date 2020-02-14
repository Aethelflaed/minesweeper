# Minesweeper

This repositoy hosts the ongoing development of a minesweeper program, created for educational and fun purpose.

Comments and contributions are welcome.

# Build minesweeper

Minesweeper build system uses conan for dependencies management and CMake for the actual build.

As such, to properly build the system, you should:

```sh
# Install conan files
rm -rf build
mkdir build && cd build
conan install ..
cd ..

# Run cmake
cmake .

# Actual make
make
```

The actual minesweeper program will be in the bin/ directory.
