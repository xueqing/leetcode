#include <iostream>
#include <cstdint>
#include <cinttypes>

using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int nOne = 0;
        for(int i=0; i<32; i++)
        {
            nOne += n & 1;
            n >>= 1;
        }
        return nOne;
    }
};

int main()
{
	uint32_t n;
	cin >> n;

	Solution *pSol = new Solution;
	cout << pSol->hammingWeight(n) << endl;

	return 0;
}
