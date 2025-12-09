class Solution {
public:
    // main implementation (kept as a named function for clarity)
    int countTriplets(vector<int>& nums) {
        const long long MOD = 1000000007LL;
        long long ans = 0;
        unordered_map<long long, long long> left, right;

        for (int x : nums) right[x]++;

        for (int j = 0; j < (int)nums.size(); ++j) {
            long long val = nums[j];
            right[val]--;  // remove current j from right

            long long target = val * 2;
            if (left.count(target) && right.count(target)) {
                ans = (ans + (left[target] * right[target]) % MOD) % MOD;
            }

            left[val]++;  // add current j to left
        }
        return (int)ans;
    }

    // wrapper with the name the judge is calling
    int specialTriplets(vector<int>& nums) {
        return countTriplets(nums);
    }
};
