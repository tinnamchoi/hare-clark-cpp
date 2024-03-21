.PHONY: build

build:
	cmake -B build
	cmake --build build

run:
	./build/example

run-tests:
	cat tests/in.txt | ./build/example | head -n 1000 > tests/out.txt

clean:
	rm -rf build
