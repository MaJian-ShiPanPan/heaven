/**
 * 知识点
 * 	递归
 * 
 * 题目1：求数组arr[L..R]上最大值，用递归
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>

int FindMaxValueByRecu(std::vector<int>& vec, int L, int R)
{
    int iMax = INT_MIN;

    if(vec.empty())
    {
        return iMax;
    }

    if(L == R)
    {
        return vec[L];
    }
    int mid = L + (R - L) >> 1;
    int iMaxLeft = FindMaxValueByRecu(vec, L, mid);
    if(iMaxLeft > iMax) iMax = iMaxLeft;
    int iMaxReght = FindMaxValueByRecu(vec, mid, R);
    if(iMaxReght > iMax) iMax = iMaxReght;
    return iMax;
}

int FindMaxValueByMyself(std::vector<int>& vec)
{
    if(vec.empty())
    {
        return -1;
    }

    int iMax = INT_MIN;
    for(auto& e: vec)
    {
        if(e > iMax)
        {
            iMax = e;
        }
    }
    return iMax;
}

int FindMaxValue(std::vector<int>& vec)
{
    return 0;
}

std::vector<int> generateRandomArray(const int iMaxLength, const int iMaxValue)
{
    std::vector<int> vec;
    int iLength = rand() % (iMaxLength + 1);
    for(int i = 0; i < iLength; ++i)
    {
        vec.push_back((rand() % (iMaxValue + 1)) - (rand() % (iMaxValue + 1)));
    }
    return vec;
}

void CheckResultByFindMaxValueByMyself(const int iLoopCount, const int iMaxLength, const int iMaxValue)
{
    for(int i = 0; i < iLoopCount; ++i)
    {
        std::vector<int> vec = generateRandomArray(iMaxLength, iMaxValue);
        int iMaxValueByFindMaxValueByMyself = FindMaxValueByMyself(vec);
        int iMaxValueByFindMaxValueByRecu = FindMaxValueByRecu(vec, 0, vec.size() - 1);
        if(iMaxValueByFindMaxValueByMyself == iMaxValueByFindMaxValueByRecu)
        {
            std::cout << "Check result success;" << std::endl;
        }
        else
        {
            std::cout << "Check result Failed, iMaxValueByFindMaxValueByMyself: " << iMaxValueByFindMaxValueByMyself
                << ", iMaxValueByFindMaxValueByRecu: " << iMaxValueByFindMaxValueByRecu 
                << std::endl;
        }
    }
}

int main()
{
    const int kiMaxLength = 100;
    const int kiLoopCount = 100;
    const int kiMaxValue = 100000;
    CheckResultByFindMaxValueByMyself(kiLoopCount, kiMaxLength, kiMaxValue);
    return EXIT_SUCCESS;
}