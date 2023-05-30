#include "Util.h"
#include <assert.h>
#include <random>
#include <chrono>

int selectRandomNum(int max)
{
    assert(max >= 1);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    return rand() % max + 1;
}

bool isPerfectSquare(int num)
{
    if(num < 0)
    {
        return false;
    }
    double sqrtNum = (double)sqrt(num);
    return ceil(sqrtNum) == floor(sqrtNum);
}