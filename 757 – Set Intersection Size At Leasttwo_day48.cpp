class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& A, const vector<int>& B){
            if (A[1] == B[1]) return A[0] > B[0];
            return A[1] < B[1];
        });

        int ans = 0;
        int a = -1e9, b = -1e9; // a < b: last two chosen points
        for (auto &it : intervals) {
            int l = it[0], r = it[1];

            if (l > b) {
                // none of a,b lie in [l,r]
                ans += 2;
                a = r - 1;
                b = r;
            } else if (l > a) {
                // b is inside [l,r], a is not
                ans += 1;
                a = b;
                b = r;
            } else {
                // both a and b already inside [l,r] -> do nothing
            }
        }
        return ans;
    }
};
