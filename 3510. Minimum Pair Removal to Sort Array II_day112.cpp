#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        map<int, long long> mp;
        for (int i = 0; i < n; i++) {
            mp[i] = nums[i];
        }

        // count initial violations
        int bad = 0;
        for (auto it = mp.begin(); next(it) != mp.end(); ++it) {
            if (it->second > next(it)->second)
                bad++;
        }
        if (bad == 0) return 0;

        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<>
        > pq;

        for (auto it = mp.begin(); next(it) != mp.end(); ++it) {
            pq.push({it->second + next(it)->second, it->first});
        }

        int ops = 0;

        while (bad > 0) {
            auto [sum, idx] = pq.top();
            pq.pop();

            auto it = mp.find(idx);
            if (it == mp.end()) continue;

            auto it2 = next(it);
            if (it2 == mp.end()) continue;

            // skip stale heap entry
            if (it->second + it2->second != sum)
                continue;

            // ---- remove old violations ----
            if (it != mp.begin()) {
                auto itL = prev(it);
                if (itL->second > it->second) bad--;
            }
            if (it->second > it2->second) bad--;
            auto itR = next(it2);
            if (itR != mp.end() && it2->second > itR->second) bad--;

            // ---- merge ----
            it->second += it2->second;
            mp.erase(it2);
            ops++;

            // ---- add new violations ----
            if (it != mp.begin()) {
                auto itL = prev(it);
                if (itL->second > it->second) bad++;
            }
            itR = next(it);
            if (itR != mp.end() && it->second > itR->second) bad++;

            // push updated neighbor sums
            if (it != mp.begin()) {
                auto itL = prev(it);
                pq.push({itL->second + it->second, itL->first});
            }
            if (itR != mp.end()) {
                pq.push({it->second + itR->second, it->first});
            }
        }

        return ops;
    }
};
