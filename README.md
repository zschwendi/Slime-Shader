# Slime Shader

A C++ image renderer with two effects: RainbowWave and RainbowGoop.
RainbowGoop calls RainbowWave, then bends a copy of its colors.

## Build and run

The C++ program needs a C++11 compiler and make.

```sh
make
./slime
```

The program asks for width, height, time in seconds, and effect.
Dimensions must be from 1 to 2048. Time selects a frame; it does not make the
program wait. Density is 4.0 and speed is 0.25, matching the original preview.
It renders a frame and prints every pixel's row, column, and RGB values. The preview below
displays the whole frame as an animation. File export is not part of this version.

```sh
make clean
```

## Required C++ feature

`Image` uses `std::vector<int>` to own the RGB pixel data. `SlimeShader` inherits
from `Image` and fills or transforms those pixels through its rendering methods.
The program also uses references in the `Image` interface, loops, and terminal
input/output through `std::cin` and `std::cout`. Each class has its own header
and implementation file; `main.cpp` constructs the shader and calls its methods.

## Optional Animated Swift preview

The preview is a separate macOS application with its own Makefile:

```sh
cd Preview
make
make run
```

Quit the existing preview before running a newly built version.
Use the RainbowWave / RainbowGoop control to switch effects while it runs.
The C++ terminal program does not build or link any preview files.
