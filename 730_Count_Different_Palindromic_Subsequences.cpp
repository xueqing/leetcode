#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

/**
 * @brief The Solution class
    Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.
    A subsequence of a string S is obtained by deleting 0 or more characters from S.
    A sequence is palindromic if it is equal to the sequence reversed.
    Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

    Example 1:
    Input:
    S = 'bccb'
    Output: 6
    Explanation:
    The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
    Note that 'bcb' is counted only once, even though it occurs twice.

    Example 2:
    Input:
    S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
    Output: 104860361
    Explanation:
    There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.

    Note:
    The length of S will be in the range [1, 1000].
    Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
 */

/*
 * time limited for computing repeated values with the same start and end
int countPalindromicSubsequences(string S) {
    const int DIFF_CHAR = 4;

    array<vector<int>, DIFF_CHAR> inds;
    for(size_t i=0; i<S.length(); i++)
        inds.at(S.at(i)-'a').push_back(i);

    int sum = 0;
    vector<pair<int, int> > res;
    for(size_t i=0; i<DIFF_CHAR; i++)
    {
        if(!inds.at(i).empty())
        {
            sum++;
        }

        if(inds.at(i).size() > 1)
        {
            // save the first and last index of the Palindromic Subsequences
            sum++;
            res.emplace_back(inds.at(i).front(), inds.at(i).back());
        }
    }

    if(res.empty()) return sum;

    while(!res.empty())
    {
        int start = res.back().first;
        int end = res.back().second;
        res.pop_back();

        for(size_t j=0; j<DIFF_CHAR; j++)
        {
            vector<int> vec2 = inds.at(j);

            //add length by 1 for pairs
            for(auto it : vec2)
            {
                if(it >= end) break;
                if(it > start && it < end)
                {
                    sum++;
                    break;
                }
            }

            //add length by 2 for pairs
            bool b1=false, b2=false;
            int ss=-1, ee=-1;
            for(auto it=vec2.begin(); it!=vec2.end(); it++)
            {
                if(*it >= end) break;

                if(!b1 && *it > start)
                {
                    b1 = true;
                    ss = *it;
                    for(auto itt=vec2.rbegin(); *itt!=*it; itt++)
                    {
                        if(*itt <= start) break;
                        if(!b2 && *itt < end)
                        {
                            b2 = true;
                            ee = *itt;
                            break;
                        }
                    }
                    break;
                }
            }

            if(b1 && b2)
            {
                sum++;
                res.emplace_back(ss, ee);
            }
        }
    }
    return sum;
}
*/

class Solution {
public:
    const int N_MODE =  pow(10, 9) + 7;
    size_t m_lenStr = -1;
    int m_lowerInds[4][1001];
    int m_upperInds[4][1001];
    int m_sumSub[1001][1001];

    int countPalindromicSubsequences(string S) {
        m_lenStr = S.length();

        for(size_t i=0; i<4; i++)
            for(size_t j=0; j<=m_lenStr; j++)
                m_lowerInds[i][j] = m_upperInds[i][j] = 0;

        for(size_t i=0; i<=m_lenStr; i++)
            for(size_t j=0; j<=m_lenStr; j++)
                m_sumSub[i][j] = -1;

        for(size_t i=0; i<m_lenStr; i++)
            m_lowerInds[S.at(i)-'a'][i+1] = m_upperInds[S.at(i)-'a'][i+1] = i + 1;

        for(size_t i=0; i<4; i++)
            for(size_t j=m_lenStr-1; j>=1; j--)
                if(m_lowerInds[i][j] == 0)
                    m_lowerInds[i][j] = m_lowerInds[i][j+1];

        for(size_t i=0; i<4; i++)
            for(size_t j=2; j<=m_lenStr; j++)
                if(m_upperInds[i][j] == 0)
                    m_upperInds[i][j] = m_upperInds[i][j-1];

        int sum = 0;
        for(size_t i=0; i<4; i++)
        {
            if(m_upperInds[i][m_lenStr] != 0)
            {
                sum = (sum + 1) % N_MODE;
                if(m_upperInds[i][m_lenStr] != m_lowerInds[i][1])
                {
                    int ss = m_lowerInds[i][1];
                    int ee = m_upperInds[i][m_lenStr];
                    sum = (sum + SubOfString(ss, ee)) % N_MODE;
                }
            }
        }
        return sum;
    }

