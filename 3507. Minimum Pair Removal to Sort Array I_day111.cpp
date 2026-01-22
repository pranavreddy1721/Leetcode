class Solution {
public:
    bool isNonDecreasing(const vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) return false;
        }
        return true;
    }

    int minimumPairRemoval(vector<int>& nums) {
        int operations = 0;

        while (!isNonDecreasing(nums)) {
            int minSum = INT_MAX;
            int idx = 0;

            // Find leftmost adjacent pair with minimum sum
            for (int i = 0; i + 1 < nums.size(); i++) {
                int sum = nums[i] + nums[i + 1];
                if (sum < minSum) {
                    minSum = sum;
                    idx = i;
                }
            }

            // Replace the pair with their sum
            nums[idx] = minSum;
            nums.erase(nums.begin() + idx + 1);
            operations++;
        }

        return operations;
    }
};
