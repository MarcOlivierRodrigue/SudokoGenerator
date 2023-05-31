#include "Util.h"
#include "gtest/gtest.h"
#include <limits.h>
#include <set>
#include <vector>
#include <iostream>

TEST(Util, isPerctSquare)
{
    bool res = true;
    std::vector<int> perfectSquares;
    
    for(int i = 0; i < 1000; ++i)
    {
        int mult = i*i;
        if(mult >= 0)
        {
            perfectSquares.push_back(mult);
        }
        else
        {
            break;
        }
    }

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
