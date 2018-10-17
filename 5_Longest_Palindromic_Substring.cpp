#include <iostream>
#include <string>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        std::string res;
        if(s.empty())
            return res;
        res = s.substr(0,1);
        size_t len = s.length(), sindex=0;
        for(sindex=0; sindex<len; sindex++)
        {
            size_t start = sindex, end=0, reslen = 0;
            size_t eindex = s.find_last_of(s.at(start));
            for(end=eindex; end>=start;)
            {
                if(s.at(start) == s.at(end))
                {
                    if(start == end || start + 1 == end)
                    {
                        reslen = ((start - sindex) << 1) + 1 + end - start;
                        if(reslen > res.length())
                            res = s.substr(sindex, reslen);
                        break;
                    }
                    start++;
                    end--;
                }
                else
                {
                    start = sindex;
                    eindex = s.find_last_of(s.at(start), eindex-1);
                    end = eindex;
                }
            }
        }
        return res;
    }

    void test(std::string &str)
    {
        std::cout << str << "->" << longestPalindrome(str) << std::endl;
    }
};

int main()
{
    std::string str = "aaabaaaa";//"babad";//"cbbd"//"a"//"bb"//"aaabaaaa"
    Solution example;
    example.test(str);
    return 0;
}
