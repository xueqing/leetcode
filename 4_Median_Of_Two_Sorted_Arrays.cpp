#include <iostream>
#include <vector>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        size_t len1 = nums1.size();
        size_t len2 = nums2.size();
        size_t mid = (len1 + len2) >> 1;
        double res = 0, pre = 0;
        size_t i=0, j=0, k=0;
        for(; k<=mid; k++)
        {
            pre = res;
            if(i<len1 && j<len2)
            {
                if(nums1.at(i) < nums2.at(j))
                {
                    res = nums1.at(i++);
                }
                else
                {
                    res = nums2.at(j++);
                }
                continue;
            }
            if(i<len1)
            {
                res = nums1.at(i++);
                continue;
            }
            if(j<len2)
            {
                res = nums2.at(j++);
                continue;
            }
        }
        if(((len1 + len2) & 1) == 0)
        {
            res = (pre + res) / 2;
        }
        return res;
    }

    void ConstructFromArray(int arr[], size_t len, std::vector<int>& nums)
    {
        for(unsigned i=0; i<len; i++)
        {
            nums.push_back(arr[i]);
        }
    }

    void Print(std::vector<int>& nums)
    {
        for(auto it : nums)
        {
            std::cout << "->" << it;
        }
        std::cout << std::endl;
    }

    void test(int arr1[], size_t len1, int arr2[], size_t len2)
    {
        std::vector<int> nums1;
        ConstructFromArray(arr1, len1, nums1);
        std::vector<int> nums2;
        ConstructFromArray(arr2, len2, nums2);

        std::cout << "array1";
        Print(nums1);
        std::cout << "array2";
        Print(nums2);
        double res = findMedianSortedArrays(nums1, nums2);
        std::cout << "result:" << res << std::endl;
    }
};

int main()
{
    int arr1[] = {1,3};//1,3
    int arr2[] = {2};//2
    Solution example;
    example.test(arr1, 2, arr2, 1);
    return 0;
}
