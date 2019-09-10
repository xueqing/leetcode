#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

    Example 1:
    Input: "aba"
    Output: True
    Example 2:
    Input: "abca"
    Output: True
    Explanation: You could delete the character 'c'.
 */
using namespace std;

class Solution {
public:
    bool validPalindrome(string &s, size_t start, size_t end) {
        while(start < end)
        {
            if(s.at(start) != s.at(end)) return false;
            start++;
            end--;
        }
        return true;
    }

    bool validPalindrome(string s) {
        for(size_t start=0, end=s.size()-1; start<end;)
        {
            if(s.at(start) != s.at(end))
                return validPalindrome(s, start++, end)
                        || validPalindrome(s, start, end--);
            start++;
            end--;
        }
        return true;
    }

    void test(string &target, bool ans)
    {
        bool res = validPalindrome(target);
        cout << res << (ans == res ? " == " : " != ") << ans << ":" << target;
        cout << endl;
    }
};

int main()
{
    vector<string> targets = {"aba", "abca","abcdba", "abcdb","cbbcc"};
    vector<bool> ans = {true, true, true, false, true};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(targets.at(i), ans.at(i));
    }
    return 0;
}
