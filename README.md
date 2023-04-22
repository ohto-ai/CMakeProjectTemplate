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

## Guide

See our discussion [here](https://github.com/Ohto-Ai/CMakeProjectTemplate/discussions/2)

### Package Variables

#### For Ubuntu
See [this](https://cmake.org/cmake/help/latest/cpack_gen/deb.html) for more information.

`CPACK_DEBIAN_PACKAGE_DEPENDS` - list of dependencies for the package
You can use `ldd <path-to-binary>` to get the list of dependencies.
Set the variable in the `CMakeLists.txt` file like this:
```cmake
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurl4 (>= 7.58.0), libssl1.1 (>= 1.1.0)")
```

### For Windows
See [this](https://cmake.org/cmake/help/latest/cpack_gen/nsis.html) for more information.
## Example

```bash
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ cmake -Bbuild
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Build version: 8d50a17
-- Performing Test GNU_BIG_OBJ_FLAG_ENABLE
-- Performing Test GNU_BIG_OBJ_FLAG_ENABLE - Failed
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE  
-- Configuring done
-- Generating done
-- Build files have been written to: /home/ohtoai/workspace/CMakeProjectTemplate/build
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ cmake --build build/ --target all -j8
Scanning dependencies of target cmake-project-template
Scanning dependencies of target version.test
[ 25%] Building CXX object src/CMakeFiles/cmake-project-template.dir/main.cpp.o
[ 50%] Building CXX object test/CMakeFiles/version.test.dir/version.test.cpp.o
[ 75%] Linking CXX executable cmake-project-template
[ 75%] Built target cmake-project-template
[100%] Linking CXX executable version.test
[100%] Built target version.test
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ cmake --build build/ --target package
[ 50%] Built target cmake-project-template
[100%] Built target version.test
Run CPack packaging tool...
CPack: Create package using DEB
CPack: Install projects
CPack: - Run preinstall target for: CMakeProjectTemplate
CPack: - Install project: CMakeProjectTemplate []
CPack: Create package
-- CPACK_DEBIAN_PACKAGE_DEPENDS not set, the package will have no dependencies.
CPack: - package: /home/ohtoai/workspace/CMakeProjectTemplate/build/cmake-project-template-0.0.0-Linux.deb generated.
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ cd build/test/ && ctest -C Release --output-on-failure && cd -
Test project /home/ohtoai/workspace/CMakeProjectTemplate/build/test
    Start 1: version.test
1/1 Test #1: version.test .....................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
/home/ohtoai/workspace/CMakeProjectTemplate
```
### Use package

#### Windows

![](doc/img/package_windows_thumb.png)
![](doc/img/package_windows_welcome.png)

#### Ubuntu

```log
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ sudo dpkg -i cmake-project-template-0.0.0-Linux.deb
Selecting previously unselected package cmake-project-template.
(Reading database ... 139665 files and directories currently installed.)
Preparing to unpack .../cmake-project-template-0.0.0-Linux.deb ...
Unpacking cmake-project-template (0.0.0) ...
Setting up cmake-project-template (0.0.0) ...
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ which cmake-project-template
/usr/bin/cmake-project-template
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ cmake-project-template 
Hello, World!
AppName: cmake-project-template
Author: 
Email: 
Version: 0.0.0
CommitHash: cf106a5
CommitDate: 2023-04-22
BuildDate: Apr 22 2023
BuildTime: 15:00:21
IsDevVersion: 1
```
