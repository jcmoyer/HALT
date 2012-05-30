# ============================================================================
# Copyright (c) 2011-2012 J.C. Moyer
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
# ============================================================================

CC=g++
CF=-g -O0 -fno-inline

UTILITY_INCLUDE=-I./utilities
UTILITY_MODULES=Imaging.o Platform.o stb_image.o

LIBS=-lSDL -lGL -lHALT

all: HelloWorld.o

HelloWorld.o: $(UTILITY_MODULES)
	$(CC) $(LIBS) $(CF) HelloWorld.cpp $(UTILITY_MODULES) -o HelloWorld

Imaging.o:
	$(CC) $(UTILITY_INCLUDE) $(CF) -c utilities/Imaging.cpp

Platform.o:
	$(CC) $(UTILITY_INCLUDE) $(CF) -c utilities/Platform.cpp

stb_image.o:
	$(CC) $(UTILITY_INCLUDE) $(CF) -c utilities/stb_image.c

clean:
	rm -f *.o
	rm -f HelloWorld
