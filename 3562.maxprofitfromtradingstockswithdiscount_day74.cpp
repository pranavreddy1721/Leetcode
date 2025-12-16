class Solution {
public:
    static constexpr int NEG = -1000000000;

    int n, budget;
    vector<int> present, futurePrice;
    vector<vector<int>> tree;
    vector<vector<int>> dp0, dp1;

    void dfs(int u) {
        vector<int> skip(budget + 1, NEG);
        vector<int> buy0(budget + 1, NEG);
        vector<int> buy1(budget + 1, NEG);

        skip[0] = 0;

        int c0 = present[u];
        int p0 = futurePrice[u] - c0;
        if (c0 <= budget) buy0[c0] = p0;

        int c1 = present[u] / 2;
        int p1 = futurePrice[u] - c1;
        if (c1 <= budget) buy1[c1] = p1;

        for (int v : tree[u]) {
            dfs(v);

            vector<int> nskip(budget + 1, NEG);
            vector<int> nbuy0(budget + 1, NEG);
            vector<int> nbuy1(budget + 1, NEG);

            for (int c = 0; c <= budget; c++) {
                if (skip[c] != NEG) {
                    for (int x = 0; c + x <= budget; x++)
                        if (dp0[v][x] != NEG)
                            nskip[c + x] = max(nskip[c + x], skip[c] + dp0[v][x]);
                }

                if (buy0[c] != NEG) {
                    for (int x = 0; c + x <= budget; x++)
                        if (dp1[v][x] != NEG)
                            nbuy0[c + x] = max(nbuy0[c + x], buy0[c] + dp1[v][x]);
                }

                if (buy1[c] != NEG) {
                    for (int x = 0; c + x <= budget; x++)
                        if (dp1[v][x] != NEG)
                            nbuy1[c + x] = max(nbuy1[c + x], buy1[c] + dp1[v][x]);
                }
            }

            skip = nskip;
            buy0 = nbuy0;
            buy1 = nbuy1;
        }

        dp0[u].assign(budget + 1, NEG);
        dp1[u].assign(budget + 1, NEG);
        for (int c = 0; c <= budget; c++) {
            dp0[u][c] = max(skip[c], buy0[c]);
            dp1[u][c] = max(skip[c], buy1[c]);
        }
    }

    int maxProfit(int n_,
                  vector<int>& present_,
                  vector<int>& future_,
                  vector<vector<int>>& hierarchy,
                  int budget_) {

        n = n_;
        budget = budget_;
        present.assign(n + 1, 0);
        futurePrice.assign(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            present[i] = present_[i - 1];
            futurePrice[i] = future_[i - 1];
        }

        tree.assign(n + 1, {});
        for (auto &e : hierarchy)
            tree[e[0]].push_back(e[1]);

        dp0.assign(n + 1, {});
        dp1.assign(n + 1, {});

        dfs(1);

        int ans = 0;
        for (int c = 0; c <= budget; c++)
            ans = max(ans, dp0[1][c]);

        return ans;
    }
};
