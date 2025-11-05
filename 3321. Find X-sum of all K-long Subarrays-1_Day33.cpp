#include <bits/stdc++.h>
using namespace std;

struct Cmp {
    // order by frequency desc, then value desc
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    }
};

class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<long long> ans;
        if (k == 0 || n == 0) return ans;

        unordered_map<int,int> freq;
        set<pair<int,int>, Cmp> top, rest;
        long long sumTop = 0;

        auto insertPair = [&](const pair<int,int>& p) {
            // insert p = {freq, num}
            if ((int)top.size() < x) {
                top.insert(p);
                sumTop += (long long)p.first * (long long)p.second;
            } else {
                // worst in top is the last element (since top is sorted desc)
                auto worstTopIt = prev(top.end());
                if (Cmp()(*worstTopIt, p)) {
                    // worstTop > p  -> p is worse than worstTop -> put in rest
                    rest.insert(p);
                } else {
                    // p is better than worstTop -> move worstTop to rest, insert p into top
                    pair<int,int> worst = *worstTopIt;
                    sumTop -= (long long)worst.first * (long long)worst.second;
                    top.erase(worstTopIt);
                    rest.insert(worst);

                    top.insert(p);
                    sumTop += (long long)p.first * (long long)p.second;
                }
            }
        };

        auto erasePair = [&](const pair<int,int>& p) {
            // try erase from top first
            auto itTop = top.find(p);
            if (itTop != top.end()) {
                sumTop -= (long long)itTop->first * (long long)itTop->second;
                top.erase(itTop);
                // after removing from top, we may need to pull best from rest into top
                if ((int)top.size() < x && !rest.empty()) {
                    auto itRestBest = rest.begin(); // best in rest
                    pair<int,int> bestRest = *itRestBest;
                    rest.erase(itRestBest);
                    top.insert(bestRest);
                    sumTop += (long long)bestRest.first * (long long)bestRest.second;
                }
                return;
            }
            // otherwise erase from rest
            auto itRest = rest.find(p);
            if (itRest != rest.end()) rest.erase(itRest);
        };

        // initialize first window
        for (int i = 0; i < k; ++i) {
            int num = nums[i];
            int old = freq[num];
            if (old > 0) erasePair({old, num});
            freq[num] = old + 1;
            insertPair({old + 1, num});
        }
        ans.push_back(sumTop);

        // slide window
        for (int i = k; i < n; ++i) {
            int out = nums[i - k];
            int in = nums[i];

            // remove outgoing
            int oldOut = freq[out];
            erasePair({oldOut, out});
            if (oldOut == 1) {
                freq.erase(out);
            } else {
                freq[out] = oldOut - 1;
                insertPair({oldOut - 1, out});
            }

            // add incoming
            int oldIn = freq.count(in) ? freq[in] : 0;
            if (oldIn > 0) erasePair({oldIn, in});
            freq[in] = oldIn + 1;
            insertPair({oldIn + 1, in});

            ans.push_back(sumTop);
        }

        return ans;
    }
};
