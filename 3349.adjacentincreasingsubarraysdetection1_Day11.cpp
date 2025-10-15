class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        // pref[i] = number of consecutive increasing pairs ending at i
        // (i.e. length of run of nums[j] < nums[j+1] that ends at i)
        // pref[0] = 0
        vector<int> pref(n, 0);
        for (int i = 1; i < n; ++i) {
            pref[i] = (nums[i-1] < nums[i]) ? pref[i-1] + 1 : 0;
        }
        // A subarray starting at s of length k is strictly increasing
        // iff pref[s + k - 1] >= k - 1
        for (int s = 0; s + 2*k <= n; ++s) {
            if (pref[s + k - 1] >= k - 1 && pref[s + 2*k - 1] >= k - 1) {
                return true;
            }
        }
        return false;
    }
};
