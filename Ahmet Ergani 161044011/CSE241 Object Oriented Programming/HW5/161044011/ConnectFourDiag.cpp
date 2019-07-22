//
// Created by ahmte on 24-Nov-17.
//

#include "ConnectFourDiag.h"
#include <fstream>

int ConnectFourDiag::initBoard()        //same as ConnectFourPlus
{
    board = new Cell *[height];
    for (int i = 0; i < height; i++)
        board[i] = new Cell[width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; ++j)
        {
            board[i][j].setRow(i);
            board[i][j].setColumn(j);
        }
    totalDot = height * width;
    return 1;
}

int ConnectFourDiag::play()
{
    int a = column - 'A';						//a will be our X coordinate
    for (int i = 0; i < height; ++i)			//starting from the bottom we search for a '.'
        if(board[i][a].getValue() == '.')
        {
            increaseLivingCell();				//we make the arrangements if we found one and return 1
            board[i][a].setValue(XorO);
            currentX = a;
            currentY = i;
            return 1;							//if there is none we return 0.that means the column is full
        }
    return 0;
}

int ConnectFourDiag::save()
{
    ofstream save;                                      //"save" is our ofstream
    save.open(filename);                                //opening the file
    save << height << endl;                             //height, width and livingcell are at the top of the savefile
    save << width << endl;
    if (save.is_open())                                 //checking if it's opened or not just in case of an error
    {
        for (int i = 0; i < height; i++)                //writing the board to the file
        {
            for (int j = 0; j < width; j++)
            {
                if(board[i][j].getValue() == ' ')
                    save << 'E' << endl;
                else
                    save << board[i][j].getValue() << endl;
            }
        }
    }
    else cerr << "FILE OPEN ERROR";                     //if program fails to open the file
    save.close();                                       //closing the file
    return 1;
}

int ConnectFourDiag::load()
{
    int hw = 0;                                        //hwl temporarily holds height and width
    char val;                                           //value temporarily hold value
    ifstream load;                                      //load is our ifstream
    load.open(filename);                                //opening the file
    while(getLivingCell() > 0)                          //making our livingCell 0
        decreaseLivingCell();
    for (int i = 1; i < height; ++i)
        delete [] board[i];
    //delete [] board;
    load >> hw;                                        //reading height, width
    height = hw;
    load >> hw;
    width = hw;
    initBoard();                                        //initializing the new vector
    if (load.is_open())
    {
        for (int i = 0; i < height; i++)                //reading and rearranging the board
        {
            for (int j = 0; j < width; j++)
            {
                load >> val;
                if(val == 'E')
                    board[i][j].setValue(' ');
                else
                    board[i][j].setValue(val);
                if(val == 'X' || val == 'O')
                    increaseLivingCell();
            }
        }
    }
    else cerr << "FILE OPEN ERROR";                     //if program fails to open the file
    load.close();                                       //closing the file
    printBoard();
    return 1;
}

int ConnectFourDiag::firstAngleBisector()
{
    int fab = 0;
    for(int i = 1;i < 4;i++)
    {
        if(currentY == height - 1)                                  //checking if the location is in the boundaries or not
            break;
        if(XorO == board[currentY + i][currentX + i].getValue())    //checking the up right neighbours
            fab++;
        else
            break;
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentY - i < 0 || currentX - i < 0)                    //checking if the location is in the boundaries or not
            break;
        if(XorO == board[currentY - i][currentX - i].getValue())    //checking the down left neighbours
            fab++;
        else
            break;
    }
    return fab;
}
int ConnectFourDiag::secondAngleBisector()
{
    int sab = 0;
    for(int i = 1;i < 4;i++)
    {
        if(currentX - i < 0 || currentY == height - 1)              //checking if the location is in the boundaries or not
            break;
        if(XorO == board[currentY + i][currentX - i].getValue())    //checking the up left neighbours
            sab++;
        else
            break;
    }
    for(int i = 1;i < 4;i++)
    {
        if(currentY - i < 0)                                        //checking if the location is in the boundaries or not
            break;
        if(XorO == board[currentY - i][currentX + i].getValue())    //checking the down right neighbours
            sab++;
        else
            break;
    }
    return sab;
}
int ConnectFourDiag::winCheck()
{
    int  fab = 0,sab = 0;
    fab = firstAngleBisector();                       //how? by checking the return values of these 2 function
    sab = secondAngleBisector();
    if(fab >= 3)
    {
        winDirection = 'f';
        return 1;
    }
    if(sab >= 3)
    {
        winDirection = 's';
        return 1;
    }
    return 0;
}

