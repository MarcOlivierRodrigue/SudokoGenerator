#pragma once
#include "Logic.h"

// Foward declaration of the grid Class and Square
class Grid;

class BuilderBase : public Logic
{
public:
    BuilderBase();
    virtual ~BuilderBase();
    virtual void fillSudoku(Grid& grid);
protected:
    virtual void fillDiagnal(Grid& grid);
    virtual void fillDiagnalSubGrid(Grid& grid, int m_i, int m_j);
    virtual bool fillNonDiagnal(Grid& grid, int i, int j);
    virtual void cancelPlacement(Grid& grid, int i, int j); 
    virtual void placeValue(Grid& grid, int i, int j, int val); 
};

