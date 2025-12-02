#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const long long MOD = 1000000007LL;

    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<long long, long long> freq;  // y -> number of points
        for (auto &p : points)
            freq[p[1]]++;

        vector<long long> ways;
        ways.reserve(freq.size());

        auto C2 = [&](long long x) {
            return (x < 2 ? 0 : (x * (x - 1) / 2) % MOD);
        };

        for (auto &f : freq) {
            long long c = C2(f.second);
            if (c > 0) ways.push_back(c);
        }

        long long sum = 0, sumSq = 0;
        for (long long v : ways) {
            sum = (sum + v) % MOD;
            sumSq = (sumSq + v * v % MOD) % MOD;
        }

        long long res = ( (sum * sum % MOD - sumSq + MOD) % MOD ) * ((MOD + 1) / 2) % MOD;
        return (int)res;
    }
};
