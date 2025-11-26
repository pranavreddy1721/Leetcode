class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();
        // dp[j][r] = number of ways to reach column j in the previous row with remainder r
        vector<vector<int>> dp(n, vector<int>(k, 0));
        
        // start cell
        dp[0][grid[0][0] % k] = 1;
        // initialize first row (only from left)
        for (int j = 1; j < n; ++j) {
            for (int r = 0; r < k; ++r) {
                if (dp[j-1][r] == 0) continue;
                int newR = (r + grid[0][j]) % k;
                dp[j][newR] = (dp[j][newR] + dp[j-1][r]) % MOD;
            }
        }
        
        // process remaining rows
        for (int i = 1; i < m; ++i) {
            vector<vector<int>> newDp(n, vector<int>(k, 0));
            // first column: only from top (previous dp[0])
            for (int r = 0; r < k; ++r) {
                if (dp[0][r] == 0) continue;
                int newR = (r + grid[i][0]) % k;
                newDp[0][newR] = (newDp[0][newR] + dp[0][r]) % MOD;
            }
            // other columns: combine from top (dp[j]) and left (newDp[j-1])
            for (int j = 1; j < n; ++j) {
                // from top (previous row)
                for (int r = 0; r < k; ++r) {
                    if (dp[j][r] == 0) continue;
                    int newR = (r + grid[i][j]) % k;
                    newDp[j][newR] = (newDp[j][newR] + dp[j][r]) % MOD;
                }
                // from left (current row)
                for (int r = 0; r < k; ++r) {
                    if (newDp[j-1][r] == 0) continue;
                    int newR = (r + grid[i][j]) % k;
                    newDp[j][newR] = (newDp[j][newR] + newDp[j-1][r]) % MOD;
                }
            }
            dp.swap(newDp);
        }
        
        return dp[n-1][0];
    }
};
