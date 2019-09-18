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

/**
 * 版本 1：
 *     保存每种字母 (a,b,c,d) 出现的下标到 inds 数组，字母出现次数不为 0 时，总数加 1；字母出现次数大于 2 时，总数加 1，并选出两个字母用于构造回文串
 * 思路：
 *     1. 先选出两个相同的字母 str1(aa,bb,cc,dd)，分别对应最小下标 start 和最大下标 end，即在字符串 S 中最靠边的位置
 *     2. 回文串长度加 1：从 inds 中选择下标 index(index > start 且 index < end)，在 str1(aa,bb,cc,dd) 中插入一个字母(a,b,c,d) 成为新的回文串 str2
 *        str2 相当于在 start 和 end 直接再选择一个字母成为新的回文串
 *     3. 回文串长度加 2：从 inds 中选择下标 ss(ss > start) 和 ee(ee < end)，在 str1(aa,bb,cc,dd) 中插入两个相同字母(aa,bb,cc,dd) 成为新的回文串 str3
 *        str3 相当于在 start 和 end 直接再选择两个相同的字母成为新的回文串
 *     4. 处理回文串 str3，更新 start=ss 和 end=ee，长度分别加 1 和加 2，重复上述流程
 * 代码解释：
 *     const int DIFF_CHAR = 4;//有 4 种字母
 *     array<vector<int>, DIFF_CHAR> inds;  //保存 4 种字母出现的下标，即预处理 S，保存对应的字母和下标
 *     int sum = 0;                         //保存回文串的总数
 *     vector<pair<int, int> > res;         //pair 保存了每次处理回文串的 start 和 end，开始为空
 * 问题：
 *     因为没有保存中间值(即 start 和 end 相同)，重复计算导致超时
 */
