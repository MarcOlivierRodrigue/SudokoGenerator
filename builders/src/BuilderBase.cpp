#include "Grid.h"
#include "BuilderBase.h"
#include "Util.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


BuilderBase::BuilderBase() : m_updates(0) {}
BuilderBase::~BuilderBase() {}

void BuilderBase::fillSudoku(Grid& grid)
{
    sg_uint sideLen = grid.getSideLen(); 
    sg_uint subGridCols = grid.getSubGridCols();
    resetUpdates();

    bool nonSolvableProb = true;

    while (nonSolvableProb)
    {
        grid.empty();
        fillDiagnal(grid);
        nonSolvableProb = !fillNonDiagnal(grid, 0, subGridCols);
    }
}

// Since the subgrids on the diagnal axis are independant, we fill them in naivly 
void BuilderBase::fillDiagnal(Grid& grid)
{
    sg_uint subGridRows = grid.getSubGridRows();
    sg_uint subGridCols = grid.getSubGridCols();
    sg_uint len = subGridRows > subGridCols ? subGridCols : subGridRows;

    for(sg_uint k = 0; k < len;  ++k)
    {
        fillDiagnalSubGrid(grid, k*subGridRows, k*subGridCols);
    }
}

void BuilderBase::fillDiagnalSubGrid(Grid& grid, sg_uint m_i, sg_uint m_j)
{
    std::vector<sg_uint> numVec;
    sg_uint sideLen = grid.getSideLen();
    sg_uint subGridCols = grid.getSubGridCols();

    for(sg_uint k = 1; k <= sideLen; ++k)
    {
        numVec.push_back(k);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numVec.begin(), numVec.end(), std::default_random_engine(seed));

    sg_uint i = 0;
    sg_uint j = 0;

    for(int k = 0; k < sideLen; ++k)
    {
        i = k / subGridCols;
        j = k % subGridCols;

        this->placeValue(grid, m_i + i, m_j + j, numVec[k]);
    }
}

// Classic backtracking algorithm
bool BuilderBase::fillNonDiagnal(Grid& grid, sg_uint i, sg_uint j)
{
    sg_uint sideLen = grid.getSideLen(); 
    sg_uint subGridRows = grid.getSubGridRows();
    sg_uint subGridCols = grid.getSubGridCols();

    // ignore the diagnal subgrids
    if(grid.getSubGridXIndex(j) == grid.getSubGridYIndex(i))
    {
        j += subGridCols;
    }

    if(j >= sideLen)
    {
        j = 0;
        i += 1;

        // When we change line, we want to avoid the first subgrid on the top left corner
        if(grid.getSubGridYIndex(i) == 0)
        {
            j = subGridCols;
        }
    }

    if(i >= sideLen)
    {
        return true;
    }
    
    sg_uint m_i = grid.getSubGridYMargin(i);
    sg_uint m_j = grid.getSubGridXMargin(j);
    sg_uint k = selectRandomNum(sideLen);
    sg_uint ki = 0;

    while(ki < sideLen)
    {
        incrementUpdates();

        if(this->isSquareLegal(grid, m_i, m_j, i, j, k))
        {
            this->placeValue(grid, i, j, k);
            if(fillNonDiagnal(grid, i, j+1))
            {
                return true;
            }
        }
        this->cancelPlacement(grid, i, j);
        ++ki;

        k += 1;
        if(k > sideLen)
            k = 1;
    }
    return false;
}

void BuilderBase::cancelPlacement(Grid& grid, sg_uint i, sg_uint j)
{
    grid(i,j) = 0;
}

void BuilderBase::placeValue(Grid& grid, sg_uint i, sg_uint j, sg_uint val)
{
    grid(i,j) = val;
}

unsigned long int BuilderBase::getUpdatesCount() const
{
    return m_updates;
}

void BuilderBase::incrementUpdates()
{
    ++m_updates;
}

void BuilderBase::resetUpdates()
{
    m_updates = 0;
}