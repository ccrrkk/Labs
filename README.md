# Experiments
This repository publish our experiments, frameworks and answers, data structure 2024, USTC, Teacher: Mingjun Xiao, TAs: Daoyu Wang, Jiabing Ou, Qingtian He, Bowen Wang

## CMAKE使用方式：

1. mkdir build ; cd build
2. cmake .. -G "MinGW Makefiles"
3. mingw32-make
4. (如无问题，应该生成了exe文件)./XXX.exe

## CMAKE下调试的方式
1. cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
2. mingw32-make
3. 按下F5开始调试

**注意**：此时有可能无法正常调试，会显示XX不存在之类的字样，这是由于我们这个文件夹中实际上存在多个多文件项目，需要修改.vscode中的文件路径。
方法：打开.vscode/launch.json,将"program"和"cwd"两行的路径改为实际项目的路径。

```
Labs
├─ 📁Lab1-2048-Framework
│  ├─ 📁build
│  │  ├─ 📁CMakeFiles
│  │  │  ├─ 📁2048.dir
│  │  │  │  ├─ 📁src
│  │  │  │  │  ├─ 📄Game.cpp.obj
│  │  │  │  │  ├─ 📄Game.cpp.obj.d
│  │  │  │  │  ├─ 📄GameBoard.cpp.obj
│  │  │  │  │  ├─ 📄GameBoard.cpp.obj.d
│  │  │  │  │  ├─ 📄GameRender.cpp.obj
│  │  │  │  │  ├─ 📄GameRender.cpp.obj.d
│  │  │  │  │  ├─ 📄InputHandler.cpp.obj
│  │  │  │  │  ├─ 📄InputHandler.cpp.obj.d
│  │  │  │  │  ├─ 📄main.cpp.obj
│  │  │  │  │  └─ 📄main.cpp.obj.d
│  │  │  │  ├─ 📄build.make
│  │  │  │  ├─ 📄cmake_clean.cmake
│  │  │  │  ├─ 📄compiler_depend.make
│  │  │  │  ├─ 📄compiler_depend.ts
│  │  │  │  ├─ 📄depend.make
│  │  │  │  ├─ 📄DependInfo.cmake
│  │  │  │  ├─ 📄flags.make
│  │  │  │  ├─ 📄link.txt
│  │  │  │  ├─ 📄linkLibs.rsp
│  │  │  │  ├─ 📄objects.a
│  │  │  │  ├─ 📄objects1.rsp
│  │  │  │  └─ 📄progress.make
│  │  │  ├─ 📁3.31.0-rc1
│  │  │  │  ├─ 📁CompilerIdC
│  │  │  │  │  ├─ 📁tmp
│  │  │  │  │  ├─ 📄a.exe
│  │  │  │  │  └─ 📄CMakeCCompilerId.c
│  │  │  │  ├─ 📁CompilerIdCXX
│  │  │  │  │  ├─ 📁tmp
│  │  │  │  │  ├─ 📄a.exe
│  │  │  │  │  └─ 📄CMakeCXXCompilerId.cpp
│  │  │  │  ├─ 📄CMakeCCompiler.cmake
│  │  │  │  ├─ 📄CMakeCXXCompiler.cmake
│  │  │  │  ├─ 📄CMakeDetermineCompilerABI_C.bin
│  │  │  │  ├─ 📄CMakeDetermineCompilerABI_CXX.bin
│  │  │  │  ├─ 📄CMakeRCCompiler.cmake
│  │  │  │  └─ 📄CMakeSystem.cmake
│  │  │  ├─ 📁CMakeScratch
│  │  │  ├─ 📁pkgRedirects
│  │  │  ├─ 📄cmake.check_cache
│  │  │  ├─ 📄CMakeConfigureLog.yaml
│  │  │  ├─ 📄CMakeDirectoryInformation.cmake
│  │  │  ├─ 📄Makefile.cmake
│  │  │  ├─ 📄Makefile2
│  │  │  ├─ 📄progress.marks
│  │  │  └─ 📄TargetDirectories.txt
│  │  ├─ 📄2048.exe
│  │  ├─ 📄CMakeCache.txt
│  │  ├─ 📄cmake_install.cmake
│  │  └─ 📄Makefile
│  ├─ 📁include
│  │  ├─ 📄Game.h
│  │  ├─ 📄GameBoard.h
│  │  ├─ 📄GameRender.h
│  │  └─ 📄InputHandler.h
│  ├─ 📁src
│  │  ├─ 📁output
│  │  ├─ 📄Game.cpp
│  │  ├─ 📄GameBoard.cpp
│  │  ├─ 📄GameRender.cpp
│  │  ├─ 📄history.txt
│  │  ├─ 📄InputHandler.cpp
│  │  └─ 📄main.cpp
│  ├─ 📄CMakeLists.txt
│  └─ 📄test.md
├─ 📁Lab2
│  ├─ 📁Framework
│  │  ├─ 📁include
│  │  │  ├─ 📄list.h
│  │  │  ├─ 📄queue.h
│  │  │  ├─ 📄stack.h
│  │  │  └─ 📄unordered_set.h
│  │  ├─ 📁src
│  │  │  ├─ 📁1_Test
│  │  │  │  ├─ 📄CMakeLists.txt
│  │  │  │  └─ 📄main.cpp
│  │  │  ├─ 📁2_Expression
│  │  │  │  ├─ 📄calculator.cpp
│  │  │  │  ├─ 📄calculator.h
│  │  │  │  ├─ 📄CMakeLists.txt
│  │  │  │  └─ 📄main.cpp
│  │  │  ├─ 📁3_Robot
│  │  │  │  ├─ 📄CMakeLists.txt
│  │  │  │  ├─ 📄main.cpp
│  │  │  │  ├─ 📄walk.cpp
│  │  │  │  └─ 📄walk.h
│  │  │  ├─ 📁structures
│  │  │  │  ├─ 📄CMakeLists.txt
│  │  │  │  ├─ 📄queue.cpp
│  │  │  │  ├─ 📄stack.cpp
│  │  │  │  └─ 📄unordered_set.cpp
│  │  │  ├─ 📄.DS_Store
│  │  │  └─ 📄CMakeLists.txt
│  │  ├─ 📄.DS_Store
│  │  └─ 📄CMakeLists.txt
│  ├─ 📁__MACOSX
│  │  ├─ 📁Framework
│  │  │  ├─ 📁include
│  │  │  │  ├─ 📄._list.h
│  │  │  │  └─ 📄._unordered_set.h
│  │  │  ├─ 📁src
│  │  │  │  ├─ 📁1_Test
│  │  │  │  │  └─ 📄._main.cpp
│  │  │  │  ├─ 📁2_Expression
│  │  │  │  │  ├─ 📄._calculator.cpp
│  │  │  │  │  └─ 📄._main.cpp
│  │  │  │  ├─ 📁3_Robot
│  │  │  │  │  ├─ 📄._main.cpp
│  │  │  │  │  ├─ 📄._walk.cpp
│  │  │  │  │  └─ 📄._walk.h
│  │  │  │  ├─ 📄._.DS_Store
│  │  │  │  └─ 📄._CMakeLists.txt
│  │  │  ├─ 📄._.DS_Store
│  │  │  └─ 📄._CMakeLists.txt
│  │  └─ 📄._Framework
│  └─ 📄Lab2-exp-manual-v2.pdf
└─ 📄README.md
```