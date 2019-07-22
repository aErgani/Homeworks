//
// Created by ahmte on 24-Nov-17.
//

#ifndef HW5_CONNECTFOURDIAG_H
#define HW5_CONNECTFOURDIAG_H


#include "ConnectFourAbstract.h"

class ConnectFourDiag: public ConnectFourAbstract
{
private:
    int initBoard() override;
    int save() override;
    int load() override;
    int firstAngleBisector();
    int secondAngleBisector();
    int winCheck();
    int play() override;
public:
    int playGame() override;
};


#endif //HW5_CONNECTFOURDIAG_H
