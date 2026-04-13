main: build/main.o build/test.o
	g++ build/main.o build/test.o -o main

build/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

build/test.o: src/test.cpp
	g++ -c src/test.cpp -o build/test.o