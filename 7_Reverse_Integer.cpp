#include <iostream>
#include <string>

/**
 * @brief The Solution class
    Given a 32-bit signed integer, reverse digits of an integer.

    Example 1:

    Input: 123
    Output: 321
    Example 2:

    Input: -123
    Output: -321
    Example 3:

    Input: 120
    Output: 21
    Note:
    Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1].
    For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
 */

class Solution {
public:
    int reverse(int x) {
         const int TIMES = 10;
         int res = 0;
         bool isneg = (x > 0 ? false : true);
         x = abs(x);
         while(x >= TIMES)
         {
             res = res * 10 + x % TIMES;
             x /= TIMES;
         }
         int temp = res * 10 + x % TIMES;
         res = ((temp >> 30) >= (res >> 29) ? temp : 0);
         if(isneg && res != 0)
             res = (~res) + 1;
         return res;
     }

     void test(int num)
     {
         std::cout << num << "->" << reverse(num) << std::endl;
     }
};

int main()
{
    int num = -121;//123,-123,120,1534236469
    Solution example;
    example.test(num);//321,-321,21,0
    return 0;
}
