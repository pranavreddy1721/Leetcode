class Solution {
public:
    long long maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size();
        vector<long long> dp(n);
        long long ans = LLONG_MIN;

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = energy[i];
            if (i + k < n)
                dp[i] += dp[i + k];
            ans = max(ans, dp[i]);
        }

        return ans;
    }
};