int countPalindromicSubsequences1(string S) {
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

/**
 * 版本 2：
 *     添加数组保存中间值(即 start 和 end 相同)
 * 思路：
 *     实现回调函数求下标范围 [start, end] 对应的回文子串数目，每次更新数组记录中间值
 * 代码解释：
 *     array<set<int>, 4> m_inds;   //保存 4 种字母出现的下标，即预处理 S，保存对应的字母和下标
 *     int m_sumInds[4][1001];      //保存 4 种字母在 S 中从开始到某个位置出现的次数，用于查找在某个范围内是否出现，可快速筛查是否有满足要求的字母可以用于构造新的回文串，初始化为 0
 *     int m_sumSub[1001][1001];    //保存中间值，对应 S 任意两个位置 [start, end] 对应的回文串数目，初始化为 -1
 *                                  //回文串的总数即 m_sumSub[1][S.length()]
 * 问题：
 *     使用 set::upper_bound 可以快速求出满足范围的新的 ss，但是查找对应的 ee 还需要遍历数组
 */
class Solution2 {
public:
    const int N_MODE =  pow(10, 9) + 7;
    size_t m_lenStr = -1;
    array<set<int>, 4> m_inds;
    int m_sumInds[4][1001];
    int m_sumSub[1001][1001];

    int countPalindromicSubsequences(string S) {
        m_lenStr = S.length();

        for(size_t i=0; i<4; i++)
            for(size_t j=0; j<=m_lenStr; j++)
                m_sumInds[i][j] = 0;

        for(size_t i=0; i<=m_lenStr; i++)
            for(size_t j=0; j<=m_lenStr; j++)
                m_sumSub[i][j] = -1;

        for(size_t i=0; i<m_lenStr; i++)
        {
            int index = S.at(i)-'a';
            m_inds.at(index).emplace(i+1);
            m_sumInds[index][i+1] = m_sumInds[index][i] + 1;
        }

        for(size_t i=0; i<4; i++)
            for(size_t j=1; j<=m_lenStr; j++)
                m_sumInds[i][j] = m_sumInds[i][j-1] + m_sumInds[i][j];

        int sum = 0;
        for(size_t i=0; i<4; i++)
        {
            if(m_sumInds[i][m_lenStr] != 0)
            {
                sum = (sum + 1) % N_MODE;
                if(m_sumInds[i][m_lenStr] > 1)
                {
                    int ss = *m_inds.at(i).begin();
                    int ee = *m_inds.at(i).rbegin();
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
            if(m_sumInds[i][end-1] != m_sumInds[i][start])
            {
                sum = (sum + 1) % N_MODE;//add length by 1 for pairs
                if(m_sumInds[i][end-1] - m_sumInds[i][start] > 1)//add length by 2 for pairs
                {
                    int ss = *m_inds.at(i).upper_bound(start);
                    for(int ee=end-1; ee>ss; ee--)
                    {
                        if(m_sumInds[i][ee] != m_sumInds[i][ee-1])
                        {
                            sum = (sum + SubOfString(ss, ee)) % N_MODE;
                            break;
                        }
                    }
                }
            }
        }

        m_sumSub[start][end] = sum;
        return m_sumSub[start][end];
    }
};

/**
 * 版本 3：
 *     优化查找满足要求的 ss 和 ee 的过程
 * 构造思路：
 *     添加数组保存字母在某个位置之前和之后最近出现的下标
 * 代码解释：
 *     int m_lowerInds[4][1001];    //保存字母在某个位置之后最近出现的下标，初始化为 0
 *     int m_upperInds[4][1001];    //保存字母在某个位置之前最近出现的下标，初始化为 0
 *     int m_sumSub[start][end];    //保存下标从 start 到 end 的子串有多少个回文串，初始化为 -1
 * 关于 Solution3
 *     Solution3 使用 vector 替换数组，初始化速度更快，但是内存占用(39-40MB)相比数组(12-13MB)增大
 * 举例：
 *     S = 'bccb'
 *     m_lowerInds['b'-'a'][1001]={1,4,4,4}, m_upperInds['b'-'a'][1001]={1,1,1,4}
 *     m_lowerInds['c'-'a'][1001]={2,2,3,0}, m_upperInds['c'-'a'][1001]={0,2,3,3}
 *     m_lowerInds[i][1])       对应字母 'a'+i 在 S 中第一次出现的下标
 *     m_upperInds[i][m_lenStr] 对应字母 'a'+i 在 S 中最后一次出现的下标
 *     m_lowerInds[i][start])   对应字母 'a'+i 在 S 中 start 之后(包括 start)第一次出现(最靠近 start)的下标     
 *     m_upperInds[i][end]      对应字母 'a'+i 在 S 中 end 之前(包括 end)第一次出现(最靠近 end)的下标
 */

class Solution {
public:
    const int N_MODE =  1e9 + 7;
    int m_lowerInds[4][1001];
    int m_upperInds[4][1001];
    int m_sumSub[1001][1001];

    inline int myMod(int num) {return num < N_MODE ? num : num - N_MODE;}

    int countPalindromicSubsequences(string S) {
        size_t lenStr = S.length();

        for(size_t i=0; i<4; i++)
            memset(m_lowerInds[i], 0, sizeof(int)*(lenStr+1));
        for(size_t i=0; i<4; i++)
            memset(m_upperInds[i], 0, sizeof(int)*(lenStr+1));
        for(size_t i=0; i<=lenStr; i++)
            memset(m_sumSub[i], -1, sizeof(int)*(lenStr+1));

        for(size_t i=0; i<lenStr; i++)
            m_lowerInds[S.at(i)-'a'][i+1] = m_upperInds[S.at(i)-'a'][i+1] = i + 1;

        for(size_t i=0; i<4; i++)
            for(size_t j=lenStr-1; j>=1; j--)
                if(m_lowerInds[i][j] == 0)
                    m_lowerInds[i][j] = m_lowerInds[i][j+1];

        for(size_t i=0; i<4; i++)
            for(size_t j=2; j<=lenStr; j++)
                if(m_upperInds[i][j] == 0)
                    m_upperInds[i][j] = m_upperInds[i][j-1];

        int sum = 0;
        for(size_t i=0; i<4; i++)
        {
            if(m_upperInds[i][lenStr] != 0)
            {
                sum = myMod(sum + 1);
                if(m_upperInds[i][lenStr] != m_lowerInds[i][1])
                {
                    int ss = m_lowerInds[i][1];
                    int ee = m_upperInds[i][lenStr];
                    sum = myMod(sum + SubOfString(ss, ee));
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
                sum = myMod(sum + 1);//add length by 1 for pairs
                if(m_upperInds[i][end-1] > m_lowerInds[i][start+1])//add length by 2 for pairs
                {
                    int ss = m_lowerInds[i][start+1];
                    int ee = m_upperInds[i][end-1];
                    sum = myMod(sum + SubOfString(ss, ee));
                }
            }
        }

        m_sumSub[start][end] = sum;
        return m_sumSub[start][end];
    }
};

class Solution3 {
public:
    const int N_MODE =  1e9 + 7;
    vector<vector<int>> m_lowerInds;
    vector<vector<int>> m_upperInds;
    vector<vector<int>> m_sumSub;

    inline int myMod(int num) {return num < N_MODE ? num : num - N_MODE;}

    int countPalindromicSubsequences(string S) {
        size_t lenStr = S.length();

        m_lowerInds.resize(4, vector<int>(lenStr+1, 0));
        m_upperInds.resize(4, vector<int>(lenStr+1, 0));
        m_sumSub.resize(lenStr+1, vector<int>(lenStr+1, -1));

        for(size_t i=0; i<lenStr; i++)
            m_lowerInds[S.at(i)-'a'][i+1] = m_upperInds[S.at(i)-'a'][i+1] = i + 1;

        for(size_t i=0; i<4; i++)
            for(size_t j=lenStr-1; j>=1; j--)
                if(m_lowerInds[i][j] == 0)
                    m_lowerInds[i][j] = m_lowerInds[i][j+1];

        for(size_t i=0; i<4; i++)
            for(size_t j=2; j<=lenStr; j++)
                if(m_upperInds[i][j] == 0)
                    m_upperInds[i][j] = m_upperInds[i][j-1];

        int sum = 0;
        for(size_t i=0; i<4; i++)
        {
            if(m_upperInds[i][lenStr] != 0)
            {
                sum = myMod(sum + 1);
                if(m_upperInds[i][lenStr] != m_lowerInds[i][1])
                {
                    int ss = m_lowerInds[i][1];
                    int ee = m_upperInds[i][lenStr];
                    sum = myMod(sum + SubOfString(ss, ee));
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
                sum = myMod(sum + 1);//add length by 1 for pairs
                if(m_upperInds[i][end-1] > m_lowerInds[i][start+1])//add length by 2 for pairs
                {
                    int ss = m_lowerInds[i][start+1];
                    int ee = m_upperInds[i][end-1];
                    sum = myMod(sum + SubOfString(ss, ee));
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
