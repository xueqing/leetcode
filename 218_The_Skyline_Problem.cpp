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
#include <math.h>
#include <stdint.h>
#include <assert.h>

using namespace std;

/**
 * 思路：
 *     保存建筑物的房顶线段，起初是 x 轴上一条完整的线段，即高度为 0。
 *     之后每次处理一个建筑物，需要分割已有线段，将处理建筑物房顶线段放在合适的位置
 * 代码解释：
 *     vector<Line> m_lines;    //保存线段
 *     int maxX = INT32_MIN;    //保存建筑物坐标 L 最大值，即线段最大长度
 *     size_t m_pos = 0;        //保存上一个建筑物 L 对应的位置，因为建筑物输入是按照 L 递增的
 *     void insertABuilding(size_t index, int left, int right, int height); //在第 index 个线段的位置插入一根新线段
 *     void mergeLines(vector<vector<int>> &res); //合并线段，记录对应的坐标点。当高度与前者不同时，记录 L 和高度
 */
class Solution {
    struct Line
    {
        int left;
        int right;
        int height;

        Line(int l, int r, int h) : left(l), right(r), height(h){}
    };

public:
    void insertABuilding(size_t index, int left, int right, int height)
    {
        vector<Line>::iterator it = m_lines.begin()+index;
        int formall = it->left;
        int formalr = it->right;
        int formalh = it->height;
        if(left == right || right <= formall)
            return;
        else if(left >= formalr)
            insertABuilding(index+1, left, right, height);
        else if(height <= formalh)
            insertABuilding(index, min(right, formalr), right, height);
        else if(left > formall)
        {
            it->right = left;
            m_lines.emplace(it+1, left, formalr, formalh);
            m_pos++;
            insertABuilding(index+1, left, right, height);
        }
        else if(left == formall)
        {
            it->height = height;
            if(right >= formalr)
                insertABuilding(index, formalr, right, height);
            else
            {
                it->right = right;
                m_lines.emplace(it+1, right, formalr, formalh);
            }
        }
    }

    void mergeLines(vector<vector<int>> &res)
    {
        vector<int> tmp;
        tmp.resize(2, 0);
        tmp.at(0) = m_lines.front().left;
        tmp.at(1) = m_lines.front().height;
        res.emplace_back(tmp);
        for(size_t i=1; i<m_lines.size(); i++)
        {
            if(m_lines.at(i).height != m_lines.at(i-1).height)
            {
                tmp.at(0) = m_lines.at(i).left;
                tmp.at(1) = m_lines.at(i).height;
                res.emplace_back(tmp);
            }
        }
        tmp.at(0) = m_lines.back().right;
        tmp.at(1) = 0;
        res.emplace_back(tmp);
    }

    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> res;
        if(buildings.empty()) return res;

        int maxX = INT32_MIN;
        for(size_t i=0; i<buildings.size(); i++)
            maxX = max(maxX, buildings.at(i).at(1));
        m_lines.emplace_back(buildings.front().at(0), maxX, 0);

        for(size_t i=0; i<buildings.size(); i++)
            insertABuilding(m_pos, buildings.at(i).at(0), buildings.at(i).at(1), buildings.at(i).at(2));

        mergeLines(res);
        return res;
    }

private:
    vector<Line> m_lines;
    size_t m_pos = 0;
};

bool CompareVectorOfInt(vector<vector<int>>& vec1, vector<vector<int>> &vec2) {
    if(vec1.size() != vec2.size()) return false;
    for(size_t i=0; i<vec1.size(); i++)
    {
        if(vec1.at(i).at(0) != vec2.at(i).at(0) || vec1.at(i).at(1) != vec2.at(i).at(1))
            return false;
    }
    return true;
}

int main()
{
    vector<pair<vector<vector<int>>, vector<vector<int>>>> test;
    {
        vector<vector<int>> in = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
        vector<vector<int>> out = {{2,10},{3,15},{7,12},{12,0},{15,10},{20,8},{24,0}};
        test.emplace_back(in, out);
    }

    {
        vector<vector<int>> in = {{0,1,3}};
        vector<vector<int>> out = {{0,3},{1,0}};
        test.emplace_back(in, out);
    }

    for(auto it : test)
    {
        vector<vector<int>> &in = it.first;
        vector<vector<int>> &out = it.second;
        Solution solu;
        vector<vector<int>> res = solu.getSkyline(in);
        if(!CompareVectorOfInt(res, out))
        {
            cout << "match=Nooooo" << endl;
            assert(false);
        }
        cout << "match=Y" << endl;
    }

    return 0;
}
