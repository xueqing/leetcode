#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target.
    Return the sum of the three integers. You may assume that each input would have exactly one solution.

    Example:

    Given array nums = [-1, 2, 1, -4], and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        size_t len=nums.size();
        int temp=0, res=nums.at(0)+nums.at(1)+nums.at(2);
        for(size_t i=0; i<len; i++)
        {
            for(size_t j=i+1, k=len-1; j<k; )
            {
                temp = nums.at(i) + nums.at(j) + nums.at(k);
                res = (abs(res-target) > abs(temp-target) ? temp : res);
                if(temp > target)
                    k--;
                else if(temp < target)
                    j++;
                else
                {
                    j++;
                    k--;
                }
            }
        }
        return res;
    }

    void test(vector<int> &nums, int &target, int &ans)
    {
        int res = threeSumClosest(nums, target);
        cout << res << (res == ans ? " == " : " != ") << ans << ":";
        for(size_t i=0; i<nums.size(); i++)
            cout << nums.at(i) << " ";
        cout << endl;
    }
};

int main()
{
    vector<vector<int>> strs = {{-1, 2, 1, -4};
    vector<int> targets = {1};
    vector<int> ans = {2};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(strs.at(i), targets.at(i), ans.at(i));
    }
    return 0;
}
