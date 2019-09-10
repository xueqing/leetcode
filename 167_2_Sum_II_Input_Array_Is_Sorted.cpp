#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
    The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

    Note:
    Your returned answers (both index1 and index2) are not zero-based.
    You may assume that each input would have exactly one solution and you may not use the same element twice.
    Example:

    Input: numbers = [2,7,11,15], target = 9
    Output: [1,2]
    Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
 */

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res;
        for(size_t i=0, j=numbers.size()-1; i<j;)
        {
            int temp = numbers.at(i) + numbers.at(j);
            if(temp > target)
                j--;
            else if(temp < target)
                i++;
            else
            {
                res.push_back(i+1);
                res.push_back(j+1);
                break;
            }
        }
        return res;
    }

    bool mycompare(vector<int> &v1, vector<int> &v2)
    {
        if(v1.size() != v2.size()) return false;
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        for(size_t i=0; i<v1.size(); i++)
        {
            if(v1.at(i) != v2.at(i)) return false;
        }
        return true;
    }

    void test(vector<int> &nums, int &target, vector<int> &ans)
    {
        vector<int> res = twoSum(nums, target);
        cout << "res" << (mycompare(ans, res) ? " == " : " != ") << "ans" << ":";
        for(size_t i=0; i<nums.size(); i++)
            cout << nums.at(i) << " ";
        cout << endl;
    }
};

int main()
{
    vector<vector<int>> nums = {{2,7,11,15}};
    vector<int> targets = {9};
    vector<vector<int>> ans = {{1,2}};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(nums.at(i), targets.at(i), ans.at(i));
    }
    return 0;
}
