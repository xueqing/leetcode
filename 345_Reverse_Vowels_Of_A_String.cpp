#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

/**
 * @brief The Solution class
    Write a function that takes a string as input and reverse only the vowels of a string.

    Example 1:

    Input: "hello"
    Output: "holle"
    Example 2:

    Input: "leetcode"
    Output: "leotcede"
    Note:
    The vowels does not include the letter "y".
 */
using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        if(s.size() <= 1) return s;
        set<char> vowelset={'a','e','i','o','u','A','E','I','O','U'};
        for(size_t start=0, end=s.size()-1; start<end;)
        {
            if(vowelset.find(s.at(start)) == vowelset.end())
                start++;
            else if(vowelset.find(s.at(end)) == vowelset.end())
                end--;
            else
            {
                swap(s.at(start), s.at(end));
                start++;
                end--;
            }
        }
        return s;
    }

    void test(string &target, string &ans)
    {
        string res = reverseVowels(target);
        cout << res << (ans == res ? " == " : " != ") << ans << ":" << target;
        cout << endl;
    }
};

int main()
{
    vector<string> targets = {"hello", "leetcode", "", "a","Aa"};
    vector<string> ans = {"holle", "leotcede", "", "a","aA"};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(targets.at(i), ans.at(i));
    }
    return 0;
}
