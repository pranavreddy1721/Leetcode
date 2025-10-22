

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        unordered_map<long long,int> freq;
        freq.reserve(n*2);
        for (int x : nums) freq[x]++;

        unordered_map<long long,int> startC, endC;
        startC.reserve(n*2);
        endC.reserve(n*2);
        vector<long long> positions;
        positions.reserve(3*n);

        for (int x : nums) {
            long long L = (long long)x - k;
            long long R = (long long)x + k;
            startC[L] += 1;
            endC[R] += 1;
            positions.push_back(L);
            positions.push_back(R);
            positions.push_back(x);
        }

        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());

        int cur = 0;
        int ans = 1;
        for (long long pos : positions) {
            if (startC.count(pos)) cur += startC[pos];
            int overlap = cur;
            int equal_count = freq.count(pos) ? freq[pos] : 0;
            ans = max(ans, min(overlap, equal_count + numOperations));
            ans = max(ans, min(overlap, numOperations));
            if (endC.count(pos)) cur -= endC[pos];
        }
        return ans;
    }
};