    int SubOfString(int start, int end)
    {
        if(start < 0 || end < 0)        return 0;
        if(m_sumSub[start][end] != -1)  return m_sumSub[start][end];

        int sum = 1;
        for(size_t i=0; i<4; i++)
        {
            if(m_upperInds[i][end-1] > start)
            {
                sum = (sum + 1) % N_MODE;//add length by 1 for pairs
                if(m_upperInds[i][end-1] > m_lowerInds[i][start+1])//add length by 2 for pairs
                {
                    int ss = m_lowerInds[i][start+1];
                    int ee = m_upperInds[i][end-1];
                    sum = (sum + SubOfString(ss, ee)) % N_MODE;
                }
            }
        }

        m_sumSub[start][end] = sum;
        return m_sumSub[start][end];
    }
};

int main()
{
    vector<pair<string, int>> test;
    test.emplace_back("a", 1);
    test.emplace_back("aaa", 3);
    test.emplace_back("bccb", 6);
    test.emplace_back("abccba", 14);
    test.emplace_back("abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba", 104860361);
    test.emplace_back("bcbacbabdcbcbdcbddcaaccdcbbcdbcabbcdddadaadddbdbbbdacbabaabdddcaccccdccdbabcddbdcccabccbbcdbcdbdaada", 117990582);
    test.emplace_back("dcdacabbabacbddababcdabdaaddcdcadbbaccbadcacdbddaabdabbcdacbcdadbbdccadacbbabacaccbccadcccacbacbcacccdaacacabbbcbaabaadbbbdcdcbdcadabdcdacbadabcaaacdbbbcadadcaadcabcdcdcbaccccdabbbdccdcbcaaaaccabdbdadcdbcbbcddcaabcbbcbabbabcbdbcdabadabccabbaabbdcbbccbabdccacacccbdabbccdbccdaaabddbccbbddaabacacbbbdacbcbabccdcaddccbcdbbacbbadcccccbaddddcdbdadcbcdcdbddacbbcdcdaddadbccaccbadcbcccacbddabbddbaabddccbddbbdccaacadbdcdbaaacbbbcabcdcbaaccbcdcdbacbddccbcbbbaadccdabacaccbbdabddbacbabcbcacddddcdbdcaaabbbaaacdbcdcabbbcbacbacadbacdcdcabacbaabdabccaccbadabbcdccbdbcccbddcdaaadadccccbabcddbacbadbbbcaaaddcacddbcaadaaadbdcbdbbbccaabbdbdbdccbbaddaacabbcbbbdccdaabbcaccabacabccccbbbdcadabbcaaacdbcdabdaaaacbdbddadaaadaccabcaaadccaddbbcdcddadbdbdcbddbadddbbabdddbdcacbcaadaddbdcacbcdcdccdddaadccbabbbdbcdacbbdbadacbaaddcbacdaddbbbacacbcdbccddcaadbcccdbcaaaadcdbcddddbacadbdcdaccddacbdcabbbaababdaddccddaacbbbdcdcdbdddcabdbaaccdbddccacdcdaaaddccccddcbadcddddacddadcbdbccbbadcbbdbcbbbabddbcccacbadacbcccdcdbbbdcdcbbac", 480484038);

    int mod = pow(10, 9) + 7;
    for(auto it : test)
    {
        string str = it.first;
        Solution solu;
        int ans = it.second;
        int res = solu.countPalindromicSubsequences(str);
        cout << "result=" << res << "; module=" << res % mod << "; answer=" << ans << endl;
    }

    return 0;
}
