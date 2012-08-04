# HALT

Hardware accelerated terminal implementation written in C++ and OpenGL.

## Installation

### Windows

HALT has a dependency on the OpenGL Extension Wrangler Library. You must
download it from [here](http://glew.sourceforge.net/) and compile it on your
own.

#### Visual Studio

Clone the repository into a folder:

    >git clone git://github.com/jcmoyer/HALT.git

Then, in Visual Studio, create a new project from source. Select the HALT
directory. You need to configure your build settings so that Visual Studio
builds either a static library or DLL (consult your documentation). Then, link
in `OpenGL32.lib` and `glew32.lib`. Build normally.

The examples have an additional dependency on SDL 1.2. They can be built by
linking `SDL.lib` and `Halt.lib` (default).

### Linux

#### Debian/Ubuntu

First, download the required dependencies. These are required to build HALT in
one way or another:

    $ sudo apt-get install build-essential libglew-dev libgl1-mesa-dev git

Then, clone the repository:

    $ git clone git://github.com/jcmoyer/HALT.git

You can now build HALT.

    $ cd HALT/
    $ make && sudo make install

To build the examples (optional):

    $ sudo apt-get install libsdl-dev
    $ cd examples/ && make

## Usage

TODO. For now, see examples.

## License (MIT)

Copyright (c) 2011-2012 J.C. Moyer

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
