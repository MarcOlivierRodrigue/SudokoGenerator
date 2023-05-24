#pragma once

// Foward declaration of the grid Class and Square
class Grid;

class Node
{
public:
    Node();
    virtual ~Node();
    void relinkTD();
    void unlinkTD();
    void relinkLR();
    void unlinkLR();
    void setRowData(int val, int i, int j);
private:
    Node* m_right;
    Node* m_left;
    Node* m_bottom;
    Node* m_top;
    //ColumnHeader* m_header;
    int m_rowVal;
    int m_rowI;
    int m_rowJ;
};

/*
class ColumnHeader : public Node
{
public:
    ColumnHeader();
    ~ColumnHeader();
    void setSize(int size);
    void incrementSize();
    void decrementSize();
    int getSize() const;
    void setColId(int colId);
    int getColId() const;
private:
    int m_colId = -1;
    int m_size = 0;
};


class DancingLinksGrid
{
public:
    DancingLinksGrid(const Grid& grid);
    ~DancingLinksGrid();
    ColumnHeader* getRoot();
private:
    DancingLinksGrid();
    ColumnHeader* root;
};
*/


