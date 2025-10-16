class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        unordered_map<int, int> freq;
        for (long long num : nums) {
            int r = ((num % value) + value) % value;
            freq[r]++;
        }
        
        int mex = 0;
        while (true) {
            int r = mex % value;
            if (freq[r] == 0) break;
            freq[r]--;
            mex++;
        }
        return mex;
    }
};
