class Solution {
public:
    unordered_map<string, vector<char>> mp;
    unordered_map<string, bool> memo;

    bool dfs(string row) {
        if (row.size() == 1) return true;
        if (memo.count(row)) return memo[row];

        vector<vector<char>> choices;
        for (int i = 0; i + 1 < row.size(); i++) {
            string key = row.substr(i, 2);
            if (!mp.count(key)) {
                memo[row] = false;
                return false;
            }
            choices.push_back(mp[key]);
        }

        return memo[row] = buildNext(choices, 0, "", row);
    }

    bool buildNext(vector<vector<char>>& choices, int idx, string curr, string& row) {
        if (idx == choices.size())
            return dfs(curr);

        for (char c : choices[idx]) {
            if (buildNext(choices, idx + 1, curr + c, row))
                return true;
        }
        return false;
    }

    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (auto& s : allowed) {
            mp[s.substr(0, 2)].push_back(s[2]);
        }
        return dfs(bottom);
    }
};
