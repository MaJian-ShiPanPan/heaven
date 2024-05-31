/**
 * 题目链接：
 *      https://leetcode.cn/problems/remove-duplicates-from-sorted-array/?envType=study-plan-v2&envId=top-interview-150
 * 
 * 知识点：
 *      N.A.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
        {
            return 0;
        }

        vector<int> result;
        result.push_back(nums[0]);
        int iIndex = 1;
        for(int i = 1; i < nums.size(); i++)
        {
            ++iIndex;
            if((iIndex <= 2) && (result[result.size() - 1] == nums[i]))
            {
                result.push_back(nums[i]);
            }
            else if((result[result.size() - 1] != nums[i]))
            {
                result.push_back(nums[i]);
                iIndex = 1;
            }
        }
        nums = result;
        return nums.size();
    }
};

int main(int argc, char* argv[])
{
    Solution solution;
    vector<int> nums = {0, 0, 1, 1, 1, 1, 2, 3, 3};
    solution.removeDuplicates(nums);
    for(auto& e: nums)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    return 0;
}