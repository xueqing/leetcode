/**
 * @brief The Solution class
    You are given an integer array nums and you have to return a new counts array.
    The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

    Example:

    Input: [5,2,6,1]
    Output: [2,1,1,0]
    Explanation:
    To the right of 5 there are 2 smaller elements (2 and 1).
    To the right of 2 there is only 1 smaller element (1).
    To the right of 6 there is 1 smaller element (1).
    To the right of 1 there is 0 smaller element.
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
#include <map>
#include <iterator>

using namespace std;

class Solution {
    struct Point
    {
        size_t m_ind;
        int m_val;

        Point(size_t ind, int val) : m_ind(ind), m_val(val) {}
    };

    struct myComp
    {
        bool operator() (const Point &left, const Point &right) const
        {
            //如果左边的值小就返回真
            return left.m_ind > right.m_ind && left.m_val < right.m_val;
        }
    };

public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res;
        res.resize(nums.size(), 0);
        multiset<Point, myComp> numSet;
        for(size_t i=0; i!=nums.size(); ++i)
            numSet.emplace(i, nums.at(i));
        for_each(numSet.begin(), numSet.end(), [](Point p) {cout << "[" << p.m_ind << "," << p.m_val << "] ";});
        cout << endl;
        for(auto it=numSet.begin(); it!=numSet.end(); ++it)
            res.at(it->m_ind) = distance(numSet.begin(), numSet.lower_bound(*it));
        return res;
    }
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
    vector<pair<vector<int>, vector<int>> > test;
    {
        int a[] = {5,2,6,1};
        int asize = sizeof(a) / sizeof(a[0]);
        int b[] = {2,1,1,0};
        int bsize = sizeof(b) / sizeof(b[0]);
        test.emplace_back(vector<int>(a, a+asize), vector<int>(b, b+bsize));
    }

    {
        int a[] = {0,2,1};
        int asize = sizeof(a) / sizeof(a[0]);
        int b[] = {0,1,0};
        int bsize = sizeof(b) / sizeof(b[0]);
        test.emplace_back(vector<int>(a, a+asize), vector<int>(b, b+bsize));
    }

    for(auto &it:test)
    {
        vector<int> &input = it.first;
        Solution solu;
        vector<int> &ans = it.second;
        vector<int> res = solu.countSmaller(input);
        for_each(res.begin(), res.end(), [](int i) {cout << i << " ";});
        cout << endl;
        cout << "match=" << (compareVector(res, ans) ? "Y" : "Nooooo") << endl;
    }

    return 0;
}
