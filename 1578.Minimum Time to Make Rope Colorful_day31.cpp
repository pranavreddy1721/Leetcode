class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int totalTime = 0;
        int n = colors.size();

        for (int i = 1; i < n; i++) {
            if (colors[i] == colors[i - 1]) {
                // Remove the smaller one
                if (neededTime[i] < neededTime[i - 1]) {
                    totalTime += neededTime[i];
                    neededTime[i] = neededTime[i - 1]; // keep the higher time one
                } else {
                    totalTime += neededTime[i - 1];
                }
            }
        }

        return totalTime;
    }
};
