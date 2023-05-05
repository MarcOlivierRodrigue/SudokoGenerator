#pragma once

// Foward declaration of the grid Class
class Grid;

class Printer
{
public:
    Printer();
    ~Printer();
    void printGrid(const Grid& grid) const;
private:
    void printLine(int len) const;
    void printSquare(const Square* const square, int totalSpace) const;
    int digitsInInt(int len) const;
};