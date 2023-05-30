#pragma once
#include "Grid.h"

class Grid_test : public Grid
{
public:
    Grid_test(int sideLen);
    ~Grid_test();
    int* getData_test();
private:
    Grid_test();
};
