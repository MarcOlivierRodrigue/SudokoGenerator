#include "DancingLinks.h"

#include <iostream>

Link::Link() {}

Link::~Link()
{
    std::cout << "Link destructor" << std::endl;
    if(m_top != nullptr)
    {
        m_top->m_bottom = m_bottom;
    }

    if(m_bottom != nullptr)
    {
        m_bottom->m_top = m_top;
    }

    if(m_left != nullptr)
    {
        m_left->m_right = m_right;
    }

    if(m_right != nullptr)
    {
        m_right->m_left = m_left;
    }
}

Link* Link::getTop()
{
    return m_top;
}

Link* Link::getBottom() 
{
    return m_bottom;
}

Link* Link::getRight() 
{
    return m_right;
}

Link* Link::getLeft() 
{
    return m_left;
}

void Link::setTop(Link* top)
{
    m_top = top;
}

void Link::setBottom(Link* bottom)
{
    m_bottom = bottom;
}

void Link::setRight(Link* right)
{
    m_right = right;
}

void Link::setLeft(Link* left)
{
    m_left = left;
}

int Link::getCol() const
{
    return m_col;
}

int Link::getSize() const
{
    return m_size;
}