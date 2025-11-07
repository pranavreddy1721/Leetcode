#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool can(vector<long long>& power, long long r, long long k, long long target) {
        int n = power.size();
        vector<long long> added(n, 0);
        long long used = 0, windowAdd = 0;
        
        for (int i = 0; i < n; ++i) {
            if (i - r - 1 >= 0) windowAdd -= added[i - r - 1];
            
            long long currPower = power[i] + windowAdd;
            if (currPower < target) {
                long long need = target - currPower;
                used += need;
                if (used > k) return false;
                
                if (i + r < n) added[i + r] += need;
                windowAdd += need;
            }
        }
        return true;
    }

    long long maxPower(vector<int>& stations, long long r, long long k) {
        int n = stations.size();
        vector<long long> power(n, 0);
        
        // Compute initial power using prefix sums
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + stations[i];
        for (int i = 0; i < n; ++i) {
            int left = max(0, i - (int)r);
            int right = min(n - 1, i + (int)r);
            power[i] = prefix[right + 1] - prefix[left];
        }

        // Binary search on answer
        long long low = 0, high = *max_element(power.begin(), power.end()) + k;
        long long ans = 0;

        while (low <= high) {
            long long mid = (low + high) / 2;
            if (can(power, r, k, mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
