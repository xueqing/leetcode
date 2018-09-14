#include <iostream>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        size_t len = 0;
        std::string substr;
        for(size_t i = 0, j = 0; i<s.length(); i++)
        {
            for(j = i; j<s.length(); j++)
            {
                if(substr.find(s.at(j)) != std::string::npos)
                {
                    len = std::max(len, substr.length());
                    substr.clear();
                    break;
                }
                substr.push_back(s[j]);
            }
        }
        len = std::max(len, substr.length());
        return len;
    }

    void test()
    {
        std::string s("abcabcbb");//bbbbb,dvdf,abcabcbb
        std::cout << lengthOfLongestSubstring(s) << std::endl;
    }
};

int main()
{
    Solution example;
    example.test();
    return 0;
}
