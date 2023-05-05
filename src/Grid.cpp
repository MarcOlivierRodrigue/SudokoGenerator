#include <math.h>
#include "Grid.h"

Grid::Grid(int sideLen) : 
    m_sideLen(sideLen), 
    m_subGridRows(sqrt(sideLen)),
    m_subGridCols(sqrt(sideLen))
{
    m_data = new Square[sideLen*sideLen];
}

Grid::Grid(int sideLen, int subGridRows, int subGridCols) :
    m_sideLen(sideLen),
    m_subGridRows(subGridRows),
    m_subGridCols(subGridCols)
{
    m_data = new Square[sideLen*sideLen];
}


Grid::~Grid()
{
    delete[] m_data;
}

Square* Grid::operator()(int i, int j)
{
    return m_data + (i * m_sideLen + j);
}

const Square* const Grid::operator()(int i, int j) const
{
    return m_data + (i * m_sideLen + j);
}

int  Grid::getSideLen() const
{
    return m_sideLen;
}

int  Grid::getSubGridRows() const
{
    return m_subGridRows;
}

int  Grid::getSubGridCols() const
{
    return m_subGridCols;
} 

