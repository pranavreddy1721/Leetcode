class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        // Sort by start time
        sort(events.begin(), events.end());

        int n = events.size();

        // maxSuffix[i] = max value from i to end
        vector<int> maxSuffix(n);
        maxSuffix[n - 1] = events[n - 1][2];

        for (int i = n - 2; i >= 0; --i) {
            maxSuffix[i] = max(maxSuffix[i + 1], events[i][2]);
        }

        int ans = 0;

        for (int i = 0; i < n; ++i) {
            int start = events[i][0];
            int end = events[i][1];
            int val = events[i][2];

            // Take only this event
            ans = max(ans, val);

            // Binary search for next valid event
            int lo = i + 1, hi = n - 1;
            int idx = -1;

            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (events[mid][0] >= end + 1) {
                    idx = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }

            // Combine with best future event
            if (idx != -1) {
                ans = max(ans, val + maxSuffix[idx]);
            }
        }

        return ans;
    }
};
