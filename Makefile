.PHONY: build

build:
	cmake -B build
	cmake --build build

run:
	./build/hare-clark

run-tests:
	time cat tests/in.txt | ./build/hare-clark > tests/out.txt

clean:
	rm -r build
