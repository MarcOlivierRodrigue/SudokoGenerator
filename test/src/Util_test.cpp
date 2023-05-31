#include "Util.h"
#include "gtest/gtest.h"
#include <limits.h>
#include <set>
#include <vector>

TEST(Util, isPerctSquare)
{
    bool res = true;
    std::vector<int> perfectSquares = {
        0,1,4,9,16,
        25,36,49,64,81,
        100,121,144,169,196,
        225,256,289,324,361,
        400,441,484,529,576,
        625,676,729,784,841,
        900,961,1024
    };
    std::set<int>perfectSquareSet(perfectSquares.begin(), perfectSquares.end());

    for(int i = 0; i <= perfectSquares[perfectSquares.size()-1]; ++i)
    {
        if(isPerfectSquare(i) != perfectSquareSet.count(i))
        {
            res = false; 
            break;
        }
    }
    EXPECT_TRUE(res);
}

TEST(Util, isPerfectSquare_handleNegative)
{
    EXPECT_FALSE(isPerfectSquare(-9));
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
