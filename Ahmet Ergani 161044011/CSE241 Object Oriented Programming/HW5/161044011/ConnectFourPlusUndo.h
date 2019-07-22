//
// Created by ahmte on 24-Nov-17.
//

#ifndef HW5_CONNECTFOURPLUSUNDO_H
#define HW5_CONNECTFOURPLUSUNDO_H

#include "Cell.h"
#include "ConnectFourAbstract.h"

class ConnectFourPlusUndo: public ConnectFourAbstract
{
private:
    char * moves;               //this dynamic array holds all accomplished moves
    int initBoard() override;   //a little bit different than the ConnectFourPlus and ConnectFourDiag
    int save() override;
    int load() override;
    int horizontal();
    int vertical();
    int winCheck() override;
    int plusUndo();
    int play() override;
public:
    int playGame() override;
    ~ConnectFourPlusUndo() override;
};


#endif //HW5_CONNECTFOURPLUSUNDO_H
