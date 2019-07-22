all: hello

hello: main.o hello.o
	g++ main.o hello.o -o exe

main.o: main.cpp
	g++ -c main.cpp

hello.o: hello.cpp
	g++ -c hello.cpp

clean:
	rm *.o exe
