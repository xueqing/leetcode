#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

/**
 * @brief The Solution class
    A move consists of taking a point (x, y) and transforming it to either (x, x+y) or (x+y, y).
    Given a starting point (sx, sy) and a target point (tx, ty), return True if and only if a sequence of moves exists to transform the point (sx, sy) to (tx, ty). Otherwise, return False.

    Examples:
    Input: sx = 1, sy = 1, tx = 3, ty = 5
    Output: True
    Explanation:
    One series of moves that transforms the starting point to the target is:
    (1, 1) -> (1, 2)
    (1, 2) -> (3, 2)
    (3, 2) -> (3, 5)

    Input: sx = 1, sy = 1, tx = 2, ty = 2
    Output: False

    Input: sx = 1, sy = 1, tx = 1, ty = 1
    Output: True

    Note:
    sx, sy, tx, ty will all be integers in the range [1, 10^9].
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
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        m_DIMEN = max(tx, ty);
        m_tx = tx;
        m_ty = ty;
        m_xSteps = (m_tx - sx) / sy;
        m_ySteps = (m_ty - sy) / sx;

        return tryToReach(sx, sy, 0, 0);
    }

private:
    int m_DIMEN = -1;
    int m_tx = -1;
    int m_ty = -1;
    int m_xSteps = -1;
    int m_ySteps = -1;

    bool tryToReach(int sx, int sy, int xSteps, int ySteps)
    {
        if(xSteps > m_xSteps || ySteps > m_ySteps)   return false;
        int dx = m_tx - sx;
        int dy = m_ty - sy;
        if(dx == 0) return dy % sx == 0;
        if(dy == 0) return dx % sy == 0;
        if(dx < 0 || dy < 0)   return false;
        if(dx < sy || dy < sx)   return false;

        bool bret = false;
        if(sx == sy)
        {
            if(m_tx % sx != 0 || m_ty % sy != 0) return false;
        }
        else
        {
            int dxy = abs(sy - sx);
            if(dx % dxy != 0 || dy % dxy != 0) return false;
        }
        bret = tryToReach(sx, sy+sx, xSteps, ySteps+1) || tryToReach(sx+sy, sy, xSteps+1, ySteps);

        return bret;
    }
};

int main()
{
    vector<pair<array<int, 4>, bool> > test;
    {
        array<int, 4> arr = {1,1,3,5};
        test.emplace_back(arr,true);
    }
    {
        array<int, 4> arr = {1,1,2,2};
        test.emplace_back(arr,false);
    }
    {
        array<int, 4> arr = {1,1,1,1};
        test.emplace_back(arr,true);
    }

    {
        array<int, 4> arr = {9,5,12,8};
        test.emplace_back(arr,false);
    }

    {
        array<int, 4> arr = {35,13,455955547,420098884};
        test.emplace_back(arr,false);
    }

    {
        array<int, 4> arr = {2,7,9,16};
        test.emplace_back(arr,true);
    }

    for(auto it : test)
    {
        array<int, 4> input = it.first;
        Solution solu;
        bool ans = it.second;
        bool res = solu.reachingPoints(input.at(0), input.at(1), input.at(2), input.at(3));
        cout << "result=" << res << "; answer=" << ans << "; match=" << (res == ans ? "Y" : "Nooooo") << endl;
    }

    return 0;
}
