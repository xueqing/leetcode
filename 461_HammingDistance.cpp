#include <iostream>

using namespace std;

class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = x ^ y;
        int nDiff = 0;
        for(int i=0; i<32; i++)
        {
            nDiff += res & 1;
            res >>= 1;
        }
        return nDiff;
    }
};

int main()
{
	int x, y;
	cin >> x >> y;

	Solution *pSol = new Solution;
	cout << pSol->hammingDistance(x, y) << endl;

	return 0;
}
