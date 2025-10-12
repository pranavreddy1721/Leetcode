class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<long long, long long> sumDamage;
        sumDamage.reserve(power.size() * 2);
        for (int p : power) sumDamage[(long long)p] += (long long)p;

        vector<long long> vals;
        vals.reserve(sumDamage.size());
        for (auto &kv : sumDamage) vals.push_back(kv.first);
        sort(vals.begin(), vals.end());

        int n = (int)vals.size();
        if (n == 0) return 0;
        vector<long long> dp(n, 0);
        dp[0] = sumDamage[vals[0]];

        for (int i = 1; i < n; ++i) {
            long long include = sumDamage[vals[i]];
            long long target = vals[i] - 3; // we can add dp[j] where vals[j] <= vals[i]-3
            int j = (int)(upper_bound(vals.begin(), vals.end(), target) - vals.begin()) - 1;
            if (j >= 0) include += dp[j];
            dp[i] = max(dp[i-1], include);
        }

        return dp[n-1];
    }
};
