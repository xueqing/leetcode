#include <iostream>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    int GetVal(ListNode* &pNode)
    {
        if(pNode)
            return pNode->val;
        return 0;
    }

    ListNode* NextNode(ListNode* &pNode)
    {
        if(pNode && pNode->next)
            return pNode->next;
        return nullptr;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *pre = nullptr, *root = nullptr;
        int pro = 0;
        while(l1 || l2 || pro!=0)
        {
            ListNode *sum = new ListNode((GetVal(l1) + GetVal(l2) + pro)%10);
            pro = (GetVal(l1) + GetVal(l2) + pro) / 10;
            l1 = NextNode(l1);
            l2 = NextNode(l2);
            if(nullptr == root)
            {
                root = sum;
                pre = sum;
                std::cout << "sum:" << sum->val << std::endl;
                continue;
            }            
            pre->next = sum;
            std::cout << "sum:" << sum->val << std::endl;
            pre = pre->next;
        }
        return root;
    }

    ListNode* ConstructListNode(int arr[], size_t len)
    {
        ListNode *pre = nullptr, *root = nullptr;
        for(unsigned i=0; i<len; i++)
        {
            ListNode *pNode = new ListNode(arr[i]);
            if(nullptr == root)
            {
                root = pNode;
                pre = pNode;
                continue;
            }
            pre->next = pNode;
            pre = pre->next;
        }
        return root;
    }

    void Print(ListNode *root)
    {
        std::cout << "->" << root->val;
        while(root->next)
        {
            root = root->next;
            std::cout << "->" << root->val;
        }
        std::cout << std::endl;
    }

    void test(int arr1[], size_t len1, int arr2[], size_t len2)
    {
        ListNode *root1 = ConstructListNode(arr1, len1);
        std::cout << "array1";
        Print(root1);
        ListNode *root2 = ConstructListNode(arr2, len2);
        std::cout << "array2";
        Print(root2);
        ListNode *res = addTwoNumbers(root1, root2);
        std::cout << "result";
        Print(res);
    }
};

int main()
{
    int arr1[] = {2,4,3};//0
    int arr2[] = {5,6,4};//0
    Solution example;
    example.test(arr1, 3, arr2, 3);
    return 0;
}
