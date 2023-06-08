#include "Grid.h"
#include "DancingLinksGrid.h"

//-------------------------------------------- Row Info -----------------------------------------------//

RowInfo::RowInfo(int i, int j, int val) : m_row(i), m_col(j), m_val(val)
{}

int RowInfo::getRow() const
{
    return m_row;
}

int RowInfo::getCol() const
{
    return m_col;
}

int RowInfo::getVal() const
{
    return m_val;
}

//-------------------------------------------- Node --------------------------------------------------//


Node::Node() : m_rowInfo(nullptr)
{
    m_bottom = this;
    m_top = this;
    m_left = this;
    m_right = this;
}

Node::Node(RowInfo* rowInfo) : m_rowInfo(rowInfo)
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

DancingLinksGrid::DancingLinksGrid(const Grid& grid)
{
    m_sudokuSideLen = grid.getSideLen();
    m_sudokuSubGridCols = grid.getSubGridCols();
    m_sudokuSubGridRows = grid.getSubGridRows();

    int colLen = 4 * m_sudokuSideLen * m_sudokuSideLen;
    int rowInfoLen = m_sudokuSideLen * m_sudokuSideLen * m_sudokuSideLen;
    int nodesLen = rowInfoLen * 4;
    

    // Fill the column header list
    m_headers.reserve(colLen);
    m_headers.push_back(new ColumnHeader());
    m_root.linkRight(m_headers[0]);
    for(int i = 1; i < colLen; ++i)
    {
        m_headers.push_back(new ColumnHeader());
        m_headers[i-1]->linkRight(m_headers[i]);
    }

    // Fill the row info list
    m_rowInfos.reserve(rowInfoLen);
    for(int i = 0; i < m_sudokuSideLen; ++i)
    {
        for(int j = 0; j < m_sudokuSideLen; ++j)
        {
            for(int k = 1; k <= m_sudokuSideLen; ++k)
            {
                m_rowInfos.push_back(new RowInfo(i, j, k));
            }
        }
    }

    // Create the row info list
    m_nodes.reserve(nodesLen);
    std::array<int, 4> headerIndexes; 
    for(int i = 0; i < rowInfoLen; ++i)
    {
        getHeaderIndexes(m_rowInfos[i], headerIndexes);
        m_nodes.push_back(new Node(m_rowInfos[i]));
        m_nodes[i*4]->linkToColumn(m_headers[headerIndexes[0]]);

        for(int j = 1; j < 4; ++j)
        {
            int newNodeIndex = i * 4 + j;
            m_nodes.push_back(new Node(m_rowInfos[i]));
            m_nodes[newNodeIndex - 1]->linkRight(m_nodes[newNodeIndex]);
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

    for(int i = 0; i < m_rowInfos.size(); ++i)
    {
        delete m_rowInfos[i];
    }
}

void DancingLinksGrid::getHeaderIndexes(const RowInfo* const rowInfo, std::array<int, 4>& cols) const
{
    int i = rowInfo->getRow();
    int j = rowInfo->getCol();
    int val = rowInfo->getVal();
    
    int subGridIndex = i / m_sudokuSubGridRows * m_sudokuSubGridRows + j / m_sudokuSubGridCols;
    int columnGridSectionLen = m_sudokuSideLen * m_sudokuSideLen; 

    cols[0] = i * m_sudokuSideLen + j; 
    cols[1] = columnGridSectionLen + (i * m_sudokuSideLen + (val - 1));
    cols[2] = columnGridSectionLen * 2 + (j * m_sudokuSideLen + (val - 1));
    cols[3] = columnGridSectionLen * 3 + (subGridIndex * m_sudokuSideLen + (val - 1));
}