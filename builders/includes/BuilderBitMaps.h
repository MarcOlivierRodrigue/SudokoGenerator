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
    virtual bool isSquareLegal(const Grid& grid, int m_i, int m_j, int i, int j, int val) const override;
    virtual void cancelPlacement(Grid& grid, int i, int j) override;
    virtual void placeValue(Grid& grid, int i, int j, int val) override;  
private: 
    inline int getSubGridIndex(int i, int j, int subGridRows, int subGridCols) const;
    std::vector<int> m_subGridsBM;
    std::vector<int> m_rowsBM;
    std::vector<int> m_colsBM;
};
