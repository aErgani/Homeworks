//
// Created by ahmte on 24-Nov-17.
//
#include <iostream>
#include "Cell.h"
#ifndef HW5_CONNECTFOURABSTRACT_H
#define HW5_CONNECTFOURABSTRACT_H

using namespace std;

class ConnectFourAbstract
{
protected:
    static int livingCell;
    int height;
    int width;
    int currentX;
    int currentY;
    int totalDot = 0;
    char XorO;
    char column;
    char winDirection;
    char playType;
    string command;             /*this is used to hold playType (PvP or PvAI) and the column*/
    string filename;
    Cell ** board;              /*our board array*/
    virtual int initBoard() = 0;//initializes the board
    virtual int play() = 0;
    int undoPlay();             /*erases the last move on the given column*/
    virtual int save() = 0;
    virtual int load() = 0;
    int printBoard();
    virtual int winCheck() = 0; //checks if anybod won the game or not
    int lowerCase();            //lowers the cases of the characters if a player has won
    int MrOmnipotent();         //AI
    ConnectFourAbstract& operator=(ConnectFourAbstract const& other);
    static void increaseLivingCell() {livingCell++;}
    static void decreaseLivingCell() {livingCell--;}
    static int getLivingCell() {return livingCell;}

public:
    ConnectFourAbstract():height(5),width(5){}
    ConnectFourAbstract(int h,int w):height(h),width(w){}
    virtual ~ConnectFourAbstract();
    ConnectFourAbstract(ConnectFourAbstract const& other );
    virtual int playGame() = 0;     //Plays the game
};



#endif //HW5_CONNECTFOURABSTRACT_H
