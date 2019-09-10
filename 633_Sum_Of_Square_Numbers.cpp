#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given a non-negative integer c, your task is to decide whether
    there're two integers a and b such that a2 + b2 = c.

    Example 1:
    Input: 5
    Output: True
    Explanation: 1 * 1 + 2 * 2 = 5
    Example 2:
    Input: 3
    Output: False
 */

using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        for(int i=0, j=sqrt(c); i<=j; )
        {
            int squsum = i * i + j* j;
            if(squsum > c)
                j--;
            else if(squsum < c)
                i++;
            else
                return true;
        }
        return false;
    }

    void test(int &target, bool ans)
    {
        bool res = judgeSquareSum(target);
        cout << res << (ans == res ? " == " : " != ") << ans << ":" << target;
        cout << endl;
    }
};

int main()
{
    vector<int> targets = {5, 3, 61, 4};
    vector<bool> ans = {true, false, true, true};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(targets.at(i), ans.at(i));
    }
    return 0;
}
