#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int nSingle = nums.at(0);
        for(int i=1; i<nums.size(); i++)
        {
            nSingle ^= nums.at(i);
        }
        return nSingle;
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
	cout << pSol->singleNumber(nums) << endl;

	return 0;
}
