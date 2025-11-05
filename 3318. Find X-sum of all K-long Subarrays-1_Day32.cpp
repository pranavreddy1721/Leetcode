#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<int> result;

        for (int i = 0; i <= n - k; i++) {
            // Subarray of size k
            vector<int> sub(nums.begin() + i, nums.begin() + i + k);

            // Count frequencies
            unordered_map<int, int> freq;
            for (int num : sub) freq[num]++;

            // Sort by frequency (desc), then value (desc)
            vector<pair<int, int>> freqVec(freq.begin(), freq.end());
            sort(freqVec.begin(), freqVec.end(), [](auto &a, auto &b) {
                if (a.second == b.second)
                    return a.first > b.first;
                return a.second > b.second;
            });

            // Pick top x distinct elements
            unordered_set<int> chosen;
            for (int j = 0; j < min(x, (int)freqVec.size()); j++) {
                chosen.insert(freqVec[j].first);
            }

            // Sum all occurrences of chosen elements
            int sum = 0;
            for (int num : sub)
                if (chosen.count(num))
                    sum += num;

            result.push_back(sum);
        }

        return result;
    }
};
