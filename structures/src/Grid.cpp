#include <math.h>
#include "Grid.h"
#include "Util.h"
#include <assert.h>
#include <string.h>

Grid::Grid(int sideLen) : 
    m_sideLen(sideLen), 
    m_subGridRows(sqrt(sideLen)),
    m_subGridCols(sqrt(sideLen))
{
    assert(isPerfectSquare(sideLen));
    m_data = new int[sideLen*sideLen];
    empty();
}

Grid::Grid(int sideLen, int subGridRows, int subGridCols) :
    m_sideLen(sideLen),
    m_subGridRows(subGridRows),
    m_subGridCols(subGridCols)
{
    assert(subGridRows*subGridCols == sideLen);
    m_data = new int[sideLen*sideLen];
    empty();
}

Grid::Grid(const Grid& grid) :
    m_sideLen(grid.getSideLen()),
    m_subGridCols(grid.getSubGridCols()),
    m_subGridRows(grid.getSubGridRows())
{
    m_data = new int[m_sideLen*m_sideLen];
    memcpy(m_data, grid.m_data, sizeof(int)*m_sideLen*m_sideLen);
}

Grid::~Grid()
{
    delete[] m_data;
}

int& Grid::operator()(int i, int j)
{
    return *(m_data + (i * m_sideLen + j));
}

const int& Grid::operator()(int i, int j) const
{
    return *(m_data + (i * m_sideLen + j));
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

int Grid::getSubGridXMargin(int j) const
{
    return j - j % m_subGridCols;
}

int Grid::getSubGridYMargin(int i) const
{
    return i - i % m_subGridRows;
}

int Grid::getSubGridXIndex(int j) const
{
    return j / m_subGridCols;
}

int Grid::getSubGridYIndex(int i) const
{
    return i / m_subGridRows;
}

void Grid::empty()
{
    memset(m_data, 0, sizeof(int)*m_sideLen*m_sideLen);
}



