#include "Grid.h"
#include "BuilderBitMaps.h"
#include <string.h>

BuilderBitMaps::BuilderBitMaps() : BuilderBase() {}
BuilderBitMaps::~BuilderBitMaps() {}

void BuilderBitMaps::fillSudoku(Grid& grid)
{
    sg_uint sideLen = grid.getSideLen(); 
    sg_uint subGridCols = grid.getSubGridCols();
    resetUpdates();

    bool nonSolvableProb = true;

    while (nonSolvableProb)
    {
        grid.empty();
        initBitMaps(grid);
        fillDiagnal(grid);
        
        nonSolvableProb = !fillNonDiagnal(grid, 0, subGridCols);
    }
}

bool BuilderBitMaps::isSquareLegal(const Grid& grid, sg_uint m_i, sg_uint m_j, sg_uint i, sg_uint j, sg_uint val) const
{
    sg_uint subGridRows = grid.getSubGridRows();
    sg_uint subGridCols = grid.getSubGridCols();

    return !(m_subGridsBM[getSubGridIndex(i,j,subGridRows,subGridCols)] & (1 << val)) && !(m_rowsBM[i] & (1 << val)) && !(m_colsBM[j] & (1 << val));
}

void BuilderBitMaps::initBitMaps(const Grid& grid)
{
    sg_uint sideLen = grid.getSideLen();

    m_subGridsBM.resize(sideLen);
    m_rowsBM.resize(sideLen);
    m_colsBM.resize(sideLen);

    std::fill(m_subGridsBM.begin(), m_subGridsBM.end(), 0);
    std::fill(m_rowsBM.begin(), m_rowsBM.end(), 0);
    std::fill(m_colsBM.begin(), m_colsBM.end(), 0);
}

inline int BuilderBitMaps::getSubGridIndex(sg_uint i, sg_uint j, sg_uint subGridRows, sg_uint subGridCols) const
{
    return i / subGridRows * subGridRows + j / subGridCols;
}

void BuilderBitMaps::cancelPlacement(Grid& grid, sg_uint i, sg_uint j)
{
    sg_uint subGridRows = grid.getSubGridRows();
    sg_uint subGridCols = grid.getSubGridCols();

    m_subGridsBM[getSubGridIndex(i,j,subGridRows,subGridCols)] ^= 1 << grid(i,j);
    m_rowsBM[i] ^= 1 << grid(i,j);
    m_colsBM[j] ^= 1 << grid(i,j);
    grid(i,j) = 0;
}

void BuilderBitMaps::placeValue(Grid& grid, sg_uint i, sg_uint j, sg_uint val)
{
    sg_uint subGridRows = grid.getSubGridRows();
    sg_uint subGridCols = grid.getSubGridCols();

    m_subGridsBM[getSubGridIndex(i,j,subGridRows,subGridCols)] |= 1 << val;
    m_rowsBM[i] |= 1 << val;
    m_colsBM[j] |= 1 << val;
    grid(i,j) = val;
}