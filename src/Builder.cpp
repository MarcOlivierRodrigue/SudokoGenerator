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
        grid.reset();
        fillDiagnal(grid);
        nonSolvableProb = !fillNonDiagnal(grid, 0, subGridCols);
    }

    // Failled Son
    /*
    int lastSquarePosibilities;
    for(int k = 0; k < sideLen*sideLen; ++k)
    {
        int i = k / sideLen;
        int j = k % sideLen;
        
        // get the subgrid initial coordinates
        int m_i = i / subGridRows * subGridRows;
        int m_j = j / subGridCols * subGridCols;

        // Initialize the table to keep track of all the values we have tried
        std::set<int> triedValues;
        
        int initalVal; 
        // If we backtracked and a value is already there
        if(*grid(i,j) != 0)
        {
            initalVal = *grid(i,j);
            triedValues.insert(initalVal);
            *grid(i,j) = 0;
        }
        else
        {
            initalVal = selectRandomNum(sideLen);
        }
        int val = initalVal;   

        while (!isSquareLegal(grid, m_i, m_j, i, j, val))
        {
            triedValues.insert(val);
            if(triedValues.size() == sideLen)
            {
                break;
            }
            val = incrementVal(val, sideLen);
        }
        std::cout << "K:" << k << " " << m_i << " " <<  m_j << std::endl;
        std::cout << triedValues.size() << std::endl;


        if(triedValues.size() != sideLen)
        {
            *grid(i,j) = val;
            lastSquarePosibilities = triedValues.size();
        }
        else
        {
            k -= 2;
        }
    }
    */
}

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

        *grid(m_i + i, m_j + j) = numSet[k]; 
    }
}


bool Builder::fillNonDiagnal(Grid& grid, int i, int j)
{
    int sideLen = grid.getSideLen(); 
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();
    int m_i = i - i % subGridRows;
    int m_j = j - j % subGridCols;

    // ignore the diagnal subgrids
    if(m_i == m_j)
    {
        j += subGridCols;
    }

    if(j >= sideLen)
    {
        j = 0;
        i += 1;

        if(m_i == 0 && i / subGridRows == 0)
        {
            j = subGridRows;
        }
    }

    if(i >= sideLen)
    {
        return true;
    }
    
    m_i = i - i % subGridRows;
    m_j = j - j % subGridCols;

    for(int k = 1; k <= sideLen; ++k)
    {
        if(isSquareLegal(grid, m_i, m_j, i, j, k))
        {
            *grid(i,j) = k;
            if(fillNonDiagnal(grid, i, j+1))
            {
                return true;
            }
        }
        *grid(i,j) = 0;
    }
    return false;
}


int Builder::selectRandomNum(int max)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    return rand() % max + 1;
}

int Builder::incrementVal(int val, int max)
{
    val += 1;
    if(val > max)
    {
        val = 1;
    }
    return val;
}