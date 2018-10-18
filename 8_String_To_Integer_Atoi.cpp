#include <iostream>
#include <string>

/**
 * @brief The Solution class
    Implement atoi which converts a string to an integer.

    The function first discards as many whitespace characters as necessary until the first non-whitespace character is found.
    Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits
    as possible, and interprets them as a numerical value.
    The string can contain additional characters after those that form the integral number, which are ignored and have no
    effect on the behavior of this function.
    If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists
    because either str is empty or it contains only whitespace characters, no conversion is performed.
    If no valid conversion could be performed, a zero value is returned.

    Note:
    Only the space character ' ' is considered as whitespace character.
    Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1].
    If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
    Example 1:

    Input: "42"
    Output: 42
    Example 2:

    Input: "   -42"
    Output: -42
    Explanation: The first non-whitespace character is '-', which is the minus sign.
                 Then take as many numerical digits as possible, which gets 42.
    Example 3:

    Input: "4193 with words"
    Output: 4193
    Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
    Example 4:

    Input: "words and 987"
    Output: 0
    Explanation: The first non-whitespace character is 'w', which is not a numerical
                 digit or a +/- sign. Therefore no valid conversion could be performed.
    Example 5:

    Input: "-91283472332"
    Output: -2147483648
    Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
                 Thefore INT_MIN (−231) is returned.
 */

class Solution {
public:
    int myAtoi(std::string str) {
        int num=0, ch=0;
        size_t start=0, end=0, len=str.length();
        for(start=0; start<len; start++)
        {
            if(str.at(start) == ' ')
                continue;
            if((str.at(start)<'0' || str.at(start)>'9')
                    && str.at(start) != '-'
                    && str.at(start) != '+')
                return 0;
            break;
        }
        if(start >= len)
            return 0;
        bool isneg = (str.at(start) == '-');
        start += (str.at(start) == '-' || str.at(start) == '+');

        bool nonZero = false;
        for(end=start; end<len; end++)
        {
            if((str.at(end)<'0' || str.at(end)>'9'))
                break;
            if(str.at(end) == '0' && !nonZero)
            {
                start++;
                continue;
            }
            nonZero = true;
        }
        if(end == start)
            return 0;

        if(isneg && (end - start > 10
                || (end - start == 10 && str.substr(start, end)>="2147483648")))
            return -2147483648;
        if(!isneg && (end - start > 10
                || (end - start == 10 && str.substr(start, end)>="2147483647")))
            return 2147483647;

        for(num=0; start<end; start++)
        {
            ch = str.at(start) - '0';
            num = num * 10 + ch;
        }
        if(isneg)
        {
            num = ((num == 0) ? 0 : ~num + 1);
        }
        return num;
    }

    void test(std::string &str)
    {
        std::cout << str << "->" << myAtoi(str) << std::endl;
    }
};

int main()
{
    std::string str = "-2147483647";//"42","-42","4193 with words","words and 987","-91283472332",""," ","+1","2147483648","-000000000000001","-2147483647"
    Solution example;
    example.test(str);//42,-42,4193,0,-2147483648,0,0,1,-2147483648,-1,-2147483647
    return 0;
}
