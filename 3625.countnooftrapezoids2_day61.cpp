#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using pii = pair<int,int>;

    // normalized slope as (dy, dx)
    pii getSlope(int x1, int y1, int x2, int y2) {
        int dx = x2 - x1;
        int dy = y2 - y1;
        if (dx == 0) return {1, 0};   // vertical
        if (dy == 0) return {0, 1};   // horizontal
        int g = std::gcd(dx, dy);
        dx /= g; dy /= g;
        if (dx < 0) { dx = -dx; dy = -dy; }
        return {dy, dx};
    }

    // LeetCode driver expects this name
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        if (n < 4) return 0;

        unordered_map<long long, vector<pair<int,int>>> mp;
        mp.reserve((size_t)n * n);

        auto encode = [&](const pii &s) -> long long {
            // shift by +3000 to avoid negatives (coords up to 1000 -> slopes within safe range)
            return ((long long)(s.first + 3000) << 32) | (long long)(s.second + 3000);
        };

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                pii sl = getSlope(points[i][0], points[i][1], points[j][0], points[j][1]);
                mp[encode(sl)].push_back({i, j});
            }
        }

        long long ans = 0;
        for (auto &kv : mp) {
            auto &vec = kv.second;
            int m = (int)vec.size();
            if (m < 2) continue;
            // count disjoint segment pairs
            for (int i = 0; i < m; ++i) {
                for (int j = i + 1; j < m; ++j) {
                    auto [a, b] = vec[i];
                    auto [c, d] = vec[j];
                    if (a == c || a == d || b == c || b == d) continue;
                    ans++;
                }
            }
        }

        // problem constraints ensure answer fits in int, cast for driver
        return (int)ans;
    }
};
