all: exe


exe: main.o Cell.o ConnectFourAbstract.o ConnectFourDiag.o ConnectFourPlus.o ConnectFourPlusUndo.o
	g++ main.o Cell.o ConnectFourAbstract.o ConnectFourDiag.o ConnectFourPlus.o ConnectFourPlusUndo.o  -o exe
	rm *.o

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

ConnectFourAbstract.o: ConnectFourAbstract.cpp
	g++ -std=c++11 -c ConnectFourAbstract.cpp

ConnectFourDiag.o: ConnectFourDiag.cpp
	g++ -std=c++11 -c ConnectFourDiag.cpp

ConnectFourPlus.o: ConnectFourPlus.cpp
	g++ -std=c++11 -c ConnectFourPlus.cpp

ConnectFourPlusUndo.o: ConnectFourPlusUndo.cpp
	g++ -std=c++11 -c ConnectFourPlusUndo.cpp

Cell.o: Cell.cpp
	g++ -std=c++11 -c Cell.cpp

clean:
	rm *.o exe