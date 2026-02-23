cFlags=  -lSDL2 -lGLEW -lGL -lm -I$(include)
include = ./include
source = ./src
binary = ./bin

all:
	gcc $(source)/*.c $(cFlags) -o $(binary)/test

run: all
	./bin/test