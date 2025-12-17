class Solution {
public:
    static const long long NEG = -4e18;
    int n, K;
    vector<int> prices;
    long long dp[1005][505][2][2];
    bool vis[1005][505][2][2];

    long long solve(int idx, int t, int type, int run) {
        if (idx == n) {
            return run == 0 ? 0 : NEG;
        }
        if (vis[idx][t][type][run]) return dp[idx][t][type][run];
        vis[idx][t][type][run] = true;

        long long ans = NEG;
        long long p = prices[idx];

        if (run == 0) {
            // Skip day
            ans = solve(idx + 1, t, type, 0);

            // Start NORMAL transaction (buy)
            ans = max(ans, -p + solve(idx + 1, t, 0, 1));

            // Start SHORT transaction (sell)
            ans = max(ans, +p + solve(idx + 1, t, 1, 1));
        } else {
            // Continue holding
            ans = solve(idx + 1, t, type, 1);

            // Complete transaction
            if (t < K) {
                if (type == 0) { // NORMAL → sell
                    ans = max(ans, p + solve(idx + 1, t + 1, type, 0));
                } else { // SHORT → buy back
                    ans = max(ans, -p + solve(idx + 1, t + 1, type, 0));
                }
            }
        }

        return dp[idx][t][type][run] = ans;
    }

    long long maximumProfit(vector<int>& prices_, int k) {
        prices = prices_;
        n = prices.size();
        K = k;
        memset(vis, false, sizeof(vis));
        return solve(0, 0, 0, 0);
    }
};
