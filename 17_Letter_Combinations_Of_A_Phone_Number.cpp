#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
    A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

    Example:
    Input: "23"
    Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
    Note:

    Although the above answer is in lexicographical order, your answer could be in any order you want.
 */

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans={""};
        vector<string> corrs={"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        size_t len = digits.length();
        string letters, pre;
        for(size_t i=0; i<len; i++)
        {
            letters = corrs.at(digits.at(i)-'2');
            size_t j=ans.size();
            while(j-- > 0)
            {
                pre = ans.front();
                for(size_t k=0; k<letters.size(); k++)
                    ans.push_back(pre+letters.at(k));
                ans.erase(ans.begin());
            }
        }
        if(ans.size() == 1) ans.clear();
        return ans;
    }

    bool mycompare(vector<string> &v1, vector<string> &v2)
    {
        if(v1.size() != v2.size()) return false;
        for(size_t i=0; i<v1.size(); i++)
        {
            if(v1.at(i) != v2.at(i)) return false;
        }
        return true;
    }

    void test(string &str, vector<string> &ans)
    {
        vector<string> res = letterCombinations(str);
        cout << "res" << (mycompare(res, ans) ? " == " : " != ") << "ans" << ":" << str.c_str();
        cout << endl;
    }
};

int main()
{
    vector<string> strs = {"23","","4"};
    vector<vector<string>> ans = {{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}, {}, {"g","h","i"}};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(strs.at(i), ans.at(i));
    }
    return 0;
}
