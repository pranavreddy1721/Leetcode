class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        vector<bool> result;
        int mod = 0;

        for(int bit : nums){
            mod = (mod * 2 + bit) % 5;
            result.push_back(mod == 0);
        }

        return result;
    }
};
