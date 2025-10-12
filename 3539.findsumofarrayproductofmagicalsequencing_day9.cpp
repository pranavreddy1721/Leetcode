class Solution {
public:
    int magicalSum(int m, int k, vector<int>& nums) {
        const long long MOD = 1e9 + 7;
        int n = nums.size();

        auto modpow = [&](long long a, long long b) {
            long long res = 1;
            while (b) {
                if (b & 1) res = res * a % MOD;
                a = a * a % MOD;
                b >>= 1;
            }
            return res;
        };

        auto modComb = [&](int n, int r) {
            if (r < 0 || r > n) return 0LL;
            long long res = 1;
            for (int i = 1; i <= r; ++i)
                res = res * (n - i + 1) % MOD * modpow(i, MOD - 2) % MOD;
            return res;
        };

        // Step 1: Compute elementary symmetric sums E[t]
        vector<long long> E(n + 1, 0);
        E[0] = 1;
        for (long long num : nums)
            for (int t = n; t >= 1; --t)
                E[t] = (E[t] + E[t - 1] * num) % MOD;

        // Step 2: Compute f(m, k) = # of sequences of length m using exactly k distinct elements
        long long f = 0;
        for (int j = 0; j <= k; ++j) {
            long long term = modComb(k, j) * modpow(k - j, m) % MOD;
            if (j % 2) f = (f - term + MOD) % MOD;
            else f = (f + term) % MOD;
        }

        // Step 3: Answer = E[k] * f(m, k)
        long long ans = E[k] * f % MOD;
        return (int)ans;
    }
};
