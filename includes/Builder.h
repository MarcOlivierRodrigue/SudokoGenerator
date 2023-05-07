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
    void fillDiagnal(Grid* grid);
    void fillDiagnalSubGrid(Grid* grid, int m_i, int m_j);
    void fillNonDiagnal(Grid* grid);
    void fillNonDiagnalSubGrid(Grid* grid, int m_i, int m_j);
    int selectRandomNum(int max);
    inline int incrementVal(int val, int max);
};

