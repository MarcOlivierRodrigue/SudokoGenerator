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
     unsigned long int getUpdatesCount() const;
protected:
    void incrementUpdates();
    void resetUpdates();
    virtual void fillDiagnal(Grid& grid);
    virtual bool fillNonDiagnal(Grid& grid, int i, int j);
    virtual void fillDiagnalSubGrid(Grid& grid, int m_i, int m_j);
    virtual void cancelPlacement(Grid& grid, int i, int j); 
    virtual void placeValue(Grid& grid, int i, int j, int val); 
private:
    unsigned long int m_updates;
};

