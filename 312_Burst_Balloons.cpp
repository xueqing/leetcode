/**
 * @brief The Solution class
    Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums.
    You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
    Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

    Find the maximum coins you can collect by bursting the balloons wisely.

    Note:
    You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
    0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

    Example:
    Input: [3,1,5,8]
    Output: 167
    Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
                 coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
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
    int maxCoins(vector<int>& nums) {
    }
};

int main()
{
    vector<pair<vector<int>, int> > test;
    {
        int a[] = {3,1,5,8};
        int asize = sizeof(a) / sizeof(a[0]);
        test.emplace_back(vector<int>(a, a+asize), 167);
    }

    for(auto &it:test)
    {
        vector<int> &input = it.first;
        Solution solu;
        int ans = it.second;
        int res = solu.maxCoins(input);
        cout << "result=" << res << "; answer=" << ans << "; match=" << (res == ans ? "Y" : "Nooooo") << endl;
    }

    return 0;
}
