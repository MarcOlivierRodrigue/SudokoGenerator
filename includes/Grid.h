#pragma once 

class Grid
{
public:
    Grid(int sideLen);
    Grid(int sideLen, int subGridRows, int subGridCols);
    ~Grid();
    int* operator() (int i, int j);
    const int* const operator() (int i, int j) const;
    int getSideLen() const;
    int getSubGridRows() const;
    int getSubGridCols() const; 
    int getSubGridXCoord(int j) const;
    int getSubGridYCoord(int i) const;
    void reset();
private:
    Grid();
    const int m_sideLen;
    const int m_subGridRows;
    const int m_subGridCols;
    int* m_data;
};
