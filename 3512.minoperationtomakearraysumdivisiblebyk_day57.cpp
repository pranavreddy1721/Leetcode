class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        long long S = 0;
        for (int x : nums) S += x;
        int r = S % k;
        return r; // returns 0 when r==0 automatically
    }
};
