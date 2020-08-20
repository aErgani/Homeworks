all: program clean

program: sortArrays.o memory.o
	g++ sortArrays.o memory.o -o sortArrays -lpthread


sortArrays.o:
	g++ -c sortArrays.cpp

memory.o:
	g++ -c memory.cpp


clean:
	rm *.o 