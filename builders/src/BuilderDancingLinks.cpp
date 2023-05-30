#include "Grid.h"
#include "BuilderDancingLinks.h"


void BuilderDancingLinks::fillSudoku(Grid& grid)
{
    sg_uint sideLen = grid.getSideLen(); 
    sg_uint subGridRows = grid.getSubGridRows();
    sg_uint subGridCols = grid.getSubGridCols();

    bool nonSolvableProb = true;

    while (nonSolvableProb)
    {
        grid.empty();
        fillDiagnal(grid);
        nonSolvableProb = false;
    }
}