#pragma once

// Foward declaration of the grid Class and Square
class Grid;

class Link
{
public:
    Link();
    virtual ~Link();
    Link* getTop();
    Link* getBottom();
    Link* getRight();
    Link* getLeft();
    Link* getHeader();
    virtual void setTop(Link* top);
    void setBottom(Link* bottom);
    void setRight(Link* right);
    void setLeft(Link* left);
    int getCol() const;
    int getSize() const;
private:
    Link* m_right = nullptr;
    Link* m_left = nullptr;
    Link* m_bottom = nullptr;
    Link* m_top = nullptr;
    Link* m_header = nullptr;
    int m_col;
    int m_size;
};


class DancingLinksGrid
{
public:
    DancingLinksGrid(const Grid& grid);
    ~DancingLinksGrid();
private:
    DancingLinksGrid();
    Link* root;
    
};



