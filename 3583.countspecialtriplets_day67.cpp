class Solution {
public:
    int countTriplets(vector<int>& nums) {
        const long long MOD = 1e9 + 7;
        long long ans = 0;
        unordered_map<long long, long long> left, right;

        for (int x : nums) right[x]++;

        for (int j = 0; j < nums.size(); j++) {
            long long val = nums[j];
            right[val]--;  // remove j from right side

            long long target = val * 2;
            if (left.count(target) && right.count(target)) {
                ans = (ans + (left[target] * right[target]) % MOD) % MOD;
            }

            left[val]++;  // add j to left side
        }
        return ans;
    }
};
