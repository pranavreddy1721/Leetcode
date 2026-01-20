class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;

        for (int x : nums) {
            // If x is power of two, impossible
            if ((x & (x - 1)) == 0) {
                ans.push_back(-1);
                continue;
            }

            // Count trailing 1s
            int k = 0;
            int temp = x;
            while (temp & 1) {
                k++;
                temp >>= 1;
            }

            // Remove highest bit from trailing ones
            int val = x - (1 << (k - 1));
            ans.push_back(val);
        }

        return ans;
    }
};
