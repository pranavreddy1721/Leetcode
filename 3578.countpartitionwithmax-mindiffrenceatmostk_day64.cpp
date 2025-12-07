class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        // f[i] = #ways to partition first i elements (nums[0..i-1])
        // f[0] = 1 (empty prefix)
        vector<long long> f(n + 1, 0), pref(n + 1, 0);
        f[0] = 1;
        pref[0] = 1; // pref[i] = sum_{t=0..i} f[t]

        deque<int> maxdq, mindq;
        int left = 0; // left is index in nums (0-based)

        for (int i = 1; i <= n; ++i) {
            int idx = i - 1; // current element is nums[idx]

            // push current index into deques (maintain monotonicity)
            while (!maxdq.empty() && nums[maxdq.back()] <= nums[idx]) maxdq.pop_back();
            maxdq.push_back(idx);

            while (!mindq.empty() && nums[mindq.back()] >= nums[idx]) mindq.pop_back();
            mindq.push_back(idx);

            // shrink left until window [left .. idx] is valid
            while (!maxdq.empty() && !mindq.empty() && nums[maxdq.front()] - nums[mindq.front()] > k) {
                if (maxdq.front() == left) maxdq.pop_front();
                if (mindq.front() == left) mindq.pop_front();
                ++left;
            }

            // Now all j in [left .. idx] produce valid last segments for f[i].
            // f[i] = sum_{j = left .. idx} f[j] = pref[idx] - pref[left-1]
            long long sumLeft = (left - 1 >= 0) ? pref[left - 1] : 0;
            f[i] = (pref[idx] - sumLeft) % MOD;
            if (f[i] < 0) f[i] += MOD;

            // update prefix
            pref[i] = (pref[i - 1] + f[i]) % MOD;
        }

        return (int)f[n];
    }
};
