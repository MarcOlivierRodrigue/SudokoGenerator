#include "Grid.h"
#include "BuilderBitMaps.h"
#include <string.h>
#include <iostream>

BuilderBitMaps::BuilderBitMaps() {}
BuilderBitMaps::~BuilderBitMaps() {}

void BuilderBitMaps::fillSudoku(Grid& grid)
{
    int sideLen = grid.getSideLen(); 
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();

    bool nonSolvableProb = true;

    while (nonSolvableProb)
    {
        grid.empty();
        initBitMaps(grid);
        fillDiagnal(grid);
        
        nonSolvableProb = !fillNonDiagnal(grid, 0, subGridCols);
    }
}

bool BuilderBitMaps::isSquareLegal(const Grid& grid, int m_i, int m_j, int i, int j, int val) const
{
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();

    return !(m_subGridsBM[getSubGridIndex(i,j,subGridRows,subGridCols)] & (1 << val)) && !(m_rowsBM[i] & (1 << val)) && !(m_colsBM[j] & (1 << val));
}

void BuilderBitMaps::initBitMaps(const Grid& grid)
{
    int sideLen = grid.getSideLen();

    m_subGridsBM.resize(sideLen);
    m_rowsBM.resize(sideLen);
    m_colsBM.resize(sideLen);

    std::fill(m_subGridsBM.begin(), m_subGridsBM.end(), 0);
    std::fill(m_rowsBM.begin(), m_rowsBM.end(), 0);
    std::fill(m_colsBM.begin(), m_colsBM.end(), 0);
}

inline int BuilderBitMaps::getSubGridIndex(int i, int j, int subGridRows, int subGridCols) const
{
    return i / subGridRows * subGridRows + j / subGridCols;
}

void BuilderBitMaps::cancelPlacement(Grid& grid, int i, int j)
{
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();

    m_subGridsBM[getSubGridIndex(i,j,subGridRows,subGridCols)] ^= 1 << grid(i,j);
    m_rowsBM[i] ^= 1 << grid(i,j);
    m_colsBM[j] ^= 1 << grid(i,j);
    grid(i,j) = 0;
}

void BuilderBitMaps::placeValue(Grid& grid, int i, int j, int val)
{
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();

    m_subGridsBM[getSubGridIndex(i,j,subGridRows,subGridCols)] |= 1 << val;
    m_rowsBM[i] |= 1 << val;
    m_colsBM[j] |= 1 << val;
    grid(i,j) = val;
}