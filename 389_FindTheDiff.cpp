#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    char findTheDifference(string s, string t) {
        int res = 0;
        for(int i=0; i<s.size(); i++)
        {
            res ^= (s.at(i)-'a');
        }
        for(int i=0; i<t.size(); i++)
        {
            res ^= (t.at(i)-'a');
        }
        return ('a'+res);
    }
};

int main()
{
    string s, t;

    cin >> s >> t;
    Solution *pSol = new Solution;
    cout << pSol->findTheDifference(s, t) << endl;

    return 0;
}

