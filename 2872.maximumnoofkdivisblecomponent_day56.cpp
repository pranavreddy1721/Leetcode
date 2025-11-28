class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        long long ans = 0;
        vector<int> vis(n, 0);

        function<long long(int)> dfs = [&](int u) {
            vis[u] = 1;
            long long sum = values[u];

            for (int v : g[u]) {
                if (!vis[v]) {
                    sum += dfs(v);
                }
            }

            // if subtree sum divisible by k → form a component
            if (sum % k == 0) {
                ans++;
                return 0LL; // cut here
            }
            return sum;
        };

        dfs(0);
        return ans;
    }
};
