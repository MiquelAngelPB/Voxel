
all:
	gcc ./src/main.c -lSDL2 -lGL -o ./bin/test

run: all
	./bin/test