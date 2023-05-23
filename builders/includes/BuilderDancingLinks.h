#pragma once
#include "BuilderBase.h"

class Link;

class BuilderDancingLinks : public BuilderBase
{
public:
    BuilderDancingLinks();
    ~BuilderDancingLinks();
    virtual void fillSudoku(Grid& grid) override;
protected:
private:
};
