//
// Created by ahmte on 24-Nov-17.
//

#include "ConnectFourAbstract.h"
#include <fstream>

int ConnectFourAbstract::livingCell = 0;

int ConnectFourAbstract::printBoard()
{
    auto A = 'A';								//this is for the index line (A B C D E F ...)
    for (int i = width; i > 0; --i)
    {
        cout << A << " ";
        A++;
    }
    cout << endl;
    for (int i = height - 1; i >= 0; --i)	//and this is the double loop that prints our board
    {
        for (int j = 0; j < width; ++j)
            cout << board[i][j].getValue() << " ";
        cout << endl;
    }
}

int ConnectFourAbstract::undoPlay()         //this function starts checking from the top and replaces the first X or O it encounters with a dot
{
    int a = column - 'A';
    for (int i = height - 1; i >= 0 ; --i)
        if(board[i][a].getValue() == 'X' || board[i][a].getValue() == 'O')
        {
            board[i][a].setValue('.');
            decreaseLivingCell();
            return 1;
        }
}



int ConnectFourAbstract::MrOmnipotent()
{
    int random = rand();                        //this random int will help us move randomly
    XorO = 'O';
    for(int i = 0; i < width ; i++)             //first Mr Omnipotent checks every column to see if he has a chance to win
    {
        column = 'A' + i;                     //it simultaneously calls the functions play() and undoPlay()
        if(play())
        {
            if (winCheck())
                return 1;                           //it simply returns 1 if he can win since he already played
            undoPlay();
        }
    }
    XorO = 'X';                               //if  he canot win he will check if you are gonna win and if you are, he will prevent you
    for(int i = 0; i < width ; i++)
    {
        column = 'A' + i;                     //similar algorithm with the loop above only
        if (play())
        {
            if (winCheck())
            {
                undoPlay();                         //he calls undoPlay() sets XorO to his value then call play() again
                XorO = 'O';
                play();
                return 2;
            }
            undoPlay();
        }
    }
    XorO = 'O';                               //if no one is going to win, he plays randomly
    random = random % width;
    column = 'A' + random;
    play();
    return 0;
}

ConnectFourAbstract& ConnectFourAbstract::operator=(ConnectFourAbstract const& other)
{
    for (int i = 1; i < height; ++i)					//first we delete the board
        delete [] board[i];
    delete [] board;
    height = other.height;								//then assign this object's variables with the other object's variables
    width = other.width;
    initBoard();										//then initialize the board again
    for (int i = 0; i < height; i++)					//copying the other object's board
        for (int j = 0; j < width; ++j)
        {
            board[i][j] = other.board[i][j];
        }
    column = other.column;
    return *this;
}

ConnectFourAbstract::ConnectFourAbstract(ConnectFourAbstract const& other)
{
    *this = other;
}

int ConnectFourAbstract::lowerCase()
{
    char lower = 'a' - 'A';                                             //this char will allow us to accomplish this operation
    board[currentY][currentX].setValue(XorO + lower);                   //converting the case of the winning cell
    if(winDirection == 'h')                                             //according to  which direction the player won,we will enter one of those 4 if statements and scan the neighbours like the functions above[horizontal() vertical() firstAngleBisector() secondAngleBisector()]
    {                                                                   //horizontal() direction
        for(int i = 1;i < 4;i++)
        {
            if(XorO == board[currentY][currentX + i].getValue())
                board[currentY][currentX + i].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentX - i < 0)
                break;
            if(XorO == board[currentY][currentX - i].getValue())
                board[currentY][currentX - i].setValue(XorO + lower);
            else
                break;
        }
    }
    if(winDirection == 'v')
    {                                                                   //vertical() direction
        for(int i = 1;i < 4;i++)
        {
            if(XorO == board[currentY + i][currentX].getValue())
                board[currentY + i][currentX].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0)
                break;
            if(XorO == board[currentY - i][currentX].getValue())
                board[currentY - i][currentX].setValue(XorO + lower);
            else
                break;
        }
    }
    if(winDirection == 'f')
    {                                                                   //firstAngleBisector() direction
        for(int i = 1;i < 4;i++)
        {
            if(XorO == board[currentY + i][currentX + i].getValue())
                board[currentY + i][currentX + i].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0 || currentX - i < 0)
                break;
            if(XorO == board[currentY - i][currentX - i].getValue())
                board[currentY - i][currentX - i].setValue(XorO + lower);
            else
                break;
        }
    }
    if(winDirection == 's')
    {                                                                   //secondAngleBisector() direction
        for(int i = 1;i < 4;i++)
        {
            if(currentX - i < 0)
                break;
            if(XorO == board[currentY + i][currentX - i].getValue())
                board[currentY + i][currentX - i].setValue(XorO + lower);
            else
                break;
        }
        for(int i = 1;i < 4;i++)
        {
            if(currentY - i < 0)
            {
                break;
            }
            if(XorO == board[currentY - i][currentX + i].getValue())
                board[currentY - i][currentX + i].setValue(XorO + lower);
            else
                break;
        }
    }
    return 1;
}

ConnectFourAbstract::~ConnectFourAbstract()
{
    for (int i = 1; i < height; i++)
        delete[] board[i];
    //delete[] board;
}

