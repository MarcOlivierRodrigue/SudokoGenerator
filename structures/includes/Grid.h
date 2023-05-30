#pragma once
#include "Types.h"

class Grid
{
public:
    Grid(sg_uint sideLen);
    Grid(sg_uint sideLen, sg_uint subGridRows, sg_uint subGridCols);
    Grid(const Grid& grid);
    ~Grid();
    sg_uint& operator() (sg_uint i, sg_uint j);
    const sg_uint& operator() (sg_uint i, sg_uint j) const;
    sg_uint getSideLen() const;
    sg_uint getSubGridRows() const;
    sg_uint getSubGridCols() const; 
    sg_uint getSubGridXIndex(sg_uint j) const;
    sg_uint getSubGridYIndex(sg_uint i) const;
    sg_uint getSubGridXMargin(sg_uint j) const;
    sg_uint getSubGridYMargin(sg_uint i) const;
    void empty();
private:
    Grid();
    const sg_uint m_sideLen;
    const sg_uint m_subGridRows;
    const sg_uint m_subGridCols;
    sg_uint* m_data;
};
