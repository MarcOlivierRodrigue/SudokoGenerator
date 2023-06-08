#pragma once
#include <vector>
#include <array>

// Foward declarations
class Grid;
class ColumnHeader;

class RowInfo
{
    public:
        RowInfo(int i, int j, int val);
        int getRow() const;
        int getCol() const;
        int getVal() const;
    private:
        RowInfo();
        const int m_val;
        const int m_row;
        const int m_col;
};

class Node
{
public:
    Node(RowInfo* rowInfo);
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
    int getRowI() const;
    int getRowJ() const;
    int getRowVal() const;
protected:
    Node();
private:
    Node* m_right;
    Node* m_left;
    Node* m_bottom;
    Node* m_top;
    ColumnHeader* m_header;
    const RowInfo* const m_rowInfo;
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
    void getHeaderIndexes(const RowInfo* const rowInfo, std::array<int, 4>& cols) const; 
    void addGridRowNodes(const RowInfo* const rowInfo);
private:
    DancingLinksGrid();
    ColumnHeader m_root;
    std::vector<ColumnHeader*> m_headers;
    std::vector<RowInfo*> m_rowInfos;
    std::vector<Node*> m_nodes;
    int m_sudokuSideLen;
    int m_sudokuSubGridRows;
    int m_sudokuSubGridCols;
};


