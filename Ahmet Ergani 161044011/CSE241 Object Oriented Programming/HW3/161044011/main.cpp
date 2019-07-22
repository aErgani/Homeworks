#include <iostream>
#include <fstream>
#include <vector>
#include "ConnectFour.h"

//sadly I couldn't manage to implement the compare function for multi-game. Hope the score-decrease won't be massive
int main()
{
    int objectNo;
    char MS;
    ConnectFour GAME1,GAME2,GAME3,GAME4,GAME5;          //declaring objects
    cout << "select game type" << endl;
    cin >> MS;
    if(MS == 'S')
    {
        GAME1.setDontPlay(0);                           //dontPlay holds the value 1 or 2 during multi-game so we need to assign a different value than these
        GAME1.playGame();
        return 0;
    }
    else if(MS == 'M')
    {
        GAME1.setDontPlay(1);                           //dontPlay should be 1 during init part
        GAME2.setDontPlay(1);
        GAME3.setDontPlay(1);
        GAME4.setDontPlay(1);
        GAME5.setDontPlay(1);
        GAME1.playGame();                               //after each initialization we assign dontPlay 2
        cout << "Object 1 initialized" << endl;
        GAME1.setDontPlay(2);
        GAME2.playGame();
        cout << "Object 2 initialized" << endl;
        GAME2.setDontPlay(2);
        GAME3.playGame();
        cout << "Object 3 initialized" << endl;
        GAME3.setDontPlay(2);
        GAME4.playGame();
        cout << "Object 4 initialized" << endl;
        GAME4.setDontPlay(2);
        GAME5.playGame();
        cout << "Object 5 initialized" << endl;
        GAME5.setDontPlay(2);
        while(GAME1.getGameFinish() != 1 ||             //this loop breaks when all the games are finished
              GAME2.getGameFinish() != 1 ||
              GAME3.getGameFinish() != 1 ||
              GAME4.getGameFinish() != 1 ||
              GAME5.getGameFinish() != 1)
        {
            cout << "select object" << endl;
            cin >> objectNo;
            while(objectNo < 1 || objectNo > 5)
            {
                cout << "invalid input" << endl;
                cin >> objectNo;
            }
            switch(objectNo)                            //this switch let us play the object we desire
            {
                case 1:
                    if(GAME1.getGameFinish() == 1)
                    {
                        cout << "this object is a finished game select another object" << endl;
                        break;
                    }
                    GAME1.playGame();
                    break;
                case 2:
                    if(GAME2.getGameFinish() == 1)
                    {
                        cout << "this object is a finished game select another object" << endl;
                        break;
                    }
                    GAME2.playGame();
                    break;
                case 3:
                    if(GAME3.getGameFinish() == 1)
                    {
                        cout << "this object is a finished game select another object" << endl;
                        break;
                    }
                    GAME3.playGame();
                    break;
                case 4:
                    if(GAME4.getGameFinish() == 1)
                    {
                        cout << "this object is a finished game select another object" << endl;
                        break;
                    }
                    GAME4.playGame();
                    break;
                case 5:
                    if(GAME5.getGameFinish() == 1)
                    {
                        cout << "this object is a finished game select another object" << endl;
                        break;
                    }
                    GAME5.playGame();
                    break;
                default:
                    break;
            }
        }

    }
        return 0;
}