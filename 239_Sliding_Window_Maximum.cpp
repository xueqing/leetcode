/**
 * @brief The Solution class
    Given an array nums, there is a sliding window of size k which is moving from the very left
    of the array to the very right. You can only see the k numbers in the window. Each time the
    sliding window moves right by one position. Return the max sliding window.

    Example:

    Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
    Output: [3,3,5,5,6,7]
    Explanation:
    Window position                Max
    ---------------               -----
    [1  3  -1] -3  5  3  6  7       3
     1 [3  -1  -3] 5  3  6  7       3
     1  3 [-1  -3  5] 3  6  7       5
     1  3  -1 [-3  5  3] 6  7       5
     1  3  -1  -3 [5  3  6] 7       6
     1  3  -1  -3  5 [3  6  7]      7
    Note:
    You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

    Follow up:
    Could you solve it in linear time?
 */

/**
 * 版本 3：
 *     优化查找满足要求的 ss 和 ee 的过程
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
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    }

private:
};

bool compareVector(vector<int> &v1, vector<int> &v2)
{
    if(v1.size() != v2.size()) return false;
    for(size_t i=0; i<v1.size(); i++)
        if(v1.at(i) != v2.at(i))
            return false;
    return true;
}

int main()
{
    vector<pair<pair<vector<int>, int>, vector<int>>> test;
    {
        int a[] = {1,3,-1,-3,5,3,6,7};
        int asize = sizeof(a) / sizeof(a[0]);
        int b[] = {3,3,5,5,6,7};
        int bsize = sizeof(a) / sizeof(a[0]);
        test.emplace_back(make_pair(vector<int>(a, a+asize), 3), vector<int>(b, a+bsize));
    }

    for(auto &it:test)
    {
        vector<int> &input = it.first.first;
        int k = it.first.second;
        Solution solu;
        vector<int> &ans = it.second;
        vector<int> res = solu.maxSlidingWindow(input, k);
        cout << "match=" << (compareVector(res, ans) ? "Y" : "Nooooo") << endl;
    }

    return 0;
}

