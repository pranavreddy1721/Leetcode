class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        queue<string> q;
        unordered_set<string> vis;
        string ans = s;

        q.push(s);
        vis.insert(s);

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            // Track the lexicographically smallest string
            if (cur < ans) ans = cur;

            // Operation 1: Add 'a' to all odd indices
            string addOp = cur;
            for (int i = 1; i < addOp.size(); i += 2)
                addOp[i] = (addOp[i] - '0' + a) % 10 + '0';
            
            if (!vis.count(addOp)) {
                vis.insert(addOp);
                q.push(addOp);
            }

            // Operation 2: Rotate right by b
            string rotOp = cur.substr(cur.size() - b) + cur.substr(0, cur.size() - b);
            if (!vis.count(rotOp)) {
                vis.insert(rotOp);
                q.push(rotOp);
            }
        }

        return ans;
    }
};
