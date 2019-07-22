#include <iostream>
#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"
#include "ConnectFourDiag.h"

int main()
{
    string input;               //to decide which type of game user wants to play
    ConnectFourPlus* Plus;
    ConnectFourPlusUndo* PlusUndo;
    ConnectFourDiag* Diag;
    cout << "type P if you want to play ConnectFour Plus" << endl
         << "type D if you want to play ConnectFour Diag" << endl
         << "type U if you want to play Connectfour PlusUndo" << endl;
    cin >> input;
    if(input.length() > 1 || input[0] != 'P' && input[0] != 'D' && input[0] != 'U')     //error check
        while(input.length() > 1 || input[0] != 'P' && input[0] != 'D' && input[0] != 'U')
        {
            cerr << "invalid input. try again" << endl;
            cin >> input;
        }
    if(input[0] == 'P')
    {
        Plus = new (ConnectFourPlus);
        Plus->playGame();
    }
    else if(input[0] == 'D')
    {
        Diag = new (ConnectFourDiag);
        Diag->playGame();
    }
    else if(input[0] == 'U')
    {
        PlusUndo = new (ConnectFourPlusUndo);
        PlusUndo->playGame();
    }
    return 0;
}