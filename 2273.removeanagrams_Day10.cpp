class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> result;
        
        for (auto& w : words) {
            if (!result.empty()) {
                string prev = result.back();
                string curr = w;
                sort(prev.begin(), prev.end());
                sort(curr.begin(), curr.end());
                if (prev == curr) continue;  // anagrams, skip current word
            }
            result.push_back(w);
        }
        
        return result;
    }
};
