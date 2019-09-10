#include <iostream>
#include <string>

/**
 * @brief The Solution class
    Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

    Example 1:

    Input: 121
    Output: true
    Example 2:

    Input: -121
    Output: false
    Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
    Example 3:

    Input: 10
    Output: false
    Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 */

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 10 && x >= 0)
            return true;
        if(x < 0 || x % 10 == 0)
            return false;
        int reverse = 0, temp = x;
        while(temp>0)
        {
            reverse = reverse * 10 + temp % 10;
            temp /= 10;
        }
        return (reverse == x);
    }

    void test(int num, std::string ans)
    {
        std::string res = (isPalindrome(num) ? "true" : "false");
        std::cout << num << "->" << ans << (res == ans ? "==" : "!=") << res << std::endl;
    }
};

int main()
{
    int nums[] = {121,-121,10};
    char strs[][10] = {"true","false","false"};
    for(size_t i=0; i<sizeof(nums)/sizeof(int); i++)
    {
        Solution example;
        example.test(nums[i], strs[i]);
    }
    return 0;
}
