#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        const long long MOD = 1e9 + 7;

        // Add boundary fences
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        // Store all vertical differences
        unordered_set<int> vertDiff;
        int vsz = vFences.size();
        for (int i = 0; i < vsz; i++) {
            for (int j = i + 1; j < vsz; j++) {
                vertDiff.insert(vFences[j] - vFences[i]);
            }
        }

        // Find max common difference
        long long maxSide = 0;
        int hsz = hFences.size();
        for (int i = 0; i < hsz; i++) {
            for (int j = i + 1; j < hsz; j++) {
                int diff = hFences[j] - hFences[i];
                if (vertDiff.count(diff)) {
                    maxSide = max(maxSide, (long long)diff);
                }
            }
        }

        if (maxSide == 0) return -1;
        return (int)((maxSide * maxSide) % MOD);
    }
};
