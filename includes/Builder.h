#pragma once
#include "Logic.h"

// Foward declaration of the grid Class and Square
class Grid;

class Builder : public Logic
{
public:
    Builder();
    ~Builder();
    void fillSudoku(Grid* grid);
private:

    int selectRandomNum(int max);
    inline int incrementVal(int val, int max);
};

