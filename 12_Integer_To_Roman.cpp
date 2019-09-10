#include <iostream>
#include <string>

/**
 * @brief The Solution class
    Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

    Symbol       Value
    I             1
    V             5
    X             10
    L             50
    C             100
    D             500
    M             1000
    For example, two is written as II in Roman numeral, just two one's added together.
    Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

    Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII.
    Instead, the number four is written as IV. Because the one is before the five we subtract it making four.
    The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

    I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.
    Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

    Example 1:

    Input: 3
    Output: "III"
    Example 2:

    Input: 4
    Output: "IV"
    Example 3:

    Input: 9
    Output: "IX"
    Example 4:

    Input: 58
    Output: "LVIII"
    Explanation: L = 50, V = 5, III = 3.
    Example 5:

    Input: 1994
    Output: "MCMXCIV"
    Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 */

using namespace std;

class Solution {
public:
    std::string intToRoman(int num) {
        std::string res;
        std::vector<int> base={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        std::vector<std::string> sign={"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        int times = 0;
        size_t len=base.size();
        for(size_t i=0; i<len; i++)
        {
            times = num/base[i];
            while(times > 0)
            {
                res.append(sign.at(i));
                times--;
            }
            num %= base[i];
        }
        return res;
    }

    void test(int num, std::string ans)
    {
        std::string res = intToRoman(num);
        std::cout << res << (ans == res ? " == " : " != ") << ans << ":" << num << std::endl;
    }
};

int main()
{
    size_t len = 5;
    int num[] = {3,4,9,58,1994};
    char str[][10] = {"III","IV","IX","LVIII","MCMXCIV"};
    for(size_t i=0; i<len; i++)
    {
        Solution example;
        example.test(num[i], str[i]);
    }
    return 0;
}
