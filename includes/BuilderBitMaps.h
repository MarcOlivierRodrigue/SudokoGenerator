#pragma once
#include "Builder.h"
#include <vector>


class BuilderBitMaps : public Builder
{
public:
    BuilderBitMaps();
    ~BuilderBitMaps();
    virtual void fillSudoku(Grid& grid) override;
protected:
    virtual bool isSquareLegal(const Grid& grid, int m_i, int m_j, int i, int j, int val) const override;
    virtual void cancelPlacement(Grid& grid, int i, int j) override;
    virtual void placeValue(Grid& grid, int i, int j, int val) override;  
private: 
    void initBitMaps(const Grid& grid);
    inline int getSubGridIndex(int i, int j, int subGridRows, int subGridCols) const;
    std::vector<int> m_subGridsBM;
    std::vector<int> m_rowsBM;
    std::vector<int> m_colsBM;
};
