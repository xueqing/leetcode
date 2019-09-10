#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

/**
 * @brief The Solution class
    Write a function to find the longest common prefix string amongst an array of strings.

    If there is no common prefix, return an empty string "".

    Example 1:

    Input: ["flower","flow","flight"]
    Output: "fl"
    Example 2:

    Input: ["dog","racecar","car"]
    Output: ""
    Explanation: There is no common prefix among the input strings.
    Note:

    All given inputs are in lowercase letters a-z.
 */

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        size_t len = strs.size(), minlen=INT_MAX;
        if(len == 0) return "";
        if(len == 1) return strs.at(0);
        for(size_t i=0; i<len; i++)
            minlen=std::min(minlen, strs.at(i).size());
        size_t index=0;
        for(; index<minlen; index++)
        {
            for(size_t j=1; j<len; j++)
            {
                if(strs.at(j).at(index) != strs.at(0).at(index))
                    return strs.at(j).substr(0, index);
            }
        }
        return strs.at(0).substr(0, index);
    }

    void test(std::vector<std::string> &strs, std::string &ans)
    {
        std::string res = longestCommonPrefix(strs);
        std::cout << res << (ans == res ? " == " : " != ") << ans << ":";
        for(size_t i=0; i<strs.size(); i++)
            std::cout << strs.at(i) << " ";
        std::cout << std::endl;
    }
};

int main()
{
    std::vector<std::vector<std::string>> strs = {{"flower","flow","flight"}, {"dog","racecar","car"}, {"a"},{"c","c"}};
    std::vector<std::string> ans = {"fl","","a","c"};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(strs.at(i), ans.at(i));
    }
    return 0;
}
