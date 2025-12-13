class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> mentions(numberOfUsers, 0);

        // 1️⃣ Sort events
        sort(events.begin(), events.end(), [](auto &a, auto &b) {
            if (a[1] != b[1])
                return stoi(a[1]) < stoi(b[1]);
            return a[0] == "OFFLINE"; // OFFLINE before MESSAGE
        });

        // 2️⃣ Online users
        set<int> online;
        for (int i = 0; i < numberOfUsers; i++)
            online.insert(i);

        // 3️⃣ wakeUpTime -> users
        map<int, vector<int>> wakeUp;

        for (auto &e : events) {
            int time = stoi(e[1]);

            // 🔥 FIX: wake ALL users whose offline time expired
            while (!wakeUp.empty() && wakeUp.begin()->first <= time) {
                for (int id : wakeUp.begin()->second)
                    online.insert(id);
                wakeUp.erase(wakeUp.begin());
            }

            if (e[0] == "OFFLINE") {
                int id = stoi(e[2]);
                online.erase(id);
                wakeUp[time + 60].push_back(id);
            }
            else { // MESSAGE
                string s = e[2];

                if (s == "ALL") {
                    for (int i = 0; i < numberOfUsers; i++)
                        mentions[i]++;
                }
                else if (s == "HERE") {
                    for (int id : online)
                        mentions[id]++;
                }
                else {
                    stringstream ss(s);
                    string token;
                    while (ss >> token) {
                        int id = stoi(token.substr(2));
                        mentions[id]++;
                    }
                }
            }
        }

        return mentions;
    }
};
