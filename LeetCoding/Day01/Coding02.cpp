/**
 * 题目链接：
 *      https://leetcode.cn/problems/remove-element/description/?envType=study-plan-v2&envId=top-interview-150
 * 
 * 知识点：
 *      N.A
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.empty())
        {
            return 0;
        }

        int iRealPos = 0;
        int iCurrentPos = 0;

        for(int i = 0; i < nums.size(); i++)
        {
            if(val == nums[i])
            {
                continue;
            }
            else
            {
                nums[iRealPos++] = nums[i];
            }
        }
        return iRealPos;
    }
};

int main()
{
    vector<int> nums = {3, 2, 2, 3};
    int val = 3;
    Solution solution;
    int number = solution.removeElement(nums, val);
    std::cout << "number: " << number << std::endl;
    for(int i = 0; i < number; i++)
    {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}