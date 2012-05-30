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
