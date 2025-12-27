class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());

        // Min-heap of available rooms
        priority_queue<int, vector<int>, greater<int>> available;
        for (int i = 0; i < n; i++) available.push(i);

        // Min-heap of busy rooms: (endTime, room)
        priority_queue<pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>> busy;

        vector<int> count(n, 0);

        for (auto& m : meetings) {
            long long start = m[0], end = m[1];
            long long duration = end - start;

            // Free rooms that have finished
            while (!busy.empty() && busy.top().first <= start) {
                available.push(busy.top().second);
                busy.pop();
            }

            if (!available.empty()) {
                int room = available.top();
                available.pop();
                busy.push({end, room});
                count[room]++;
            } else {
                // Delay meeting
                auto [freeTime, room] = busy.top();
                busy.pop();
                busy.push({freeTime + duration, room});
                count[room]++;
            }
        }

        // Find room with maximum meetings
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (count[i] > count[ans]) ans = i;
        }
        return ans;
    }
};
