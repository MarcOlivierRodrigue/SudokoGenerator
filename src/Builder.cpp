#include "Grid.h"
#include "Builder.h"
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <set>

#include <iostream>


Builder::Builder() {}
Builder::~Builder() {}

void Builder::fillSudoku(Grid* grid)
{
    int sideLen = grid->getSideLen(); 
    int subGridRows = grid->getSubGridRows();
    int subGridCols = grid->getSubGridCols();

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

        // If we backtracked and a value is already there
        if((*grid)(i,j)->num != 0)
        {
            triedValues.insert((*grid)(i,j)->num);
            (*grid)(i,j)->num = 0;
        }
        int initalVal = selectRandomNum(sideLen); 
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

        if(triedValues.size() != sideLen)
        {
            (*grid)(i,j)->num = val;
            lastSquarePosibilities = triedValues.size();
        }
        else
        {
            k -= 2;
        }
    }
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