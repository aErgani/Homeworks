//
// Created by ahmet on 05-Nov-17.
//
#include <iostream>
#ifndef HW4_CONNECTFOUR_H
#define HW4_CONNECTFOUR_H

using namespace std;
void multiplayer(string file);
class ConnectFour
{
private:
    static int livingCell;                  //this holds currently occupied cells
    int height;                             //our height and width value
    int width;
    int currentX;                           //this two values hold the last coordinates
    int currentY;
    int dontPlay;                           //for multiplayer,because sometimes we only need to initialize but sometimes need to play a whole game,this is our flag
    int gameFinish = 0;
    int totalDot = 0;                       //we will compare this to detect "draw" situation
    char XorO = 'X';                        //this variable holds either 'X' or 'O'
    char column;                            //this is the last played column
    char winDirection;                      //this is the wining direction,vertical horizontal etc
    char playType;                          //PvP or PvAI
    bool boardType = false;                 //if boardType is true we ask for height and width,if it's false we look at the file
    string command;                         //this is the string we get from the user
    string filename;                        //this is our filename
        class Cell                          //these are expected variables,exected overloads and necessary getters/setters for our inner class Cell
        {
        private:
            int row;
            char column;
            char value;
        public:
            Cell():row(0),column(0),value('.'){}
            bool operator==(const Cell& other);
            bool operator!=(const Cell& other);
            Cell& operator++();
            Cell& operator--();
            friend istream& operator>>(istream& console ,Cell& other);
            friend ostream& operator<<(ostream& console ,const Cell& other);
            void setRow(int r){row = r;}
            void setColumn(char c){column = c;}
            void setValue(char v){value = v;}
            char getValue()const{return value;}
        };
    int play();                     //this function accomplishes a move
    int undoPlay();                 //this function erases the latest move
    int save();                     //save and load functions
    int load();
    int initBoard();                //this function initializes the board also reads the board from file too if necessary
    int printBoard();               //this function prints the board
    int horizontal();               //the next 4 function including this one is the 4 checker function for each direction
    int vertical();
    int firstAngleBisector();
    int secondAngleBisector();
    int lowerCase();                //assigns the winning cells with the lowercase characters
    int winCheck();                 //this function checks if the latest move wins by using horizontal(),vertical(),firstngleBisector() and secondAngleBisector()
    int MrOmnipotent();             //this is AI
    Cell **board;                   // our board pointer
    static void increaseLivingCell() {livingCell++;}        //functions that manipulate the livingCell
    static void decreaseLivingCell() {livingCell--;}
    static int getLivingCell(){return livingCell;}
public:
    friend istream& operator>>(istream& console ,Cell& other);          //operator overloads
    friend ostream& operator<<(ostream& console ,const Cell& other);
    ConnectFour();              //4 constructor
    ConnectFour(int w,int h);
    ConnectFour(const string &a);
    ConnectFour(const ConnectFour& other);
    ~ConnectFour();                                 //destructor
    int playGame();                                 //we can say this is our main function of the class ConnectFour
    bool operator==(const ConnectFour& other) const;
    bool operator!=(const ConnectFour& other) const;
    ConnectFour& operator=(const ConnectFour& other);
    void setDontPlay(int d){dontPlay = d;}
    int getGameFinish()const{return gameFinish;}
    void setFilename(string f){filename = f;}
};


#endif //HW4_CONNECTFOUR_H
