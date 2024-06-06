/**
 * 题目链接：
 *  https://leetcode.cn/problems/longest-palindromic-substring/
 * 
 * 知识点：
 *  动态规划
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        bool dp[s.size()][s.size()];
        int iMaxLength = 1;
        int iStart = 0;
        int iEnd = 0;
        for(int r = 0; r < s.size(); ++r)
        {
            for(int l = 0; l < r; ++l)
            {
                if((s[l] == s[r]) && ((r - l <= 2) || (dp[l + 1][r - 1] == true)))
                {
                    dp[l][r] = true;
                    if(r - l + 1 > iMaxLength)
                    {
                        iStart = l;
                        iEnd = r;
                        iMaxLength = r - l + 1;
                        std::cout << iStart << " " << iEnd << " " << s.substr(iStart, iEnd) << std::endl;
                    }
                }
            }
        }
        return s.substr(iStart, iMaxLength);
    }
};

int main(int argc, char* argv[])
{

    std::string s = "abacbcad";
    Solution solution;
    std::cout << solution.longestPalindrome(s) << std::endl;
    return 0;
}