#include <iostream>
#include "ConnectFour.h"

using namespace std;

int main()
{
    int objectNo;
    char MS;
    string file;
    cout << "select game type" << endl;
    cin >> MS;								//M for multiPlayer game S for singlePlayer game
	while(true)
	{
		if(MS != 'S' && MS != 'M')
		{
			cerr << "invalid input. type M or S" << endl;
			cin >> MS; 
		}
		else
		break;
	}
    if(MS == 'S')
    {
	cout << "enter filename" << endl;
    	cin >> file;
    	ConnectFour GAME1(file);
        GAME1.setDontPlay(0);                           //dontPlay holds the value 1 or 2 during multi-game so we need to assign a different value than these
        GAME1.playGame();
        //return 0;
    }
    else if(MS == 'M')
    {
        multiplayer(file);				//this function is called for multiplayer game
    }
    return 0;
}

