class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size(), m = mana.size();
        // prefix[k] = sum of skill[0..k-1], prefix[0] = 0
        vector<long long> prefix(n+1, 0);
        for (int i = 0; i < n; ++i) prefix[i+1] = prefix[i] + skill[i];

        long long start0 = 0; // S_0 = 0
        for (int j = 1; j < m; ++j) {
            long long bprev = mana[j-1];
            long long bcur  = mana[j];
            long long delta = LLONG_MIN;
            for (int i = 0; i < n; ++i) {
                // bprev * prefix[i+1] - bcur * prefix[i]
                long long val = bprev * prefix[i+1] - bcur * prefix[i];
                if (val > delta) delta = val;
            }
            start0 += delta; // S_j = S_{j-1} + delta
        }

        long long totalSkill = prefix[n];
        // completion time of last potion = S_{m-1} + mana[m-1] * totalSkill
        return start0 + 1LL * mana.back() * totalSkill;
    }
};
