# CMake Project Template

这是为跨平台 C++ 项目设计的 CMake 模板仓库，易于上手。

目前此项目仍处于开发阶段。

## 主要功能

- [x] 全平台 C++ 项目编译
- [x] 测试框架支持
    - [x] Catch2
    - [ ] GTest 【计划中】
- [ ] Qt 项目支持 【计划中】
- [x] Windows 打包
- [x] DEB打包
- [ ] MacOS 打包 【计划中】

## 如何使用

你可以按照以下步骤来使用此模板：

1. [创建](#创建仓库)你的仓库
2. 了解[项目结构](#项目结构)
3. 编写、[编译](#项目编译)你的项目代码
4. 编写测试代码[执行测试](#项目测试)
5. [打包](#项目打包)可执行文件
6. GitHub [自动化构建](#自动化构建)


### 创建仓库

点击 [Use this template](https://github.com/Ohto-Ai/CMakeProjectTemplate/generate) 生成自己的项目。

### 项目结构

cmake 目录存放构建工具使用的 cmake 脚本。  
doc 目录存放项目文档。  
inc 为项目共用的包含目录。  
lib 为项目共用的库目录。  
src 为项目主要代码目录。  
test 存放测试代码。

```
.
├── cmake
│   ├── package.cmake
│   └── version_from_git_tag.cmake
├── CMakeLists.txt
├── doc
│   └── img
│       ├── package_windows_finish.png
│       ├── package_windows_installing.png
│       ├── package_windows_install_options.png
│       ├── package_windows_install_path.png
│       ├── package_windows_license.png
│       ├── package_windows_start_menu.png
│       ├── package_windows_thumb.png
│       └── package_windows_welcome.png
├── inc
│   └── catch2
│       └── catch.hpp
├── lib
├── LICENSE
├── README.md
├── src
│   ├── CMakeLists.txt
│   ├── inc
│   │   └── version.h.in
│   ├── main.cpp
│   └── res
│       └── icon.ico
└── test
    ├── CMakeLists.txt
    └── version.test.cpp
```

### 项目编译

使用以下命令编译示例代码
```bash
cmake -Bbuild
cmake --build build/ --target install
```

这是一个编译示例：

```log
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

你应当在 bin/ 目录看到示例代码编译出的二进制可执行文件 `cmake-project-template`。

### 项目测试

当构建项目代码时，测试代码也应当会一并被构建。
```bash
cmake --build build/ 
```
在 build/test/ 目录中，你可以执行这些程序查看测试结果，也可以使用`ctest`来执行所有的测试程序。

以下是一个示例：
```log
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate$ cd build/test/
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate/build/test$ ctest -C Release --output-on-failure
Test project /home/ohtoai/workspace/CMakeProjectTemplate/build/test
    Start 1: version.test
1/1 Test #1: version.test .....................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.02 sec
ohtoai@ohtoai:~/workspace/CMakeProjectTemplate/build/test$ ./version.test 
===============================================================================
All tests passed (2 assertions in 1 test case)
```

关于如何使用模板自带的[Catch2](https://github.com/catchorg/Catch2/tree/v2.x)，你可以查看他们的[文档](https://github.com/catchorg/Catch2/blob/v2.x/docs/tutorial.md)。  
注意我使用的 Catch2 版本为 v2，因为新版的 Catch2 不再是单头文件的库。

### 项目打包

模板提供了 Windows 与 Ubuntu 下的打包支持。
```bash
cmake --build build/ --target package
```
你可以在 build 目录找到打包的安装文件。

关于 Ubuntu 下的包依赖，你可以在 CMakeLists.txt 中设置`CPACK_DEBIAN_PACKAGE_DEPENDS`变量，例如
```cmake
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurl4 (>= 7.58.0), libssl1.1 (>= 1.1.0)")
```
你可以使用`ldd`命令查看编译出的二进制文件依赖信息。

Windows 打包工具 NSIS 的信息可以查看[此处](https://cmake.org/cmake/help/latest/cpack_gen/nsis.html)  
Ubuntu 打包工具 DEB 的信息可以查看[此处](https://cmake.org/cmake/help/latest/cpack_gen/deb.html)

以下是安装示例：

- Windows

![](doc/img/package_windows_thumb.png)
![](doc/img/package_windows_welcome.png)

- Ubuntu

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

### 自动化构建

项目支持 GitHub Action 工作流，默认已添加编译、测试、打包的流程，后续将添加自动发布的流程。  
详细信息请查看 .github/workflows/ 文件夹。
