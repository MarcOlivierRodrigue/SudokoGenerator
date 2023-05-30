#pragma once
#include "BuilderBase.h"
#include <vector>


class BuilderBitMaps : public BuilderBase
{
public:
    BuilderBitMaps();
    ~BuilderBitMaps();
    virtual void fillSudoku(Grid& grid) override;
protected:
    void initBitMaps(const Grid& grid);
    virtual bool isSquareLegal(const Grid& grid, sg_uint m_i, sg_uint m_j, sg_uint i, sg_uint j, sg_uint val) const override;
    virtual void cancelPlacement(Grid& grid, sg_uint i, sg_uint j) override;
    virtual void placeValue(Grid& grid, sg_uint i, sg_uint j, sg_uint val) override;  
private: 
    inline int getSubGridIndex(sg_uint i, sg_uint j, sg_uint subGridRows, sg_uint subGridCols) const;
    std::vector<sg_uint> m_subGridsBM;
    std::vector<sg_uint> m_rowsBM;
    std::vector<sg_uint> m_colsBM;
};
