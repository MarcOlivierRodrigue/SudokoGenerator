#include <math.h>
#include "Grid.h"
#include "DancingLinksGrid.h"
#include "Util.h"
#include <assert.h>

//-------------------------------------------- Node --------------------------------------------------//
Node::Node() : m_i(-1), m_j(-1), m_val(-1)
{
    m_bottom = this;
    m_top = this;
    m_left = this;
    m_right = this;
}

Node::Node(int i, int j, int val) : m_i(i), m_j(j), m_val(val)
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

void Node::linkToColumn(ColumnHeader* c)
{
    m_header = c;
    Node* curr = m_header;
    while(curr->m_bottom != m_header)
    {
        curr = curr->m_bottom;
    }
    curr->linkDown(this);
    m_header->incrementSize();
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

int Node::getI() const
{
    return m_i;
}

int Node::getJ() const
{
    return m_j;
}

int Node::getVal() const
{
    return m_val;
}

//-------------------------------------------- Column Header --------------------------------------------------//

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

DancingLinksGrid::DancingLinksGrid(const Grid& grid) : DancingLinksGrid(grid.getSideLen(), grid.getSubGridRows(), grid.getSubGridCols()) 
{
}

DancingLinksGrid::DancingLinksGrid(int sideLen) : DancingLinksGrid(sideLen, sqrt(sideLen), sqrt(sideLen))
{
    assert(isPerfectSquare(sideLen));
}

DancingLinksGrid::DancingLinksGrid(int sideLen, int subGridRows, int subGridCols)
{
    assert(subGridRows*subGridCols == sideLen);

    m_sudokuSideLen = sideLen;
    m_sudokuSubGridCols = subGridRows;
    m_sudokuSubGridRows = subGridCols;

    int colLen = 4 * m_sudokuSideLen * m_sudokuSideLen;
    int nodesLen = colLen * m_sudokuSideLen;
    

    // Fill the column header list
    m_headers.reserve(colLen);
    m_headers.push_back(new ColumnHeader());
    m_root.linkRight(m_headers[0]);
    for(int i = 1; i < colLen; ++i)
    {
        m_headers.push_back(new ColumnHeader());
        m_headers[i-1]->linkRight(m_headers[i]);
    }

    // Fill the node list
    m_nodes.reserve(nodesLen);
    for(int i = 0; i < m_sudokuSideLen; ++i)
    {
        for(int j = 0; j < m_sudokuSideLen; ++j)
        {
            for(int k = 1; k <= m_sudokuSideLen; ++k)
            {
                addGridRowNodes(i, j, k);
            }
        }
    }
}

DancingLinksGrid::~DancingLinksGrid()
{
    for(int i = 0; i < m_headers.size(); ++i)
    {
        delete m_headers[i];
    }

    for(int i = 0; i < m_nodes.size(); ++i)
    {
        delete m_nodes[i];
    }
}

void DancingLinksGrid::getHeaderIndexes(int i, int j, int val, std::array<int, 4>& cols) const
{
    int subGridIndex = i / m_sudokuSubGridRows * m_sudokuSubGridRows + j / m_sudokuSubGridCols;
    int columnGridSectionLen = m_sudokuSideLen * m_sudokuSideLen; 

    cols[0] = i * m_sudokuSideLen + j; 
    cols[1] = columnGridSectionLen + (i * m_sudokuSideLen + (val - 1));
    cols[2] = columnGridSectionLen * 2 + (j * m_sudokuSideLen + (val - 1));
    cols[3] = columnGridSectionLen * 3 + (subGridIndex * m_sudokuSideLen + (val - 1));
}



void DancingLinksGrid::addGridRowNodes(int i, int j, int val)
{
    std::array<int, 4> headerIndexes;
    getHeaderIndexes(i, j, val, headerIndexes);
    m_nodes.push_back(new Node(i, j, val));
    int index = m_nodes.size() - 1;
    m_nodes[index]->linkToColumn(m_headers[headerIndexes[0]]);

    for(int k = 1; k < 4; ++k)
    {
        m_nodes.push_back(new Node(i, j, k));
        m_nodes[index]->linkRight(m_nodes[index + 1]);
        ++index;
        m_nodes[index]->linkToColumn(m_headers[headerIndexes[k]]);
    }
}