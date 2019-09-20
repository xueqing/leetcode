/**
 * @brief The Solution class
    Given an array which consists of non-negative integers and an integer m, you can split the array
    into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

    Note:
    If n is the length of array, assume the following constraints are satisfied:
    1 ≤ n ≤ 1000
    1 ≤ m ≤ min(50, n)

    Examples:
    Input:
    nums = [7,2,5,10,8]
    m = 2
    Output:
    18

    Explanation:
    There are four ways to split nums into two subarrays.
    The best way is to split it into [7,2,5] and [10,8],
    where the largest sum among the two subarrays is only 18.
 */

/**
 * 构造思路：
 *     添加数组保存字母在某个位置之前和之后最近出现的下标
 * 代码解释：
 *     int m_lowerInds[4][1001];    //保存字母在某个位置之后最近出现的下标，初始化为 0
 * 举例：
 *     S = 'bccb'
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {

    }
};

int main()
{
    vector<pair<pair<vector<int>, int>, int>> test;
    {
        int a[] = {7,2,5,10,8};
        int asize = sizeof(a) / sizeof(a[0]);
        test.emplace_back(make_pair(vector<int>(a, a+asize), 2), 18);
    }

    for(auto &it:test)
    {
        vector<int> &input = it.first.first;
        Solution solu;
        int ans = it.second;
        int res = solu.splitArray(input, it.first.second);
        cout << "result=" << res << "; answer=" << ans << "; match=" << (res == ans ? "Y" : "Nooooo") << endl;
    }

    return 0;
}
