# lvtlibcxx

## Description

This library does not represent a specific library, (yes, I know, the name of the repository does not correspond to the content). This repository was created in order to access it using its functions in your projects. The functions are separated by <code>namespace</code>s. cmake file is just for my training in writing similar files.

## Compiling

### Using CMake & GNU GCC

```console
<loveit@fedora lvtlibcxx>$ cmake .
-- The CXX compiler identification is GNU 12.2.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.5s)
-- Generating done (0.0s)
-- Build files have been written to: ${YOUR_PATH}
<loveit@fedora lvtlibcxx>$ cmake --build .
[ 50%] Building CXX object CMakeFiles/lvt.dir/lvt.cpp.o
[100%] Linking CXX shared library liblvt.so
[100%] Built target lvt
<loveit@fedora lvtlibcxx>$ gcc -g -c main.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o main.o
<loveit@fedora lvtlibcxx>$ ls
CMakeCache.txt       liblvt.so      lvt.hpp       Makefile
CMakeFiles           liblvt.so.1    lvt_impl.hpp  cmake_install.cmake
liblvt.so.1.0        main.cpp       README.md     CMakeLists.txt
lvt.cpp              main.o
<loveit@fedora lvtlibcxx>$ pwd | xclip -sel c
<loveit@fedora lvtlibcxx>$ gcc main.o -L${YOUR_PATH} -llvt -lstdc++ -std=c++23 -o main.out
<loveit@fedora lvtlibcxx>$ rm main.o
<loveit@fedora lvtlibcxx>$ LD_LIBRARY_PATH=${YOUR_PATH} ./main.out
```

#### Only commands

<b>Attention.</b> These commands creating new subdirectory with shared library in your "/opt" directory.

```console
cmake .
cmake --build .
gcc -g -c main.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o main.o
mkdir -p /opt/lvt
mv liblvt.so /opt/lvt
gcc main.o -L/opt/lvt -llvt -lstdc++ -std=c++23 -o main.out
rm main.o
LD_LIBRARY_PATH=/opt/lvt ./main.out

```

Command <code>cmake --build .</code> can be replaced with <code>make</code>
File <b>main.cpp</b> presented your source file with the "main()" function

### Using GNU GCC

```console
<loveit@fedora lvtlibcxx>$ gcc -g -c lvt.cpp -lstdc++ -std=c++23 -fPIC -Wall -Wpedantic -Wextra -o lvt.o
<loveit@fedora lvtlibcxx>$ gcc -shared lvt.o -o liblvt.so
<loveit@fedora lvtlibcxx>$ ls
CMakeLists.txt  lvt.cpp  lvt_impl.hpp  main.cpp README.md
liblvt.so       lvt.hpp  lvt.o
<loveit@fedora lvtlibcxx>$ gcc -g -c main.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o main.o
<loveit@fedora lvtlibcxx>$ pwd | xclip -sel c
<loveit@fedora lvtlibcxx>$ gcc main.o -L${COPIED_FROM_PWD_PATH} -llvt -lstdc++ -std=c++23 -o main.out
<loveit@fedora lvtlibcxx>$ rm lvt.o main.o
<loveit@fedora lvtlibcxx>$ LD_LIBRARY_PATH=${COPIED_FROM_PWD_PATH} ./main.out
```

#### Only commands

<b>Attention.</b> These commands creating new subdirectory with shared library in your "/opt" directory.

```console
gcc -g -c lvt.cpp -lstdc++ -std=c++23 -fPIC -Wall -Wpedantic -Wextra -o lvt.o
gcc -shared lvt.o -o liblvt.so
gcc -g -c main.cpp -lstdc++ -std=c++23 -Wall -Wpedantic -Wextra -o main.o
mkdir -p /opt/lvt
mv liblvt.so /opt/lvt
gcc main.o -L/opt/lvt -llvt -lstdc++ -std=c++23 -o main.out
rm lvt.o main.o
LD_LIBRARY_PATH=/opt/lvt ./main.out
```

- 1st line - compiling with "[-g](https://www.rapidtables.com/code/linux/gcc/gcc-g.html)" (default info about debug), "[-c](https://www.rapidtables.com/code/linux/gcc/gcc-c.html)" (means compile), "[-std=c++23](https://gcc.gnu.org/projects/cxx-status.html)" (c++ 23 version of standard), "[-fPIC](https://www.rapidtables.com/code/linux/gcc/gcc-fpic.html)" (position independent code. It's nead to compile shared library), "[-Wall](https://www.rapidtables.com/code/linux/gcc/gcc-wall.html) [-Wpedantic -Wextra](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)" (connects all kinds of warnings), "[-o](https://www.rapidtables.com/code/linux/gcc/gcc-o.html#output%20file)" (output file)
- 2nd line - "[-shared](https://www.rapidtables.com/code/linux/gcc/gcc-shared.html)" - compiling shared library with ".so" extension - UNIX/Linux dynamic library
- 3rd line - ("ls" doesn't counts) compiling source code with "main()" function to an object file
- 4th line - copying path of working directory (pwd) to the
- 5th line - Linking object files with shared library ("[-L](https://www.rapidtables.com/code/linux/gcc/gcc-l.html)"), "-llvt" means that compiler GNU GCC have to search such kinds of files (on UNIX/Linux OS): liblvt.a (static library) or liblvt.so (dynamic library)
- 6th line - Adding new path to environment variable "[LD_LIBRARY_PATH](https://linuxhint.com/what-is-ld-library-path/)" and running executive file, at the same time it is not necessary that executive file must have ".out" extension.