int ConnectFourDiag::playGame()
{
    char inputPlayType;                             //playType is meant to hold the values 'c' 'C' 'p' and 'P'
    int inputHeight, inputWidth;                    //inputHeight will be used to set height inputWidth will be used to set witdh
    cout << "Enter Height" << endl;             //asking the height and width from the user
    cin >> inputHeight;
    cout << "Enter Width" << endl;
    cin >> inputWidth;
    height = inputHeight;                       //setting part
    width = inputWidth;
    cout << "Initializing Board" << endl;
    initBoard();
    printBoard();                               //printing the first initial empty board
    cout << "Here is your Board" << endl;
    cout << "Type 'P' if you want to play PvP. Type 'C' if you want to play against Mr. Omnipotent "
         << endl;                               //asking for playType
    cin >> inputPlayType;
    while (1)                                   //checking if the input is valid or not
    {
        if (inputPlayType != 'P' && inputPlayType != 'p' && inputPlayType != 'C' && inputPlayType != 'c')
        {
            cerr << "invalid input try something else" << endl;
            cin >> inputPlayType;
        } else
        {
            playType = inputPlayType;
            break;
        }
    }
    if (playType == 'P' || playType == 'p')
    {
        while (1)
        {
            XorO = 'X';
            cout << "Select a column player 1 , You may also LOAD or SAVE" << endl;
            cin >> command;
            while (1)                                                                    //This whole loop is for the move of player 1
            {
                while (1)                                                                //checking if the input is valid or not
                {
                    if (command != "LOAD" && command != "SAVE" && command.length() > 1)
                    {
                        cerr << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                if (command == "SAVE")                                                  //SAVE section
                {
                    cout << "enter file name player 1" << endl;                         //asking for a filename
                    cin >> filename;
                    save();                                                             //calling the save function
                    cout << "select a column player 1" << endl;
                    cin >> command;                                                     //since saving or loading is not a "move" we need to ask for a column this time
                }else if (command == "LOAD")                                             //same algorithm as SAVE
                {
                    cout << "enter file name player 1" << endl;
                    cin >> filename;
                    load();
                    cout << "select a column player 1" << endl;
                    cin >> command;
                }
                while (1)                                                               //checking if the input is valid or not
                {
                    if (command.length() > 1)
                    {
                        cerr << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                column = command[0];                                                    //this will be the column where wthe player will accomplish his MOVE
                if (play() == 1)
                {
                    break;                                                              //breaks after a succesfull play()
                } else if (play() == 0)                                                   //Checking if that column is full or empty
                {
                    cerr << "that column is full try something else player 1"
                         << endl;  //asking another column if that one is full
                    cin >> command;
                }
            }
            if (winCheck())                                                             //Checking for WIN after each "move"
            {
                lowerCase();                                                            //calling lowerCase function, printing the board and informing the users after one of them has won
                printBoard();
                cout << "YOU WON PLAYER 1" << endl;
                return 1;
            }
            else
            {
                printBoard();
                cout << "total dot is " << totalDot << " full cell is " << getLivingCell() << endl;
                if(totalDot == getLivingCell())										  //If there is no "win" situation we check for "draw" situation
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
            }

            XorO = 'O';                                                               //getting ready for player 2, setting XorO
            cout << "Select a column player 2 , You may also LOAD or SAVE" << endl;
            cin >> command;
            while (1)                                                                   //everything is same as the while loop above except this time it's player 2
            {
                while (1)       //checking if the input is valid or not
                {
                    if (command != "LOAD" && command != "SAVE" && command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                if (command == "SAVE")                                          //SAVE section
                {
                    cout << "enter file name player 2" << endl;
                    cin >> filename;
                    save();
                    cout << "select a column player 2" << endl;
                    cin
                            >> command;
                }else if (command == "LOAD")                                   //LOAD section
                {
                    cout << "enter file name player 2" << endl;
                    cin >> filename;
                    load();
                    cout << "select a column player 2" << endl;
                    cin >> command;
                }
                while (1)       //checking if the input is valid or not         //input validation check
                {
                    if (command.length() > 1)
                    {
                        cerr << "invalid input try something else player 2" << endl;
                        cin >> command;
                    } else
                        break;
                }
                column = command[0];                                          //play() part
                if (play() == 1)
                    break;
                else if (play() == 0)
                {
                    cerr << "that column is full try something else player 2" << endl;
                    cin >> command;
                }
            }
            if (winCheck())                                 //Checking for WIN after each "move"
            {
                lowerCase();
                printBoard();
                cout << "YOU WON PLAYER 2" << endl;
                return 1;
            }
            else
            {
                printBoard();
                cout << "total dot is " << totalDot << " full cell is " << getLivingCell() << endl;
                if(totalDot == getLivingCell())								//If there is no "win" situation we check for "draw" situation
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
            }
        }
    }
    if(playType == 'C' || playType == 'c')                                               //This if statement is for the brave ones who challenge Mr Omnipotent
        while(1)
        {
            XorO = 'X';
            cout << "Select a column player 1 , You may also LOAD or SAVE" << endl;
            cin >> command;
            while (1)
            {
                while (1)       //checking if the input is valid or not
                {
                    if (command != "LOAD" && command != "SAVE" && command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                if (command == "SAVE")                                          //SAVE section
                {
                    cout << "enter file name player 1" << endl;
                    cin >> filename;
                    save();
                    cout << "select a column player 1" << endl;
                    cin
                            >> command;
                } else if (command == "LOAD")                                   //LOAD section
                {
                    cout << "enter file name player 1" << endl;
                    cin >> filename;
                    load();
                    cout << "select a column player 1" << endl;
                    cin >> command;
                }
                while (1)                                                       //checking input validation
                {
                    if (command.length() > 1)
                    {
                        cout << "invalid input try something else player 1" << endl;
                        cin >> command;
                    } else
                        break;
                }
                column = command[0];
                if (play() == 1)                                                //play() part
                    break;
                else if (play() == 0)
                {
                    cerr << "that column is full try something else player 1" << endl;
                    cin >> command;
                }
            }
            if (winCheck())                                                     //Checking for WIN after each "move"
            {
                lowerCase();
                printBoard();
                cout << "YOU WON PLAYER 1" << endl;
                return 1;
            }
            else
            {
                printBoard();
                if(totalDot == getLivingCell())								//If there is no "win" situation we check for "draw" situation
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
            }
            MrOmnipotent();                                                     //after the player make his move calling the function MrOmnipotent()
            if (winCheck())                                                     //After his glorious victory,this part informs the user that he couldn't escaped the inevitable
            {
                lowerCase();
                printBoard();
                cout << "MR OMNIPOTENT WON AS EXPECTED" << endl;
                return 1;
            }
            else
            {
                printBoard();
                if(totalDot == getLivingCell())									//If there is no "win" situation we check for "draw" situation
                {
                    cout << "DRAW" << endl;
                    return 1;
                }
            }
        }
    return 0;
}