class Solution {
public:
    int magicalSum(int m, int k, vector<int>& nums) {
        const long long MOD = 1000000007LL;
        using ll = long long;
        int n = nums.size();

        auto modpow = [&](ll a, ll e) {
            ll r = 1;
            while (e) {
                if (e & 1) r = (r * a) % MOD;
                a = (a * a) % MOD;
                e >>= 1;
            }
            return r;
        };

        // factorials and inverse factorials up to m
        vector<ll> fact(m + 1, 1), invfact(m + 1, 1);
        for (int i = 1; i <= m; ++i) fact[i] = fact[i - 1] * i % MOD;
        invfact[m] = modpow(fact[m], MOD - 2);
        for (int i = m; i >= 1; --i) invfact[i - 1] = invfact[i] * i % MOD;

        // precompute powers nums[i]^c for c = 0..m
        vector<vector<ll>> pows(n, vector<ll>(m + 1, 1));
        for (int i = 0; i < n; ++i) {
            ll base = nums[i] % MOD;
            for (int c = 1; c <= m; ++c) pows[i][c] = (pows[i][c - 1] * base) % MOD;
        }

        // dp[carry][ones][l] = coefficient sum (with /c! factors) after processing some positions
        // carry in [0..m], ones in [0..k], l in [0..m]
        // initialize for position -1 (no positions processed)
        int C = m;
        // allocate 3D vectors flattened as vector of size (C+1)*(k+1)*(m+1) for speed
        auto idx = [&](int carry, int ones, int l) {
            return (carry * (k + 1) + ones) * (m + 1) + l;
        };
        int SZ = (C + 1) * (k + 1) * (m + 1);
        vector<ll> dp(SZ, 0), ndp(SZ, 0);
        dp[idx(0,0,0)] = 1;

        for (int pos = 0; pos < n; ++pos) {
            // clear ndp
            fill(ndp.begin(), ndp.end(), 0);
            for (int carry = 0; carry <= C; ++carry) {
                for (int ones = 0; ones <= k; ++ones) {
                    for (int l = 0; l <= m; ++l) {
                        ll cur = dp[idx(carry, ones, l)];
                        if (!cur) continue;
                        int maxC = m - l;
                        // choose c occurrences for this position
                        for (int c = 0; c <= maxC; ++c) {
                            int sum = c + carry;
                            int bit = sum & 1;
                            int carry_out = sum >> 1;
                            int ones2 = ones + bit;
                            if (ones2 > k) continue; // prune
                            int l2 = l + c;
                            // multiply by nums[pos]^c / c!
                            ll add = cur * pows[pos][c] % MOD * invfact[c] % MOD;
                            int id2 = idx(carry_out, ones2, l2);
                            ndp[id2] += add;
                            if (ndp[id2] >= MOD) ndp[id2] -= MOD;
                        }
                    }
                }
            }
            dp.swap(ndp);
        }

        // finish: consider remaining carry bits (may add more ones)
        ll ans = 0;
        for (int carry = 0; carry <= C; ++carry) {
            int pop = __builtin_popcount((unsigned)carry);
            for (int ones = 0; ones <= k; ++ones) {
                int ones_final = ones + pop;
                if (ones_final != k) continue;
                int l = m; // need used exactly m picks
                ll cur = dp[idx(carry, ones, l)];
                if (!cur) continue;
                ans = (ans + cur) % MOD;
            }
        }

        // multiply by m! to account for permutations (we used 1/c! factors)
        ans = ans * fact[m] % MOD;
        return (int)ans;
    }
};
