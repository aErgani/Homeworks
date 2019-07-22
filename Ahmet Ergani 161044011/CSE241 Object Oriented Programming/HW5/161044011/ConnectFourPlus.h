//
// Created by ahmte on 24-Nov-17.
//

#ifndef HW5_CONNECTFOURPLUS_H
#define HW5_CONNECTFOURPLUS_H


#include "ConnectFourAbstract.h"

class ConnectFourPlus: public ConnectFourAbstract
{
private:
    int initBoard() override;
    int save() override;
    int load() override;
    int horizontal();
    int vertical();
    int winCheck() override;
    int play() override;        //accomplishes a single move
public:
    int playGame() override;
};


#endif //HW5_CONNECTFOURPLUS_H
