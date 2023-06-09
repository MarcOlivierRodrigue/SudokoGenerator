#include <iostream>
#include <limits>
#include <chrono>
#include <ctime>
#include "Grid.h"
#include "Printer.h"
#include "BuilderBitMaps.h"
#include "DancingLinksGrid.h"



int main(int argc, char *argv[])
{
    int gridRes = -1;
    int builderIndex = -1;
    Printer printer;
    BuilderBase* builder;
    Grid* grid;

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::duration<double> time_span;

    while (gridRes == -1)
    {
        std::cout << "What board do you want?: " << std::endl;
        std::cout << "1. 4x4" << std::endl; 
        std::cout << "2. 6x6" << std::endl; 
        std::cout << "3. 9x9" << std::endl;
        std::cout << "4. 16x16" << std::endl;
        std::cout << "5. 25x25" << std::endl;

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
                // 16x16
                grid = new Grid(16);
                break;
            case 5: 
                // 25x25
                grid = new Grid(25);
                break;
            default:
                std::cout<< "ERROR: invalid input" << std::endl;
                gridRes = -1;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }

    while (builderIndex == -1)
    {
        std::cout << "Which building algorithm do want?: " << std::endl;
        std::cout << "1. Classic Backtracking" << std::endl; 
        std::cout << "2. Backtracking with bitmaps" << std::endl;

        std::cin >> builderIndex;
        
        switch (builderIndex)
        {
            case 1:
                // Builderbase
                builder = new BuilderBase();
                break;
            case 2:
                // BuilderBitMaps
                builder = new BuilderBitMaps();
                break;
            default:
                std::cout<< "ERROR: invalid input" << std::endl;
                builderIndex = -1;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }

    // TEST ////////////////////////////////////////////////////////////////////////////////
    start = std::chrono::high_resolution_clock::now();
    DancingLinksGrid g(9);
    end = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << "time to build: " << time_span.count() << " seconds" << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////

    start = std::chrono::high_resolution_clock::now();
    builder->fillSudoku(*grid);
    end = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    printer.printGrid(*grid);

    std::cout << "time to build: " << time_span.count() << " seconds" << std::endl;
    std::cout << "recursive operations: " << builder->getUpdatesCount() << std::endl;


    delete builder;
    delete grid;
    return 0;
}