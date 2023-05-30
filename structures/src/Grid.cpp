#include <math.h>
#include "Grid.h"
#include "Util.h"
#include <assert.h>
#include <string.h>

Grid::Grid(sg_uint sideLen) : 
    m_sideLen(sideLen), 
    m_subGridRows(sqrt(sideLen)),
    m_subGridCols(sqrt(sideLen))
{
    assert(isPerfectSquare(sideLen));
    m_data = new sg_uint[sideLen*sideLen];
    empty();
}

Grid::Grid(sg_uint sideLen, sg_uint subGridRows, sg_uint subGridCols) :
    m_sideLen(sideLen),
    m_subGridRows(subGridRows),
    m_subGridCols(subGridCols)
{
    assert(subGridRows*subGridCols == sideLen);
    m_data = new sg_uint[sideLen*sideLen];
    empty();
}

Grid::Grid(const Grid& grid) :
    m_sideLen(grid.getSideLen()),
    m_subGridCols(grid.getSubGridCols()),
    m_subGridRows(grid.getSubGridRows())
{
    m_data = new sg_uint[m_sideLen*m_sideLen];
    memcpy(m_data, grid.m_data, sizeof(sg_uint)*m_sideLen*m_sideLen);
}

Grid::~Grid()
{
    delete[] m_data;
}

sg_uint& Grid::operator()(sg_uint i, sg_uint j)
{
    return *(m_data + (i * m_sideLen + j));
}

const sg_uint& Grid::operator()(sg_uint i, sg_uint j) const
{
    return *(m_data + (i * m_sideLen + j));
}

sg_uint  Grid::getSideLen() const
{
    return m_sideLen;
}

sg_uint  Grid::getSubGridRows() const
{
    return m_subGridRows;
}

sg_uint  Grid::getSubGridCols() const
{
    return m_subGridCols;
}

sg_uint Grid::getSubGridXMargin(sg_uint j) const
{
    return j - j % m_subGridCols;
}

sg_uint Grid::getSubGridYMargin(sg_uint i) const
{
    return i - i % m_subGridRows;
}

sg_uint Grid::getSubGridXIndex(sg_uint j) const
{
    return j / m_subGridCols;
}

sg_uint Grid::getSubGridYIndex(sg_uint i) const
{
    return i / m_subGridRows;
}

void Grid::empty()
{
    memset(m_data, 0, sizeof(int)*m_sideLen*m_sideLen);
}



