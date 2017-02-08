#include <iostream>
#include <cstdint>
#include <cinttypes>

using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t rev = 0;
        for(int i=0; i<31; i++)
        {
            rev ^= (n & 1);
            rev <<= 1;
            n >>= 1;
        }
        rev ^= (n & 1);
        return rev;
    }
};

int main()
{
	uint32_t n;
	cin >> n;

	Solution *pSol = new Solution;
	cout << pSol->reverseBits(n) << endl;

	return 0;
}
