#include <iostream>
#include <cmath>
#include "Grid.h"
#include "Printer.h"

Printer::Printer() {}
Printer::~Printer() {}

void Printer::printLine(int len) const 
{
    for(int i = 0; i < len; ++i)
    {
        std::cout << "-";
    }
    std::cout << "\n";
}

int Printer::digitsInInt(int num) const
{
    if(num > 0)
    {
        return int(log10(double(num)) + 1);
    }
    else
    {
        return 1;
    }
}

void Printer::printSquare(int square, int totalSpace) const
{
    if(square != 0)
    {
        int digitCount = digitsInInt(square);
        int initialSpace = totalSpace - (digitCount + 1);
        for(int i = 0; i < initialSpace; ++i)
        {
            std::cout << " ";
        } 
        std::cout << square << " ";
    }
    else
    {
        for(int i = 0; i < totalSpace; ++i)
        {
            std::cout << " ";
        }  
    }

}

void Printer::printGrid(const Grid& grid) const
{
    int sideLen = grid.getSideLen();
    int subGridCols =  grid.getSubGridCols();
    int subGridRows = grid.getSubGridRows();

    int charPerSquare = digitsInInt(sideLen) + 2;
    int lineLen = sideLen * (charPerSquare + 1) +  sideLen / grid.getSubGridCols();
    
    printLine(lineLen);
    for(int i = 0; i < sideLen; ++i)
    {
        if(i != 0 && i % subGridRows == 0)
        {
            printLine(lineLen);
        }

        std::cout << "|";
        for(int j = 0; j < sideLen; ++j)
        {
            if(j != 0 && j % subGridCols == 0)
            {
                std::cout << "|";
            }

            printSquare(*grid(i,j), charPerSquare);
            std::cout << "|";
        }
        std::cout << "\n";
        printLine(lineLen);
    }
}