/**
 * 题目链接：
 *  https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/?envType=study-plan-v2&envId=top-interview-150
 * 知识点：
 *  N.A.
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() < 2)
        {
            return 0;
        }
        int iSize = prices.size();
        int dpArr[iSize][iSize];

        for(int i = 0; i < iSize; i++)
        {
            for(int j = 0; j < iSize; ++j)
            {
                
            }
        }
        return 0;
    }
};


int main()
{
    Solution solution;
    vector<int> prices = {7,1,5,3,6,4};

    cout << solution.maxProfit(prices) << std::endl;
    return 0;
}