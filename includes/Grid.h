#pragma once 

class Grid
{
public:
    Grid(int side);
    ~Grid();
    void print();
private:
    int m_side;
    int m_sqrtSide;
};
