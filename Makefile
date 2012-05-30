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
CF=-O3 -fPIC
MODULES=CharacterMap.o D2VTranslator.o Halt.o Matrix.o Terminal.o TerminalRenderer.o TerminalSurface.o TFShader.o TProgram.o TVShader.o
HI=-I./include
LIBS=-lGLEW -lGL

all: libHALT.so

libHALT.so: $(MODULES)
	$(CC) $(LIBS) -shared $(MODULES) -o libHALT.so

CharacterMap.o:
	$(CC) $(HI) $(CF) -c src/CharacterMap.cpp

D2VTranslator.o:
	$(CC) $(HI) $(CF) -c src/D2VTranslator.cpp
	
Halt.o:
	$(CC) $(HI) $(CF) -c src/Halt.cpp

Matrix.o:
	$(CC) $(HI) $(CF) -c src/Matrix.cpp

Terminal.o:
	$(CC) $(HI) $(CF) -c src/Terminal.cpp

TerminalRenderer.o:
	$(CC) $(HI) $(CF) -c src/TerminalRenderer.cpp

TerminalSurface.o:
	$(CC) $(HI) $(CF) -c src/TerminalSurface.cpp

TFShader.o:
	$(CC) $(HI) $(CF) -c src/TFShader.cpp

TProgram.o:
	$(CC) $(HI) $(CF) -c src/TProgram.cpp

TVShader.o:
	$(CC) $(HI) $(CF) -c src/TVShader.cpp

install:
	cp libHALT.so /usr/lib
	mkdir /usr/include/HALT
	cp ./include/* /usr/include/HALT

uninstall:
	rm /usr/lib/libHALT.so
	rm -rf /usr/include/HALT

reinstall: uninstall install

clean:
	rm -f *.o
	rm -f libHALT.so


