#pragma once

// Foward declaration of the grid Class and Square
class Grid;

class Logic
{
protected:
    virtual bool isSquareLegal(const Grid* const grid, int m_i, int m_j, int i, int j, int val) const;
    virtual bool isUnusedInSubGrid(const Grid* const grid, int m_i, int m_j, int val) const;
    virtual bool isUnusedInRow(const Grid* const grid, int i, int val) const;
    virtual bool isUnusedInCol(const Grid* const grid, int j, int val) const;
};
