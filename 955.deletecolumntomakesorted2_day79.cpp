class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        vector<bool> sorted(n, false);
        int deletions = 0;

        for (int col = 0; col < m; col++) {
            bool bad = false;
            for (int r = 1; r < n; r++) {
                if (!sorted[r] && strs[r][col] < strs[r - 1][col]) {
                    bad = true;
                    break;
                }
            }

            if (bad) {
                deletions++;
            } else {
                for (int r = 1; r < n; r++) {
                    if (strs[r][col] > strs[r - 1][col]) {
                        sorted[r] = true;
                    }
                }
            }
        }

        return deletions;
    }
};
