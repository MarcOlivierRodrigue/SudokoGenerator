#include "gtest/gtest.h"
#include "DancingLinksGrid.h"
#include "Grid.h"

TEST(DancingLinksGrid, constructor)
{

}

TEST(DancingLinksGrid, getHeaderIndexes)
{
    DancingLinksGrid dLG(9);
    std::array<int, 4> res;

    dLG.getHeaderIndexes(0, 0, 1, res);
    EXPECT_EQ(0, res[0]);
    EXPECT_EQ(81, res[1]);
    EXPECT_EQ(162, res[2]);
    EXPECT_EQ(243, res[3]);

    dLG.getHeaderIndexes(8, 8, 9, res);
    EXPECT_EQ(80, res[0]);
    EXPECT_EQ(161, res[1]);
    EXPECT_EQ(242, res[2]);
    EXPECT_EQ(323, res[3]);

    dLG.getHeaderIndexes(4, 5, 6, res);
    EXPECT_EQ(41, res[0]);
    EXPECT_EQ(122, res[1]);
    EXPECT_EQ(212, res[2]);
    EXPECT_EQ(284, res[3]);
}