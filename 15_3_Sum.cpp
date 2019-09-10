#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given an array nums of n integers, are there elements a, b, c in nums such that
    a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

    Note:

    The solution set must not contain duplicate triplets.

    Example:

    Given array nums = [-1, 0, 1, 2, -1, -4],

    A solution set is:
    [
      [-1, 0, 1],
      [-1, -1, 2]
    ]
 */

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if(nums.size() < 3) return res;
        sort(nums.begin(), nums.end());
        size_t posstart=0, len=nums.size();
        for(size_t i=0; i<len; i++)
        {
            if(nums.at(i) >= 0)
            {
                posstart = i;
                break;
            }
        }
        int temp=0, a=-1, b=-1, c=-1;
        for(size_t i=0; i<=posstart; i++)
        {
            if(res.size()>0 && a==nums.at(i)) continue;
            for(size_t j=i+1, k=len-1; j<k; )
            {
                if(res.size()>0 && a==nums.at(i) && b==nums.at(j))
                {
                    j++;
                    continue;
                }
                temp = nums.at(i) + nums.at(j) + nums.at(k);
                if(temp > 0)
                    k--;
                else if(temp < 0)
                    j++;
                else
                {
                    a = nums.at(i);
                    b = nums.at(j);
                    c = nums.at(k);
                    res.push_back({a, b, c});
                    j++;
                    k--;
                }
            }
        }
        return res;
    }

    bool mycompare(vector<vector<int>> &v1, vector<vector<int>> &v2)
    {
        if(v1.size() != v2.size()) return false;
        for(size_t i=0; i<v1.size(); i++)
        {
            sort(v1.begin(), v1.end());
            sort(v2.begin(), v2.end());
            if(v1.at(i).size() != v2.at(i).size()) return false;
            for(size_t j=0; j<v1.at(i).size(); j++)
                if(v1.at(i).at(j) != v2.at(i).at(j))
                    return false;
        }
        return true;
    }

    void test(vector<int> &nums, vector<vector<int>> &ans)
    {
        vector<vector<int>> res = threeSum(nums);
        cout << "res" << (mycompare(ans, res) ? " == " : " != ") << "ans" << ":";
        for(size_t i=0; i<nums.size(); i++)
            cout << nums.at(i) << " ";
        cout << endl;
    }
};

int main()
{
    vector<vector<int>> strs = {{-1, 0, 1, 2, -1, -4}, {0,0,0}, {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6}};
    vector<vector<vector<int>>> ans = {{{-1, 0, 1},{-1,-1,2}}, {{0,0,0}}, {{-4,-2,6},{-4,0,4},{-4,1,3},{-4,2,2},{-2,-2,4},{-2,0,2}}};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(strs.at(i), ans.at(i));
    }
    return 0;
}
