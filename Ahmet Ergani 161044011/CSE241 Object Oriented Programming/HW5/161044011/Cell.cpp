//
// Created by ahmte on 24-Nov-17.
//

#include "Cell.h"

char Cell::getValue() const
{
    return value;
}

Cell::Cell()
{
    row = 0;
    column = 0;
    value = '.';
}

void Cell::setValue(char v)
{
    value = v;
}

void Cell::setRow(int r)
{
    row = r;
}

void Cell::setColumn(int c)
{
    column = c;
}