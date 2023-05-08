#pragma once 

class Grid
{
public:
    Grid(int sideLen);
    Grid(int sideLen, int subGridRows, int subGridCols);
    ~Grid();
    int& operator() (int i, int j);
    const int& operator() (int i, int j) const;
    int getSideLen() const;
    int getSubGridRows() const;
    int getSubGridCols() const; 
    int getSubGridXIndex(int j) const;
    int getSubGridYIndex(int i) const;
    int getSubGridXMargin(int j) const;
    int getSubGridYMargin(int i) const;
    void empty();
private:
    Grid();
    const int m_sideLen;
    const int m_subGridRows;
    const int m_subGridCols;
    int* m_data;
};
