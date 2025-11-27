#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        // min prefix sum for each prefix-index modulo k
        vector<long long> minPref(k, LLONG_MAX);
        
        long long pref = 0;
        long long ans = LLONG_MIN;
        
        // prefix at index 0 (sum of zero elements) has index 0
        minPref[0] = 0;
        
        // j is the prefix index after taking j elements (j from 1..n)
        for (int j = 1; j <= n; ++j) {
            pref += nums[j-1];         // pref = sum of first j elements
            int mod = j % k;           // bucket by prefix-index modulo k
            
            if (minPref[mod] != LLONG_MAX) {
                ans = max(ans, pref - minPref[mod]);
            }
            // update minimum prefix sum seen at this index mod
            minPref[mod] = min(minPref[mod], pref);
        }
        return ans;
    }
};
