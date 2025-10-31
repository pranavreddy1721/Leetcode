#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    // Expected signature by your test harness
    vector<int> getSneakyNumbers(vector<int>& nums) {
        unordered_set<int> seen;
        vector<int> res;
        for (int x : nums) {
            if (seen.count(x)) res.push_back(x);
            else seen.insert(x);
            // stop early if we already found two duplicates
            if (res.size() == 2) break;
        }
        return res;
    }
};
