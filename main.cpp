#include <iostream>
#include <limits>
#include "Grid.h"
#include "Printer.h"


int main(int argc, char *argv[])
{
    int gridRes = -1;
    Printer printer;
    Grid* grid;

    while (gridRes == -1)
    {
        std::cout << "What board do you want?: " << std::endl << "1. 4x4" << std::endl << "2. 6x6" << std::endl <<  "3. 9x9" << std::endl;
        std::cin >> gridRes;

        switch (gridRes)
        {
            case 1:
                std::cout << "4x4" << std::endl;
                grid = new Grid(4);
                break;
            case 2:
                std::cout << "6x6" << std::endl;
                grid = new Grid(6,2,3);
                break;
            case 3: 
                std::cout << "9x9" << std::endl;
                grid = new Grid(9);
                break;
            default:
                std::cout<< "ERROR: invalid input" << std::endl;
                gridRes = -1;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
        printer.printGrid(*grid);
    }
    
    return 0;
}