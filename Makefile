build:
	clear
	cmake -G "Unix Makefiles" -S . -B ./bin/
	cmake --build ./bin/ -- -s

run: build
	./bin/voxel

clean:
	rm -rf ./bin/