class Solution {
public:
    static constexpr long long INF = 1000000000000000000LL;

    struct Trie {
        int id = -1;
        unordered_map<char, Trie*> next;
    };

    void insert(Trie* root, const string& s, int id) {
        Trie* cur = root;
        for (char c : s) {
            if (!cur->next.count(c))
                cur->next[c] = new Trie();
            cur = cur->next[c];
        }
        cur->id = id;
    }

    long long minimumCost(string source, string target,
                          vector<string>& original,
                          vector<string>& changed,
                          vector<int>& cost) {

        int n = source.size();
        unordered_map<string, int> id;
        int idx = 0;

        for (int i = 0; i < original.size(); i++) {
            if (!id.count(original[i])) id[original[i]] = idx++;
            if (!id.count(changed[i]))  id[changed[i]]  = idx++;
        }

        int M = idx;
        vector<vector<long long>> dist(M, vector<long long>(M, INF));
        for (int i = 0; i < M; i++) dist[i][i] = 0;

        for (int i = 0; i < original.size(); i++) {
            int u = id[original[i]];
            int v = id[changed[i]];
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        for (int k = 0; k < M; k++)
            for (int i = 0; i < M; i++)
                for (int j = 0; j < M; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        Trie* srcTrie = new Trie();
        Trie* tgtTrie = new Trie();
        for (auto& [s, i] : id) {
            insert(srcTrie, s, i);
            insert(tgtTrie, s, i);
        }

        vector<long long> dp(n + 1, INF);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            if (source[i] == target[i])
                dp[i + 1] = min(dp[i + 1], dp[i]);

            Trie* p = srcTrie;
            Trie* q = tgtTrie;

            for (int j = i; j < n; j++) {
                if (!p->next.count(source[j]) ||
                    !q->next.count(target[j])) break;

                p = p->next[source[j]];
                q = q->next[target[j]];

                if (p->id != -1 && q->id != -1) {
                    long long c = dist[p->id][q->id];
                    if (c < INF)
                        dp[j + 1] = min(dp[j + 1], dp[i] + c);
                }
            }
        }

        return dp[n] == INF ? -1 : dp[n];
    }
};
