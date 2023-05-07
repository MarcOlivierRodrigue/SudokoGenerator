#include <iostream>
#include <limits>
#include "Grid.h"
#include "Printer.h"
#include "Builder.h"


int main(int argc, char *argv[])
{
    int gridRes = -1;
    Printer printer;
    Builder builder;
    Grid* grid;

    while (gridRes == -1)
    {
        std::cout << "What board do you want?: " << std::endl << "1. 4x4" << std::endl << "2. 6x6" << std::endl <<  "3. 9x9" << std::endl << "4. VERY BIG" << std::endl;
        std::cin >> gridRes;

        switch (gridRes)
        {
            case 1:
                // 4x4
                grid = new Grid(4);
                break;
            case 2:
                // 6x6
                grid = new Grid(6,2,3);
                break;
            case 3: 
                // 9x9
                grid = new Grid(9);
                break;
            case 4: 
                // VERY BIG
                grid = new Grid(16129);
                break;
            default:
                std::cout<< "ERROR: invalid input" << std::endl;
                gridRes = -1;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
        
        builder.fillSudoku(grid);

        if(gridRes < 4)
        {
            printer.printGrid(*grid);
        }
    }
    
    delete grid;
    return 0;
}