# Getting Started

## Introduction

radicalite is a library written in C for elemental Fractions, Radicals, and Polynomials.

## Getting the Source Code

Make sure you have [git](https://git-scm.com/) installed. If not, you can download it from the official website or use a package manager.

Then execute the following command:

    git clone https://codeberg.org/maxchen32/radicalite.git

to get the source code,

    cd radicalite

to enter the source code directory.

## Compilation

Make sure you have GCC installed. If not, Windows users are recommended to use [this precompiled GCC](https://winlibs.com/), and Linux users can install it through the distribution's package manager.

It is recommended to use **[xmake](https://xmake.io/#/)**, but we also provide support for **[CMake](https://cmake.org/)**.

### xmake:

```bash
xmake f --m release
xmake
```

If you are using MinGW on windows, the first line should be written as:

	xmake f --m release --toolchain=mingw

If you want to install into the system (default is `/usr/local/lib`):

```bash
xmake install --admin
```

If you want to compile the example program:
```bash
xmake -a
```

### CMake:

```bash
mkdir build
cd build 
cmake ..
cmake --build .
```

If you want to install into the system (default is `/usr/local/lib`):

```bash
sudo cmake --install .
```

## Writing the Program

In this tutorial, we will write a program that calculates the product of $\frac{1}{2}\sqrt{3}$ and $\frac{4}{5}\sqrt{6}$ .

Create a file named `test.c` and open it.

## Include Header Files

Write the following code:

```C
#include <stdio.h>
#include "radical.h"
```

## Program Body

Initialize a variable a of type Radical to $\frac{1}{2}\sqrt{3}$ .

```C
Radical a = initRad(1, 2, 3);
```

The three parameters of `initRad(1, 2, 3)` represent the numerator, denominator, and radicand.

Declare another variable `b` :

```C
Radical a = initRad(1, 2, 3);
Radical b = initRad(4, 5, 6);
```

Calculate the product of `a` and `b` and assign it to `c` :

```C
Radical c = mulRad(a, b);
```

Output c and a newline character to the console:

```C
printRad(c);
putchar('\n');
```

`printRad(c)` prints a variable of type Radical to the console, but does **not** add a newline.

### Complete Program:

```C
#include <stdio.h>
#include "radical.h"

int main() {
    Radical a = initRad(1, 2, 3);
    Radical b = initRad(4, 5, 6);
    Radical c = mulRad(a, b);
    printRad(c);
    putchar('\n');
    return 0;
}
```

## Compile and Run the Test Program

If you have already installed the library, it's very simple:

```bash
gcc test.c -o test -lradical -lm
./test
```

If you are using MinGW on Windows:

```batch
gcc test.c -o test.exe -Ipath\to\radicalite\include -Lpath\to\radicalite\build\windows\x64\release -lradical
test.exe
```

I don't have experience with MSVC at the moment, so I can't provide the corresponding method.

### Output

If everything goes well, it should output:

	(6/5)√(2)

which is the correct result.