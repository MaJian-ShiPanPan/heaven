/**
 * 题目连接：
 *      https://leetcode.cn/problems/merge-sorted-array/?envType=study-plan-v2&envId=top-interview-150
 * 
 * 知识点：
 *      排序
*/

#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int mPos = 0;
        int nPos = 0;
        vector<int> result = {};
        while((mPos < m) && (nPos < n))
            result.push_back((nums1[mPos] < nums2[nPos]) ? nums1[mPos++] : nums2[nPos++]);

        while(mPos < m)
            result.push_back(nums1[mPos++]);

        while(nPos < n)
            result.push_back(nums2[nPos++]);

        nums1.clear();
        nums1 = result;
    }
};

int main()
{
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {2, 5, 6};
    int n =3;

    Solution solution;
    solution.merge(nums1, m, nums2, n);


    for(auto& e: nums1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    return 0;
}