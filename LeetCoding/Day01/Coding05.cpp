/**
 * 题目链接：
 *      https://leetcode.cn/problems/rotate-array/description/?envType=study-plan-v2&envId=top-interview-150
 * 
 * 知识点：
 *      N.A
*/
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> vecResult;
        int iOffset = k % nums.size();
        for(int i = nums.size() - iOffset; i < nums.size(); i++)
        {
            vecResult.push_back(nums[i]);
        }
        for(int i = 0; i < nums.size() - iOffset; ++i)
        {
            vecResult.push_back(nums[i]);
        }
        nums = vecResult;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {-1,-100,3,99};
    int k = 2;
    solution.rotate(nums, k);

    for(auto& e: nums)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    return 0;
}