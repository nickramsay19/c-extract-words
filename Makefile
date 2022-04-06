default: main

main: bin build/main.o
	gcc -o bin/main build/main.o

build/main.o: build src/main.c
	gcc -o build/main.o -c src/main.c

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm bin/main
	rm build/*