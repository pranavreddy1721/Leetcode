
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        long long nextFree = LLONG_MIN; // smallest value not yet used
        int distinct = 0;

        for (long long x : nums) {
            long long left = x - k;
            long long right = x + k;
            if (nextFree < left) nextFree = left;   // can start at left if earlier positions free
            if (nextFree <= right) {
                distinct++;
                nextFree++; // occupy this number and move to next
            }
        }

        return distinct;
    }
};
