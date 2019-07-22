//
// Created by ahmte on 24-Nov-17.
//

#ifndef HW5_CELL_H
#define HW5_CELL_H


class Cell
{
private:
    int row;
    int column;
    char value;
public:
    char getValue() const;
    Cell();
    void setValue(char v);
    void setColumn(int c);
    void setRow(int r);
};


#endif //HW5_CELL_H
