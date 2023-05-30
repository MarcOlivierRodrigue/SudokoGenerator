#include "Util.h"
#include "gtest/gtest.h"
#include <limits.h>

TEST(Util, handleNegative)
{
    EXPECT_FALSE(isPerfectSquare(-9));
    EXPECT_TRUE(isPerfectSquare(9));
}

TEST(Util, selectRandomNum)
{
    int r = 0;

    for(int i = 0; i < 1000; ++i)
    {
        r = selectRandomNum(9);
        EXPECT_LE(1, r);
        EXPECT_LE(r, 9);
    }
}
