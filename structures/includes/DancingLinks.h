#pragma once
#include <vector>

// Foward declarations
class Grid;
class ColumnHeader;

class Node
{
public:
    Node();
    Node(int i, int j, int val);
    virtual ~Node();
    void relinkTD();
    void unlinkTD();
    void relinkLR();
    void unlinkLR();
    void linkRight(Node* n);
    void linkDown(Node* n);
    Node* getTop();
    Node* getBottom();
    Node* getLeft();
    Node* getRight();
    int getRowI() const;
    int getRowJ() const;
    int getRowVal() const;
private:
    Node* m_right;
    Node* m_left;
    Node* m_bottom;
    Node* m_top;
    ColumnHeader* m_header;
    const int m_rowVal;
    const int m_rowI;
    const int m_rowJ;
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
    ~DancingLinksGrid();
private:
    void addRow(int i, int j, int val);
    DancingLinksGrid();
    ColumnHeader m_root;
    std::vector<ColumnHeader*> m_headers;
    std::vector<Node*> m_nodes;
};


