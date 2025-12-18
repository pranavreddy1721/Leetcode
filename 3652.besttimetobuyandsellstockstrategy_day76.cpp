class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        int mid = k / 2;

        vector<long long> A(n), B(n);
        long long base = 0;

        for (int i = 0; i < n; i++) {
            A[i] = 1LL * strategy[i] * prices[i];
            B[i] = prices[i] - A[i];
            base += A[i];
        }

        long long sumA = 0, sumB = 0;

        // initial window
        for (int i = 0; i < mid; i++) sumA += A[i];
        for (int i = mid; i < k; i++) sumB += B[i];

        long long bestGain = max(0LL, -sumA + sumB);

        // slide window
        for (int l = 1; l + k - 1 < n; l++) {
            // remove outgoing
            sumA -= A[l - 1];
            sumB -= B[l + mid - 1];

            // add incoming
            sumA += A[l + mid - 1];
            sumB += B[l + k - 1];

            bestGain = max(bestGain, -sumA + sumB);
        }

        return base + bestGain;
    }
};
