source = ./src
binary = ./bin

all:
	gcc $(source)/*.c -lSDL2 -lGLEW -lGL -o $(binary)/test

run: all
	./bin/test