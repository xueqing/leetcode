#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given a string and a string dictionary, find the longest string in the dictionary that can be
    formed by deleting some characters of the given string. If there are more than one possible results,
    return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

    Example 1:
    Input:
    s = "abpcplea", d = ["ale","apple","monkey","plea"]
    Output:
    "apple"

    Example 2:
    Input:
    s = "abpcplea", d = ["a","b","c"]
    Output:
    "a"

    Note:
    1. All the strings in the input will only contain lower-case letters.
    2. The size of the dictionary won't exceed 1,000.
    3. The length of all the strings in the input won't exceed 1,000.
 */
using namespace std;

class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        size_t lens=s.length(), lend=d.size();
        size_t *matlen = new size_t[lend];
        memset(matlen, 0, lend * sizeof(size_t));
        for(size_t strindex=0; strindex<lens; strindex++)
        {
            for(size_t dirindex=0; dirindex<lend; dirindex++)
            {
                size_t curind = matlen[dirindex];
                if(curind < d.at(dirindex).length()
                        && s.at(strindex) == d.at(dirindex).at(curind))
                    matlen[dirindex] = curind + 1;
            }
        }
        string res;
        for(size_t dirindex=0; dirindex<lend; dirindex++)
        {
            if((matlen[dirindex] != d.at(dirindex).length())
                    || (res.length() > matlen[dirindex]))
                    continue;
            if((res.length() < matlen[dirindex])
                    || (strcmp(res.c_str(), d.at(dirindex).c_str()) > 0))
                res = d.at(dirindex);
        }
        delete matlen;
        return res;
    }

    void test(string &str, vector<string> &dic, string &ans)
    {
        string res = findLongestWord(str, dic);
        cout << res << (res == ans ? "==" : "!=") << ans << ":" << str;
        cout << endl;
    }
};

int main()
{
    vector<string> strs = {"abpcplea", "abpcplea", "bab", "foobarfoobar"};
    vector<vector<string>> dics = {{"ale","apple","monkey","plea"}, {"a","b","c"}, {"ba","ab","a","b"}, {"foo","bar"}};
    vector<string> ans = {"apple", "a", "ab", "bar"};
    for(size_t i=0; i<strs.size(); i++)
    {
        Solution example;
        example.test(strs.at(i), dics.at(i), ans.at(i));
    }
    return 0;
}
