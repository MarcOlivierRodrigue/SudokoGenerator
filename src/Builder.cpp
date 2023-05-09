#include "Grid.h"
#include "Builder.h"
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>


Builder::Builder() {}
Builder::~Builder() {}

void Builder::fillSudoku(Grid& grid)
{
    int sideLen = grid.getSideLen(); 
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();

    bool nonSolvableProb = true;

    while (nonSolvableProb)
    {
        grid.empty();
        fillDiagnal(grid);
        nonSolvableProb = !fillNonDiagnal(grid, 0, subGridCols);
    }
}

// Since the subgrids on the diagnal axis are independant, we fill them in naivly 
void Builder::fillDiagnal(Grid& grid)
{
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();
    int len = subGridRows > subGridCols ? subGridCols : subGridRows;

    for(int k = 0; k < len;  ++k)
    {
        fillDiagnalSubGrid(grid, k*subGridRows, k*subGridCols);
    }
}

void Builder::fillDiagnalSubGrid(Grid& grid, int m_i, int m_j)
{
    std::vector<int> numSet;
    int sideLen = grid.getSideLen();
    int subGridCols = grid.getSubGridCols();

    for(int k = 1; k <= sideLen; ++k)
    {
        numSet.push_back(k);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numSet.begin(), numSet.end(), std::default_random_engine(seed));

    int i = 0;
    int j = 0;

    for(int k = 0; k < sideLen; ++k)
    {
        i = k / subGridCols;
        j = k % subGridCols;

        this->placeValue(grid, m_i + i, m_j + j, numSet[k]);
    }
}

// Classic backtracking algorithm
bool Builder::fillNonDiagnal(Grid& grid, int i, int j)
{
    int sideLen = grid.getSideLen(); 
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();

    // ignore the diagnal subgrids
    if(grid.getSubGridXIndex(j) == grid.getSubGridYIndex(i))
    {
        j += subGridCols;
    }

    if(j >= sideLen)
    {
        j = 0;
        i += 1;

        if(grid.getSubGridYIndex(i) == 0)
        {
            j = subGridCols;
        }
    }

    if(i >= sideLen)
    {
        return true;
    }
    
    int m_i = grid.getSubGridYMargin(i);
    int m_j = grid.getSubGridXMargin(j);

    for(int k = 1; k <= sideLen; ++k)
    {
        if(this->isSquareLegal(grid, m_i, m_j, i, j, k))
        {
            this->placeValue(grid, i, j, k);
            if(fillNonDiagnal(grid, i, j+1))
            {
                return true;
            }
        }
        this->cancelPlacement(grid, i, j);
    }
    return false;
}

void Builder::cancelPlacement(Grid& grid, int i, int j)
{
    grid(i,j) = 0;
}


void Builder::placeValue(Grid& grid, int i, int j, int val)
{
    grid(i,j) = val;
}