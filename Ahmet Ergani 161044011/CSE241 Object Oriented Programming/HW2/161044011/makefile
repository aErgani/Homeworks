all: MAJOR

MAJOR: main.o 
	g++ main.o -o MAJOR 

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o MAJOR