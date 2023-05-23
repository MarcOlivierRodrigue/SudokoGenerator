#include "Util.h"
#include <random>
#include <chrono>

int selectRandomNum(int max)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    return rand() % max + 1;
}

bool isPerfectSquare(int num)
{
    double sqrtNum = (double)sqrt(num);
    return ceil(sqrtNum) == floor(sqrtNum);
}