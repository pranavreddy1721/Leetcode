class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> graph(n);
        
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});       // normal
            graph[v].push_back({u, 2 * w});   // reversed
        }
        
        const long long INF = 1e18;
        vector<long long> dist(n, INF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
        
        dist[0] = 0;
        pq.push({0, 0});
        
        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();
            
            if (cost > dist[u]) continue;
            
            for (auto &[v, w] : graph[u]) {
                if (dist[v] > cost + w) {
                    dist[v] = cost + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist[n-1] == INF ? -1 : dist[n-1];
    }
};
