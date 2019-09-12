/**
 * @brief The Solution class
    A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance.
    Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program
    to output the skyline formed by these buildings collectively (Figure B).

    The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates
    of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX,
    and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

    For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

    The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline.
    A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to
    mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part
    of the skyline contour.

    For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

    Notes:

    The number of buildings in any input list is guaranteed to be in the range [0, 10000].
    The input list is already sorted in ascending order by the left x position Li.
    The output list must be sorted by the x position.
    There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is
    not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
 */

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>
#include <queue>

using namespace std;

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
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        if(buildings.empty()) return m_res;

        if(buildings.size() == 1)
        {
            m_res.emplace_back(buildings.front().at(0), buildings.front().at(2));
            m_res.emplace_back(buildings.front().at(1), 0);
            return m_res;
        }

        multimap<int, vector<vector<int>>::iterator> xmap;
        vector<vector<int>> points;

        int nPoints = 0;
        int lf = buildings.front().at(0);
        int rf = buildings.front().at(1);
        int hf = buildings.front().at(2);
        points.emplace_back(lf, rf, hf);
        xmap.emplace(lf, nPoints++);

        int lc=-1, rc=-1, hc=-1;
        for(size_t i=1; i<buildings.size(); i++)
        {
            lc = buildings.at(i).at(0);
            rc = buildings.at(i).at(1);
            hc = buildings.at(i).at(2);
            if(lc > rf)
            {
                points.emplace_back(lc, rc, hc);
                xmap.emplace(lc, nPoints++);
                lf = lc;
                rf = rc;
                hf = hc;
            }
            else if(rc < rf)
            {
                if(hc <= hf)
                    continue;
                points.at(xmap[lf]).at(1) = lc;
                points.emplace_back(lc, rc, hc);
                xmap.emplace(lc, nPoints++);
                points.emplace_back(rc, rf, hf);
                xmap.emplace(rc, nPoints++);
                lf = rc;
            }
            else if(rc > rf)
            {
                points.at(xmap[lf]).at(1) = lc;
                points.emplace_back(lc, rc, hc);
                xmap.emplace(lc, nPoints++);
                points.emplace_back(rc, rf, hf);
                xmap.emplace(rc, nPoints++);
                lf = rc;
            }
            points.emplace_back(buildings.at(i).at(0), buildings.at(i).at(1), buildings.at(i).at(2));
            xmap.emplace(buildings.at(i).at(0), j++);
        }

//        int xfront = buildings.front().at(0);
//        int yfront = 0;
//        m_res.emplace(xfront, yfront);

//        int xcur = -1, ycur = -1;
//        for(auto it=points.begin(); it!=points.end(); it++)
//        {
//            xcur = it->first;
//            ycur = it->second;
//            if(xcur != xfront && ycur != yfront)
//            {
//                xfront = xcur;
//                yfront = ycur;
//                m_res.emplace_back(xfront, yfront);
//            }
//            else if(xcur != xfront && ycur == yfront)
//            {
//                xfront = xcur;
//            }
//            else if(ycur > yfront)
//            {
//                yfront = ycur;
//                m_res.back().at(1) = yfront;
//            }
//        }

        return m_res;
    }

private:
    vector<vector<int>> m_res;
};

string ConvertVectorToString(vector<vector<int>>& in) {
    string str;
    str.resize(in.size() << 1);

    size_t index = -1;
    str[++index] = '{';
    for(auto &it:in)
    {
        str[++index] = it.front()+'0';
        str[++index] = it.back()+'0';
    }

    str[++index] = '}';
    return str;
}

int main()
{
    vector<pair<vector<vector<int>>, string>> test;
    {
        //[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
        vector<vector<int>> in = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
        //[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]
        string out = "{{2,10},{3,15},{7,12},{12,0},{15,10},{20,8},{24,0}}";
        test.emplace_back(in, out);
    }

    for(auto it : test)
    {
        vector<vector<int>> &in = it.first;
        string &outStr = it.second;
        Solution solu;
        vector<vector<int>> res = solu.getSkyline(in);
        string resStr = ConvertVectorToString(res);
        cout << "result=" << resStr << "; answer=" << outStr << "; match=" << (resStr == outStr ? "Y" : "Nooooo") << endl;
    }

    return 0;
}
