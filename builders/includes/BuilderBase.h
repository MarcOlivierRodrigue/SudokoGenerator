#pragma once
#include "Logic.h"
#include "Types.h"

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
    virtual bool fillNonDiagnal(Grid& grid, sg_uint i, sg_uint j);
    virtual void fillDiagnalSubGrid(Grid& grid, sg_uint m_i, sg_uint m_j);
    virtual void cancelPlacement(Grid& grid, sg_uint i, sg_uint j); 
    virtual void placeValue(Grid& grid, sg_uint i, sg_uint j, sg_uint val); 
private:
    unsigned long int m_updates;
};

