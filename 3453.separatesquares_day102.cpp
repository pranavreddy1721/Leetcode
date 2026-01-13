class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double totalArea = 0.0;
        double low = 1e18, high = -1e18;

        for (auto &s : squares) {
            double y = s[1], l = s[2];
            totalArea += l * l;
            low = min(low, y);
            high = max(high, y + l);
        }

        double target = totalArea / 2.0;

        for (int iter = 0; iter < 100; iter++) { // enough for 1e-5 precision
            double mid = (low + high) / 2.0;
            double below = 0.0;

            for (auto &s : squares) {
                double y = s[1], l = s[2];
                double h = max(0.0, min(l, mid - y));
                below += l * h;
            }

            if (below < target)
                low = mid;
            else
                high = mid;
        }

        return low;
    }
};
