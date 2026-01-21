class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;

        for (int p : nums) {
            // Hint 2: even numbers are impossible
            if ((p & 1) == 0) {
                ans.push_back(-1);
                continue;
            }

            // count trailing 1s
            int cnt = 0;
            int temp = p;
            while (temp & 1) {
                cnt++;
                temp >>= 1;
            }

            // unset the highest bit among trailing 1s
            int res = p ^ (1 << (cnt - 1));
            ans.push_back(res);
        }

        return ans;
    }
};
