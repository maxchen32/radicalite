# radicalite

Hopefully a better version of maxchen32/radical.

## 介绍 Intruductions

C语言编写的基础分数、二次根式和多项式类库。  
radicalite is a library written in C for elemental Fractions, Radicals, and Polynomials.

## 编译 Compilation

确保你安装了GCC，如果没有的话，Windows用户建议使用[这个编译好的GCC](https://winlibs.com/)，Linux用户请通过所用发行版的包管理器安装。  
Make sure you have GCC installed. If not, Windows users are recommended to use [this precompiled GCC](https://winlibs.com/), and Linux users can install it through the distribution's package manager.

建议使用 **[xmake](https://xmake.io/#/)** ，但是我们也提供 **[CMake](https://cmake.org/)** 支持。  
It is recommended to use **[xmake](https://xmake.io/#/)**, but we also provide support for **[CMake](https://cmake.org/)**.

### xmake:  

```bash
xmake f --m release
xmake
```

如果你在windows上使用MinGW，第一行得写成：  
If you are using MinGW on windows, the first line should be written as:

	xmake f --m release --toolchain=mingw

如果你想要安装到系统的话（默认 `/usr/local/lib` ）：  
If you want to install into the system (default is `/usr/local/lib` ):  
```bash
xmake install --admin
```

如果你想要编译示例程序的话：  
If you want to compile the example program:

	xmake -a

### CMake:  
```bash
mkdir build
cd build 
cmake ..
cmake --build .
```

如果你想要安装到系统的话（默认 `/usr/local/lib` ）：  
If you want to install into the system (default is `/usr/local/lib` ):  
```bash
sudo cmake --install .
```

## Usage

[入门](docs/入门.md)  
[Getting Started](docs/getting_started.md)

正在编写更多的文档，敬请期待......  
Please stay tuned for more documentation.

或者你可以先看看头文件：  
Or you can take a look at the header file first:  

[fraction.h](include/fraction.h)

[radical.h](include/radical.h)