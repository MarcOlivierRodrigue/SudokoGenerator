#include "Grid.h"
#include "DancingLinks.h"

#include <iostream>

Node::Node() :
    m_rowI(-1),
    m_rowJ(-1),
    m_rowVal(-1)
{
    m_bottom = this;
    m_top = this;
    m_left = this;
    m_right = this;
}

Node::Node(int i, int j, int val) :
    m_rowI(i),
    m_rowJ(j),
    m_rowVal(val)
{
    m_bottom = this;
    m_top = this;
    m_left = this;
    m_right = this;
}

Node::~Node()
{
    unlinkTD();
    unlinkLR();
}

int Node::getRowI() const
{
    return m_rowI;
}

int Node::getRowJ() const
{
    return m_rowJ;
}

int Node::getRowVal() const
{
    return m_rowVal;
}

void Node::unlinkTD()
{
    m_top->m_bottom = m_bottom;
    m_bottom->m_top = m_top;
}

void Node::relinkTD()
{
    m_top->m_bottom = this;
    m_bottom->m_top = this;
}

void Node::unlinkLR()
{
    m_left->m_right = m_right;
    m_right->m_left = m_left;
}

void Node::relinkLR()
{
    m_left->m_right = this;
    m_right->m_left = this;
}

void Node::linkRight(Node* n)
{
    n->m_right = this->m_right;
    n->m_right->m_left = n;
    this->m_right = n;
    n->m_left = this;
}

void Node::linkDown(Node* n)
{
    n->m_bottom = this->m_bottom;
    n->m_bottom->m_top = n;
    this->m_bottom = n;
    n->m_top = this;
}

Node* Node::getTop()
{
    return m_top;
}

Node* Node::getBottom()
{
    return m_bottom;
}

Node* Node::getLeft()
{
    return m_left;
}

Node* Node::getRight()
{
    return m_right;
}

//-------------------------------------------- COLUMN HEADER --------------------------------------------------//

ColumnHeader::ColumnHeader() : 
    Node(),
    m_size(0)
{
}

ColumnHeader::~ColumnHeader()
{
}

int ColumnHeader::getSize() const
{
    return m_size;
}

void ColumnHeader::setSize(int size)
{
    m_size = size;
}

void ColumnHeader::incrementSize()
{
    ++m_size;
}

void ColumnHeader::decrementSize()
{
    --m_size;
}

//-------------------------------------------- Dancing Links Grid --------------------------------------------------//

DancingLinksGrid::DancingLinksGrid(const Grid& grid)
{
    int sideLen = grid.getSideLen();
    int colLen = 4 * sideLen * sideLen;
    int rowLen = sideLen * sideLen * sideLen;

    // Create the column header list
    m_headers.reserve(colLen);
    m_headers.push_back(new ColumnHeader());
    m_root.linkRight(m_headers[0]);
    for(int i = 1; i < colLen; ++i)
    {
        m_headers.push_back(new ColumnHeader());
        m_headers[i-1]->linkRight(m_headers[i]);
    }

    // Create the row list
    m_nodes.reserve(rowLen);
    
}

DancingLinksGrid::~DancingLinksGrid()
{
    for(int i = 0; i < m_headers.size(); ++i)
    {
        delete m_headers[i];
    }
}