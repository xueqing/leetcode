#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums
    such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

    Note:
    The solution set must not contain duplicate quadruplets.

    Example:
    Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
    A solution set is:
    [
      [-1,  0, 0, 1],
      [-2, -1, 1, 2],
      [-2,  0, 0, 2]
    ]
 */

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if(nums.size() < 3) return res;
        sort(nums.begin(), nums.end());
        size_t len=nums.size();
        int temp=0, a=-1, b=-1, c=-1, d=-1;
        for(size_t m=0; m<len-3; m++)
        {
            if(res.size()>0 && a==nums.at(m)) continue;
            for(size_t i=m+1; i<len-2; i++)
            {
                if(res.size()>0 && a==nums.at(m) && b==nums.at(i)) continue;
                for(size_t j=i+1, k=len-1; j<k; )
                {
                    if(res.size()>0 && a==nums.at(m) && b==nums.at(i) && c==nums.at(j))
                    {
                        j++;
                        continue;
                    }
                    temp = nums.at(m) + nums.at(i) + nums.at(j) + nums.at(k);
                    if(temp > target)
                        k--;
                    else if(temp < target)
                        j++;
                    else
                    {
                        a = nums.at(m);
                        b = nums.at(i);
                        c = nums.at(j);
                        d = nums.at(k);
                        res.push_back({a, b, c, d});
                        j++;
                        k--;
                    }
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

    void test(vector<int> &nums, int &target, vector<vector<int>> &ans)
    {
        vector<vector<int>> res = fourSum(nums, target);
        cout << "res" << (mycompare(res, ans) ? " == " : " != ") << "ans" << ":";
        for(size_t i=0; i<nums.size(); i++)
            cout << nums.at(i) << " ";
        cout << endl;
    }
};

int main()
{
    vector<vector<int>> strs = {{1, 0, -1, 0, -2, 2}, {0,0,0,0}, {0,1,5,0,1,5,5,-4}};
    vector<int> targets = {0, 0, 11};
    vector<vector<vector<int>>> ans = {{{-2, -1, 1, 2},{-2,  0, 0, 2},{-1,  0, 0, 1}}, {{0,0,0,0}}, {{-4,5,5,5},{0,1,5,5}}};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(strs.at(i), targets.at(i), ans.at(i));
    }
    return 0;
}
