#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given a linked list, remove the n-th node from the end of list and return its head.

    Example:
    Given linked list: 1->2->3->4->5, and n = 2.
    After removing the second node from the end, the linked list becomes 1->2->3->5.
    Note:

    Given n will always be valid.
 */

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *root = nullptr;
        return root;
    }

    void test(vector<int> &nums, int &target, vector<int> &ans)
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
    vector<vector<int>> strs = {{1,2,3,4,5}};
    vector<int> targets = {2};
    vector<vector<int>> ans = {{1,2,3,5}};
    for(size_t i=0; i<ans.size(); i++)
    {
        Solution example;
        example.test(strs.at(i), targets.at(i), ans.at(i));
    }
    return 0;
}
