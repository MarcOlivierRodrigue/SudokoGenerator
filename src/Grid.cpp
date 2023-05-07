#include <math.h>
#include "Grid.h"
#include <assert.h>
#include <string.h>

Grid::Grid(int sideLen) : 
    m_sideLen(sideLen), 
    m_subGridRows(sqrt(sideLen)),
    m_subGridCols(sqrt(sideLen))
{
    m_data = new int[sideLen*sideLen];
    memset(m_data, 0, sizeof(int)*sideLen*sideLen);
}

Grid::Grid(int sideLen, int subGridRows, int subGridCols) :
    m_sideLen(sideLen),
    m_subGridRows(subGridRows),
    m_subGridCols(subGridCols)
{
    assert(subGridRows*subGridCols == sideLen);
    m_data = new int[sideLen*sideLen];
    memset(m_data, 0, sizeof(int)*sideLen*sideLen);
}


Grid::~Grid()
{
    delete[] m_data;
}

int* Grid::operator()(int i, int j)
{
    return m_data + (i * m_sideLen + j);
}

const int* const Grid::operator()(int i, int j) const
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

void Grid::reset()
{
    memset(m_data, 0, sizeof(int)*m_sideLen*m_sideLen);
}

