class Solution {
public:
    typedef long long ll;
    unordered_map<ll, int> dp;

    int solve(int i, int mask, bool change, int k, const string &s) {
        int n = s.size();
        if (i == n) return 1;
        ll currState = ((ll)i << 27) | ((ll)mask << 1) | (ll)change;
        if (dp.find(currState) != dp.end()) return dp[currState];
        int val = s[i] - 'a';
        int newMask = mask | (1 << val);
        int count = __builtin_popcount(newMask);
        int maxi = 0;
        if (count > k) {
            maxi = max(maxi, 1 + solve(i + 1, 1 << val, change, k, s));
        } else {
            maxi = max(maxi, solve(i + 1, newMask, change, k, s));
        }
        if (!change) {
            for (int j = 0; j < 26; j++) {
                int changedMask = mask | (1 << j);
                int changedCount = __builtin_popcount(changedMask);
                if (changedCount > k) {
                    maxi = max(maxi, 1 + solve(i + 1, 1 << j, true, k, s));
                } else {
                    maxi = max(maxi, solve(i + 1, changedMask, true, k, s));
                }
            }
        }
        return dp[currState] = maxi;
    }

    int maxPartitionsAfterOperations(string s, int k) {
        dp.clear();
        return solve(0, 0, false, k, s);
    }
};






