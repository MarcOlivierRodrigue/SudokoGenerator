#pragma once
#include "Types.h"

// Foward declaration of the grid Class and Square
class Grid;

class Printer
{
public:
    Printer();
    ~Printer();
    void printGrid(const Grid& grid) const;
private:
    void printLine(sg_uint len) const;
    void printSquare(sg_uint square, sg_uint totalSpace) const;
    sg_uint digitsInInt(sg_uint len) const;
};
