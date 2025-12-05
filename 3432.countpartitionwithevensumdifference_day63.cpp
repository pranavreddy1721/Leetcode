class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int n = nums.size();
        int total = accumulate(nums.begin(), nums.end(), 0);
        return (total % 2 == 0) ? (n - 1) : 0;
    }
};
