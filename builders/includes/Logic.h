#pragma once
#include "Types.h"

// Foward declaration of the grid Class and Square
class Grid;

class Logic
{
protected:
    virtual bool isSquareLegal(const Grid& grid, sg_uint m_i, sg_uint m_j, sg_uint i, sg_uint j, sg_uint val) const;
    virtual bool isUnusedInSubGrid(const Grid& grid, sg_uint m_i, sg_uint m_j, sg_uint val) const;
    virtual bool isUnusedInRow(const Grid& grid, sg_uint i, sg_uint val) const;
    virtual bool isUnusedInCol(const Grid& grid, sg_uint j, sg_uint val) const;
};
