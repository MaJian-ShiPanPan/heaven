/**
 * 题目链接：
 *  https://leetcode.cn/problems/longest-palindromic-substring/
 * 
 * 知识点：
 *  动态规划
 *      状态：dp[l][r] ---> 表示从l到r上是否为回文数。
 *      状态转移方程：
 *          dp[l][r] = true; (dp[l + 1][r - 1] == true || r - l + 1 <= 2) && (s[l] == s[r])
 *          dp[l][r] = false; else;
 *      边界条件：
 *          dp[i][i] = true;
 *          
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
        for(int r = 1; r < s.size(); ++r)
        {
            for(int l = 0; l < r; ++l)
            {
                dp[l][r] = false; // 需要赋值一下，不然就是随机值。
                if((s[l] == s[r]) && ((r - l <= 2) || (dp[l + 1][r - 1] == true)))
                {
                    dp[l][r] = true;
                    if(r - l + 1 > iMaxLength)
                    {
                        iStart = l;
                        iEnd = r;
                        iMaxLength = r - l + 1;
                        std::cout << iStart << " " << iEnd << " " << s.substr(iStart, iMaxLength) << std::endl;
                    }
                }
                std::cout << "l: " << l << ", r:" << r
                    << ", s[l]: " << s[l] << ", s[r]: " << s[r] << ", dp[l][r]: " << dp[l][r] << std::endl; 
            }
        }
        return s.substr(iStart, iMaxLength);
    }
};

int main(int argc, char* argv[])
{

    std::string s = "aacabdkacaa";
    Solution solution;
    std::cout << solution.longestPalindrome(s) << std::endl;
    return 0;
}