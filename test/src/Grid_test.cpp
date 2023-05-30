#include "gtest/gtest.h"
#include "Grid_test.h"

Grid_test::Grid_test(int sideLen) : Grid(sideLen)
{
}

int* Grid_test::getData_test()
{
    return getData();
}


TEST(Grid, constructor)
{
    Grid g(9);
    EXPECT_EQ(9, g.getSideLen());
    EXPECT_EQ(3, g.getSubGridCols());
    EXPECT_EQ(3, g.getSubGridRows());
}