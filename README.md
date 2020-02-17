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

# Run cmake
cmake -S ..

# Actual make
make
```

The actual minesweeper program will be in the build/bin/ directory.

# Testing

To run tests, cmake should be configured with `BUILD_TESTING` option:

```sh
cmake -S .. -DBUILD_TESTING=ON
```

This will create the different tests executables under build/bin/test/.

You can run `make test` to run the tests.

Additionnaly, you can set the `CTEST_OUTPUT_ON_FAILURE` environment variable
to let CTest output what happened if a test fails.
