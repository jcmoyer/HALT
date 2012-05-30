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


