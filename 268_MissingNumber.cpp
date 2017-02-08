#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        
        for(int i=1; i<=nums.size(); i++)
        {
            res ^= i;
        }
        
        for(int i=0; i<nums.size(); i++)
        {
            res ^= nums.at(i);
        }
        return res;
    }
};

int main()
{
	vector<int> nums;
	int n, tmp;

	cin >> n;
	for(int i=0; i<n; i++)
	{
		cin  >> tmp;
		nums.push_back(tmp);
	}
	Solution *pSol = new Solution;
	cout << pSol->missingNumber(nums) << endl;

	return 0;
}
