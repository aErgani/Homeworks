//
// Created by ahmet on 17-Oct-17.
//
#include <iostream>
#include <vector>
#ifndef HW3_CONNECTFOUR_H
#define HW3_CONNECTFOUR_H

using namespace std;


class ConnectFour
{
private:
    static int livingCell;
    int height;
    int width;
    int currentX;
    int currentY;
    int dontPlay;
    int gameFinish;
    char XorO;
    char column;
    char winDirection;
    char playType;
    string command;
    string filename;
    class Cell
    {
    private:
        int column;
        int row;
        char value;
    public:
        char getValue() const;
        void setValue(char V);
        int getColumn() const;
        void setColumn(int C);
        int getRow() const;
        void setRow(int R);
        Cell();
    };
    vector< vector<Cell> > gameCells;

    int play();
    int undoPlay();
    int save();
    int load();
    int initBoard();
    int printBoard();
    int horizontal();
    int vertical();
    int firstAngleBisector();
    int secondAngleBisector();
    int lowerCase();
    int winCheck();
    int MrOmnipotent();

    static int getLivingCell()
    {
        return livingCell;
    }

    static void increaseLivingCell()
    {
        livingCell++;
    }

    static void decreaseLivingCell()
    {
        livingCell--;
    }

    void setHeight(int h);

    int getHeight() const;

    int getWidth() const;

    void setWidth(int w);

    void setXorO(char XO);

    void setColumn(char C);

    char getWinDirecton() const;

    void setWinDirection(char W);

    void setGameFinish(int g);

public:
    ConnectFour();
    ConnectFour(int a);
    int getGameFinish() const;
    int playGame();
    void setDontPlay(int d);

};


#endif //HW3_CONNECTFOUR_H
