#include "Grid.h"
#include "DancingLinks.h"

#include <iostream>

Node::Node()
{
    m_bottom = this;
    m_top = this;
    m_left = this;
    m_right = this;
}

Node::~Node()
{
    std::cout << "Link destructor" << std::endl;
    unlinkTD();
    unlinkLR();
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

void Node::setRowData(int val, int i, int j)
{
}
/*
//-------------------------------------------- COLUMN HEADER --------------------------------------------------//

ColumnHeader::ColumnHeader() : Node()
{}

ColumnHeader::~ColumnHeader()
{
    unlinkTD();
    unlinkLR();
}

int ColumnHeader::getColId() const
{
    return m_colId;
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
    root = new ColumnHeader[4 * sideLen * sideLen];
}

DancingLinksGrid::~DancingLinksGrid()
{
    delete[] root;
}
*/