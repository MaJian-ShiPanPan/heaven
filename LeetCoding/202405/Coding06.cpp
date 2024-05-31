/**
 * 题目链接：
 *  https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/?envType=study-plan-v2&envId=top-interview-150
 * 
 * 知识点：
 *  N.A.
 * 
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 思路：最优方案，相当于从后向前看。
    int maxProfit(vector<int>& prices)
    {
        if(prices.size() < 2)
        {
            return 0;
        }

        int iMax = 0;
        int lowest = prices[0];
        for(int i = 1; i < prices.size(); ++i)
        {
            if(prices[i] - lowest > iMax)
            {
                iMax = prices[i] - lowest;
            }
            else if(prices[i] < lowest)
            {
                lowest = prices[i];
            }
        }
        return iMax;
    }

    // 思想：找前后两天直接的变化值。
    int maxProfit02(vector<int>& prices) {
        int iMax = 0;
        int iLocalMax = 0;
        for(int i = 1; i < prices.size(); ++i)
        {
            iLocalMax = iLocalMax + (prices[i] - prices[i - 1]);
            if(iLocalMax > iMax)
                iMax = iLocalMax;
            else if(iLocalMax < 0)
            {
                iLocalMax = 0;
            }
        }
        return iMax;
    }


    // 下面方法会超出时间限制
    int maxProfit01(vector<int>& prices) {
        int iMax = 0;
        for(int i = 0; i < prices.size() - 1; ++i)
        {
            for(int j = i + 1; j < prices.size(); ++j)
            {
                if((prices[j] - prices[i]) > iMax)
                    iMax = prices[j] - prices[i];
            }
        }
        return iMax;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> prices = {7,1,5,3,6,4};
    Solution solution;
    std::cout << solution.maxProfit(prices) << std::endl;
    return 0;
}