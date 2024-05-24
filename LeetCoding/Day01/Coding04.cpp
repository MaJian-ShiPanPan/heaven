/**
 * 题目链接：
 *      https://leetcode.cn/problems/majority-element/?envType=study-plan-v2&envId=top-interview-150
 * 
 * 知识点：
 *      N.A.
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> mapRecord;
        for(auto& e: nums)
        {
            if(mapRecord.end() != mapRecord.find(e))
            {
                mapRecord[e]++;
            }
            else
            {
                mapRecord[e] = 1;
            }
        }


        for(auto& e: mapRecord)
        {
            if(e.second >= (nums.size() / 2) + 1)
            {
                return e.first;
            }
        }
        return 0;
    }
};


int main()
{
    Solution solution;
    vector<int> nums = {2,2,1,1,1,2,2};
    std::cout << solution.majorityElement(nums) << std::endl;
    return 0;
}