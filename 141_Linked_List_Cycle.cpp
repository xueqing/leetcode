#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief The Solution class
    Given a linked list, determine if it has a cycle in it.

    Follow up:
    Can you solve it without using extra space?
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
    bool hasCycle(ListNode *head) {
        if(!head) return false;
        ListNode *before = head;
        ListNode *after = head;
        while(before && before->next && after)
        {
            before = before->next->next;
            after = after->next;
            if(before == after) return true;
        }
        return false;
    }
};
