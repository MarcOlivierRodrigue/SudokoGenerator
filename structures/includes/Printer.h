#pragma once

// Foward declaration of the grid Class and Square
class Grid;

class Printer
{
public:
    Printer();
    ~Printer();
    void printGrid(const Grid& grid) const;
private:
    void printLine(int len) const;
    void printSquare(int square, int totalSpace) const;
    int digitsInInt(int len) const;
};
