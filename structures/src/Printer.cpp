#include <iostream>
#include <cmath>
#include "Grid.h"
#include "Printer.h"

Printer::Printer() {}
Printer::~Printer() {}

void Printer::printLine(sg_uint len) const 
{
    for(int i = 0; i < len; ++i)
    {
        std::cout << "-";
    }
    std::cout << "\n";
}

sg_uint Printer::digitsInInt(sg_uint num) const
{
    return sg_uint(log10(double(num)) + 1);
}

void Printer::printSquare(sg_uint square, sg_uint totalSpace) const
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
    sg_uint sideLen = grid.getSideLen();
    sg_uint subGridCols =  grid.getSubGridCols();
    sg_uint subGridRows = grid.getSubGridRows();

    sg_uint charPerSquare = digitsInInt(sideLen) + 2;
    sg_uint lineLen = sideLen * (charPerSquare + 1) +  sideLen / grid.getSubGridCols();
    
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

            printSquare(grid(i,j), charPerSquare);
            std::cout << "|";
        }
        std::cout << "\n";
        printLine(lineLen);
    }
}