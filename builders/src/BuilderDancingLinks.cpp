#include "Grid.h"
#include "BuilderDancingLinks.h"


void BuilderDancingLinks::fillSudoku(Grid& grid)
{
    int sideLen = grid.getSideLen(); 
    int subGridRows = grid.getSubGridRows();
    int subGridCols = grid.getSubGridCols();

    bool nonSolvableProb = true;

    while (nonSolvableProb)
    {
        grid.empty();
        fillDiagnal(grid);
        nonSolvableProb = false;
    }
}