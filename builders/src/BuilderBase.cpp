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
    int sideLen = grid.getSideLen(); 
    int subGridCols = grid.getSubGridCols();
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
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();
    int len = subGridRows > subGridCols ? subGridCols : subGridRows;

    for(int k = 0; k < len;  ++k)
    {
        fillDiagnalSubGrid(grid, k*subGridRows, k*subGridCols);
    }
}

void BuilderBase::fillDiagnalSubGrid(Grid& grid, int m_i, int m_j)
{
    std::vector<int> numVec;
    int sideLen = grid.getSideLen();
    int subGridCols = grid.getSubGridCols();

    for(int k = 1; k <= sideLen; ++k)
    {
        numVec.push_back(k);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numVec.begin(), numVec.end(), std::default_random_engine(seed));

    int i = 0;
    int j = 0;

    for(int k = 0; k < sideLen; ++k)
    {
        i = k / subGridCols;
        j = k % subGridCols;

        this->placeValue(grid, m_i + i, m_j + j, numVec[k]);
    }
}

// Classic backtracking algorithm
bool BuilderBase::fillNonDiagnal(Grid& grid, int i, int j)
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
    
    int m_i = grid.getSubGridYMargin(i);
    int m_j = grid.getSubGridXMargin(j);
    int k = selectRandomNum(sideLen);
    int ki = 0;

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

void BuilderBase::cancelPlacement(Grid& grid, int i, int j)
{
    grid(i,j) = 0;
}

void BuilderBase::placeValue(Grid& grid, int i, int j, int val)
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