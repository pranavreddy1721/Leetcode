class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        vector<int> devices;
        
        // Count devices in each row
        for (auto &row : bank) {
            int cnt = count(row.begin(), row.end(), '1');
            if (cnt > 0) devices.push_back(cnt);
        }
        
        int beams = 0;
        for (int i = 1; i < devices.size(); i++) {
            beams += devices[i - 1] * devices[i];
        }
        
        return beams;
    }
};
