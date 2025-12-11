#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        unordered_map<int, vector<int>> rows; // x -> list of y values
        unordered_map<int, vector<int>> cols; // y -> list of x values

        // Group buildings
        for (auto &b : buildings) {
            int x = b[0], y = b[1];
            rows[x].push_back(y);
            cols[y].push_back(x);
        }

        // Sort each group
        for (auto &p : rows) sort(p.second.begin(), p.second.end());
        for (auto &p : cols) sort(p.second.begin(), p.second.end());

        // Track buildings that have left+right and up+down
        unordered_set<long long> hasLR, hasUD;

        // Mark buildings with LEFT + RIGHT (in a row)
        for (auto &p : rows) {
            int x = p.first;
            auto &ys = p.second;
            if (ys.size() < 3) continue; // need at least 3 to be strictly inside
            for (size_t i = 1; i + 1 < ys.size(); ++i) {
                int y = ys[i];
                long long key = ( (long long)x << 32 ) | (unsigned long long)y;
                hasLR.insert(key);
            }
        }

        // Mark buildings with UP + DOWN (in a column)
        for (auto &p : cols) {
            int y = p.first;
            auto &xs = p.second;
            if (xs.size() < 3) continue;
            for (size_t i = 1; i + 1 < xs.size(); ++i) {
                int x = xs[i];
                long long key = ( (long long)x << 32 ) | (unsigned long long)y;
                hasUD.insert(key);
            }
        }

        // Count covered buildings (must have both)
        int covered = 0;
        for (auto &b : buildings) {
            long long key = ( (long long)b[0] << 32 ) | (unsigned long long)b[1];
            if (hasLR.count(key) && hasUD.count(key)) ++covered;
        }

        return covered;
    }
};

