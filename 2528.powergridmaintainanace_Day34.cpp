#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct DSU {
        vector<int> parent, size;
        DSU(int n) {
            parent.resize(n + 1);
            size.assign(n + 1, 1);
            iota(parent.begin(), parent.end(), 0);
        }
        int find(int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        }
        void unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a != b) {
                if (size[a] < size[b]) swap(a, b);
                parent[b] = a;
                size[a] += size[b];
            }
        }
    };

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        DSU dsu(c);

        // Build connected components
        for (auto& e : connections)
            dsu.unite(e[0], e[1]);

        // Map: root -> set of online stations (sorted)
        unordered_map<int, set<int>> compOnline;
        for (int i = 1; i <= c; ++i) {
            int root = dsu.find(i);
            compOnline[root].insert(i);
        }

        vector<bool> online(c + 1, true);
        vector<int> result;

        for (auto& q : queries) {
            int type = q[0], x = q[1];
            int root = dsu.find(x);

            if (type == 1) {
                if (online[x]) {
                    result.push_back(x);
                } else {
                    if (compOnline[root].empty())
                        result.push_back(-1);
                    else
                        result.push_back(*compOnline[root].begin());
                }
            } 
            else if (type == 2) {
                if (online[x]) {
                    online[x] = false;
                    compOnline[root].erase(x);
                }
            }
        }

        return result;
    }
};
