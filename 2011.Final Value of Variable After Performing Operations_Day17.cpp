class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int X = 0;
        for (auto &op : operations) {
            if (op[1] == '+') X++;  // either "++X" or "X++"
            else X--;               // either "--X" or "X--"
        }
        return X;
    }
};
