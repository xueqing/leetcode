#include <iostream>
#include <string>

/**
 * @brief The Solution class
    The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

    P   A   H   N
    A P L S I I G
    Y   I   R
    And then read line by line: "PAHNAPLSIIGYIR"

    Write the code that will take a string and make this conversion given a number of rows:

    string convert(string s, int numRows);
    Example 1:

    Input: s = "PAYPALISHIRING", numRows = 3
    Output: "PAHNAPLSIIGYIR"
    Example 2:

    Input: s = "PAYPALISHIRING", numRows = 4
    Output: "PINALSIGYAHRPI"
    Explanation:

    P     I    N
    A   L S  I G
    Y A   H R
    P     I
 */

class Solution {
public:
    std::string convert(std::string s, int numRows) {
        std::string res;
        if(s.length() <= numRows || numRows == 1)
            return s;
        size_t len = s.length();
        int circle = (numRows - 1) << 1;
        size_t times = len / circle;
        numRows--;
        for(size_t i=0; i<=times; i++)
        {
            res.push_back(s.at(i * circle));
        }
        for(size_t j=1, index=0; j<numRows; j++)
        {
            for(size_t i=0; i<=times; i++)
            {
                index = i * circle + j;
                if(index < len)
                {
                    res.push_back(s.at(index));
                }
                index = (i + 1) * circle - j;
                if(index < len)
                {
                    res.push_back(s.at(index));
                }
            }
        }
        for(size_t i=0; i<times; i++)
        {
            res.push_back(s.at(i * circle + numRows));
        }
        if(times * circle + numRows < len)
            res.push_back(s.at(times * circle + numRows));
        return res;
    }

    void test(std::string &str, int numRows)
    {
        std::cout << str << "->" << convert(str, numRows) << std::endl;
    }
};

int main()
{
    std::string str = "ABCD";//"PAYPALISHIRING";//"ABCD"
    int numRows = 2;//3//4//2
    Solution example;
    example.test(str, numRows);//"PAHNAPLSIIGYIR"//"PINALSIGYAHRPI"//"ACBD"
    return 0;
}
