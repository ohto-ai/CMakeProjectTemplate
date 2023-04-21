# CMake Project Template

This is a template for a CMake project. It is intended to be used as a starting point for new projects.

## Usage

```bash
# configure project
cmake -Bbuild

# build binaries
cmake --build build --config Release -j8

# build ubuntu deb package
cmake --build build --config Release --target package -j8

# build all
cmake --build build --config Release --target all -j8
```
