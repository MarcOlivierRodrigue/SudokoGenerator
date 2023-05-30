#include "Util.h"
#include "gtest/gtest.h"

TEST(Util, handleNegative)
{
    EXPECT_EQ(false, isPerfectSquare(-5));
}

