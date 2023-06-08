#pragma once
#include <vector>
#include <array>

// Foward declarations
class Grid;
class ColumnHeader;

class Node
{
public:
    Node(int i, int j, int val);
    virtual ~Node();
    void relinkTD();
    void unlinkTD();
    void relinkLR();
    void unlinkLR();
    void linkRight(Node* n);
    void linkDown(Node* n);
    void linkToColumn(ColumnHeader* c);
    Node* getTop();
    Node* getBottom();
    Node* getLeft();
    Node* getRight();
    int getI() const;
    int getJ() const;
    int getVal() const;
protected:
    Node();
private:
    Node* m_right;
    Node* m_left;
    Node* m_bottom;
    Node* m_top;
    ColumnHeader* m_header;
    const int m_i;
    const int m_j;
    const int m_val;
};


class ColumnHeader : public Node
{
public:
    ColumnHeader();
    ~ColumnHeader();
    void incrementSize();
    void decrementSize();
    void setSize(int size);
    int getSize() const;
private:
    int m_size;
};

class DancingLinksGrid
{
public:
    DancingLinksGrid(const Grid& grid);
    DancingLinksGrid(int sideLen);
    DancingLinksGrid(int sideLen, int subGridRows, int subGridCols);
    ~DancingLinksGrid();
    void getHeaderIndexes(int i, int j, int val, std::array<int, 4>& cols) const; 
    void addGridRowNodes(int i, int j, int val);
private:
    DancingLinksGrid();
    ColumnHeader m_root;
    std::vector<ColumnHeader*> m_headers;
    std::vector<Node*> m_nodes;
    int m_sudokuSideLen;
    int m_sudokuSubGridRows;
    int m_sudokuSubGridCols;
};


