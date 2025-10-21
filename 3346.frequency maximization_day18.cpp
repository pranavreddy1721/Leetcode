#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        if (n == 0) return 0;

        // frequency of exact values in nums
        unordered_map<int,int> cnt;
        cnt.reserve(n * 2);
        for (int x : nums) ++cnt[x];

        // Build difference events for intervals [x-k, x+k]
        // We place +1 at l and -1 at r+1
        map<long long,int> diff;
        for (int x : nums) {
            long long l = (long long)x - k;
            long long r = (long long)x + k;
            diff[l] += 1;
            diff[r + 1] -= 1;
        }

        // Sorted unique targets that are actual nums values
        vector<int> targets;
        targets.reserve(cnt.size());
        for (auto &p : cnt) targets.push_back(p.first);
        sort(targets.begin(), targets.end());

        // Sweep
        int ans = 0;
        int overlap = 0;
        auto it = diff.begin();
        vector<long long> keys;
        keys.reserve(diff.size());
        for (auto &p : diff) keys.push_back(p.first);

        int t_idx = 0; // pointer into targets
        int m = (int)keys.size();
        for (int i = 0; i < m; ++i) {
            long long cur = keys[i];
            overlap += diff[cur];               // overlap valid starting at `cur`

            long long seg_l = cur;
            long long seg_r;
            if (i + 1 < m) seg_r = keys[i+1] - 1; // next key starts at keys[i+1], so this segment ends at keys[i+1]-1
            else seg_r = cur; // last event: segment is just `cur` (no further integer range to consider)

            if (seg_l > seg_r) continue; // empty integer segment

            // Consider any integer target inside [seg_l, seg_r]
            // 1) Non-present integers in nums (cnt=0)
            int possible_non_present = min(overlap, numOperations);
            ans = max(ans, possible_non_present);

            // 2) Present targets in nums: iterate through sorted targets in this range
            while (t_idx < (int)targets.size() && (long long)targets[t_idx] < seg_l) ++t_idx;
            int j = t_idx;
            while (j < (int)targets.size() && (long long)targets[j] <= seg_r) {
                int x = targets[j];
                int c_equal = cnt[x];
                int possible = min(overlap, c_equal + numOperations);
                ans = max(ans, possible);
                ++j;
            }
            // advance t_idx to j for next segments (small optimization)
            t_idx = j;

            if (ans == n) return n; // can't do better
        }

        return ans;
    }
};
