build:
	g++ -std=c++20 -O2 -Wall main.cpp

run:
	./a.out

test:
	time cat in.txt | ./a.out > out.txt
