#pragma once 

struct Square
{
   int num = 0;
   bool isHidden = false;
};

class Grid
{
public:
    Grid(int sideLen);
    Grid(int sideLen, int subGridRows, int subGridCols);
    ~Grid();
    Square* operator() (int i, int j);
    const Square* const operator() (int i, int j) const;
    int getSideLen() const;
    int getSubGridRows() const;
    int getSubGridCols() const; 
private:
    Grid();
    const int m_sideLen;
    const int m_subGridRows;
    const int m_subGridCols;
    Square* m_data;
};
