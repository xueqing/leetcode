#include <iostream>
#include <string>

/**
 * @brief The Solution class
    Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

    '.' Matches any single character.
    '*' Matches zero or more of the preceding element.
    The matching should cover the entire input string (not partial).

    Note:

    s could be empty and contains only lowercase letters a-z.
    p could be empty and contains only lowercase letters a-z, and characters like . or *.
    Example 1:

    Input:
    s = "aa"
    p = "a"
    Output: false
    Explanation: "a" does not match the entire string "aa".
    Example 2:

    Input:
    s = "aa"
    p = "a*"
    Output: true
    Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
    Example 3:

    Input:
    s = "ab"
    p = ".*"
    Output: true
    Explanation: ".*" means "zero or more (*) of any character (.)".
    Example 4:

    Input:
    s = "aab"
    p = "c*a*b"
    Output: true
    Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".
    Example 5:

    Input:
    s = "mississippi"
    p = "mis*is*p*."
    Output: false
 */

class Solution {
public:
    bool isMatch(char s, char p) {
        return (s == p || p == '*' || p == '.');
    }

    bool isMatch(std::string s, std::string p) {
        std::stack stacks(s);
        return true;
    }

    void test(std::string &s, std::string &p, std::string &ans)
    {
        std::string res = isMatch(s, p);
        std::cout << res << (ans == res ? " == " : " != ") << ans << ":" << s << " -- " << p << std::endl;
    }
};

int main()
{
    size_t len = 5;
    char strs1[][10] = {"aa","aa","ab","aab","mississippi"};
    char strs2[][10] = {"a","a*",".*","c*a*b","mis*is*p*."};
    char strs3[][10] = {"false","true","true","true","false"};
    for(size_t i=5; i<len; i++)
    {
        Solution example;
        example.test(strs1[i], strs2[i], strs3[i]);
    }
    return 0;
}
