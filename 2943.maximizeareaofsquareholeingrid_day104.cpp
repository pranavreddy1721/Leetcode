class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());

        int maxH = maxSegment(hBars);
        int maxV = maxSegment(vBars);

        int side = min(maxH, maxV);
        return side * side;
    }

private:
    int maxSegment(const vector<int>& bars) {
        int best = 1;
        int start = bars[0];

        for (int i = 1; i < bars.size(); i++) {
            if (bars[i] != bars[i - 1] + 1) {
                best = max(best, bars[i - 1] - start + 2);
                start = bars[i];
            }
        }

        // last segment
        best = max(best, bars.back() - start + 2);
        return best;
    }
};
