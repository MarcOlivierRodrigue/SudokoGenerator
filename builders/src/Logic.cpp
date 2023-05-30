#include "Grid.h"
#include "Logic.h"

bool Logic::isSquareLegal(const Grid& grid, sg_uint m_i, sg_uint m_j, sg_uint i, sg_uint j, sg_uint val) const
{
    return isUnusedInSubGrid(grid, m_i, m_j, val) && isUnusedInCol(grid, j, val) && isUnusedInRow(grid, i, val);
}

bool Logic::isUnusedInSubGrid(const Grid& grid, sg_uint m_i, sg_uint m_j, sg_uint val) const
{
    for(sg_uint i = m_i; i < m_i + grid.getSubGridRows(); ++i)
    {
        for(sg_uint j = m_j; j < m_j + grid.getSubGridCols(); ++j)
        {
            if(grid(i, j) == val)
            {
                return false;
            }
        }
    }
    return true;
}

bool Logic::isUnusedInRow(const Grid& grid, sg_uint i, sg_uint val) const
{
    for(sg_uint j = 0; j < grid.getSideLen(); ++j)
    {
        if(grid(i, j) == val)
        {
            return false;
        }
    }
    return true;
}

bool Logic::isUnusedInCol(const Grid& grid, sg_uint j, sg_uint val) const
{
    for(sg_uint i = 0; i < grid.getSideLen(); ++i)
    {
        if(grid(i, j) == val)
        {
            return false;
        }
    }
    return true;
}

