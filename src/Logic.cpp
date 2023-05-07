#include "Grid.h"
#include "Logic.h"

bool Logic::isSquareLegal(const Grid* const grid, int m_i, int m_j, int i, int j, int val) const
{
    return isUnusedInSubGrid(grid, m_i, m_j, val) && isUnusedInCol(grid, j, val) && isUnusedInRow(grid, i, val);
}

bool Logic::isUnusedInSubGrid(const Grid* const grid, int m_i, int m_j, int val) const
{
    for(int i = m_i; i < m_i + grid->getSubGridRows(); ++i)
    {
        for(int j = m_j; j < m_j + grid->getSubGridCols(); ++j)
        {
            if((*grid)(i, j)->num == val)
            {
                return false;
            }
        }
    }
    return true;
}

bool Logic::isUnusedInRow(const Grid* const grid, int i, int val) const
{
    for(int j = 0; j < grid->getSideLen(); ++j)
    {
        if((*grid)(i, j)->num == val)
        {
            return false;
        }
    }
    return true;
}

bool Logic::isUnusedInCol(const Grid* const grid, int j, int val) const
{
    for(int i = 0; i < grid->getSideLen(); ++i)
    {
        if((*grid)(i, j)->num == val)
        {
            return false;
        }
    }
    return true;
}