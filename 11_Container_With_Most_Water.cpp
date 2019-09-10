#include <iostream>
#include <string>
#include <vector>
#include <string.h>

/**
 * @brief The Solution class
    Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai).
    n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
    Find two lines, which together with x-axis forms a container, such that the container contains the most water.

    Note: You may not slant the container and n is at least 2.

    The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water
    (blue section) the container can contain is 49.

    Example:

    Input: [1,8,6,2,5,4,8,3,7]
    Output: 49
    Seen this question in a
 */

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        size_t len = height.size();
        int *con = new int[len];
        memset(con, 0, sizeof(int)*len);
        for(unsigned i=0; i<len; i++)
        {
            for(unsigned j=0; j<i; j++)
            {
                int temp = std::min(height.at(i), height.at(j)) * (i-j);
                con[j] = std::max(con[j], temp);
            }
        }
        int res = 0;
        for(unsigned i=0; i<len; i++)
        {
            res = std::max(res, con[i]);
        }
        delete []con;
        return res;
    }

    void test(std::vector<int>& height, int &ans)
    {
        int res = maxArea(height);
        std::cout << res << (ans == res ? " == " : " != ") << ans << ":";
        for(size_t i=0; i<height.size(); i++)
            std::cout << height.at(i) << ", ";
        std::cout << std::endl;
    }
};

int main()
{
    size_t len = 4;
    std::vector<std::vector<int>> heights = {{1,8,6,2,5,4,8,3,7}, {2}, {1,2}, {2,3,4,5,18,17,6}};
    int ans[] = {49, 0, 1, 17};
    for(size_t i=0; i<len; i++)
    {
        Solution example;
        example.test(heights.at(i), ans[i]);
    }
    return 0;
}
