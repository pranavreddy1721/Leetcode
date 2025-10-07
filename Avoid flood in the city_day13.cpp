class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, 1);
        unordered_map<int, int> full;
        set<int> dry;
        for (int i = 0; i < n; i++) {
            if (rains[i] == 0) dry.insert(i);
            else {
                ans[i] = -1;
                if (full.count(rains[i])) {
                    auto it = dry.lower_bound(full[rains[i]]);
                    if (it == dry.end()) return {};
                    ans[*it] = rains[i];
                    dry.erase(it);
                }
                full[rains[i]] = i;
            }
        }
        return ans;
    }
};
