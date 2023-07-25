# radicalite

Hopefully a better version of maxchen32/radical.

## 介绍 Intruductions

C语言编写的基础分数、二次根式和多项式类库。  
Elemental Fractions, Radicals and Polynomials.

## 编译 Compile

建议使用 **[xmake](https://xmake.io/#/)** ，但是我们也提供 **[CMake](https://cmake.org/)** 支持。  
It is recommended to use **[xmake](https://xmake.io/#/)**, but we also provide **[CMake](https://cmake.org/)** support.

### xmake:  
```bash
xmake f --m release
xmake
```

如果你想要安装到系统的话（默认 `/usr/local/lib` ）：  
If you want to install into the system (default is `/usr/local/lib` ):  
```bash
xmake install --admin
```

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

[fraction.h](include/fraction.h)

[radical.h](include/radical.h)