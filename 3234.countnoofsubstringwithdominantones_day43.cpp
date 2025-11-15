class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        vector<int> P1(n+1, 0);
        vector<int> zeros;

        for (int i = 0; i < n; ++i) {
            P1[i+1] = P1[i] + (s[i] == '1');
            if (s[i] == '0') zeros.push_back(i);
        }

        int Z = zeros.size();
        int B = sqrt(n) + 2;       // at most √n zeros needed
        long long ans = 0;

        for (int l = 0; l < n; ++l) {

            // ======= case k = 0 zeros (zero-free substrings starting at l) =======
            int nextZero = n;
            auto it = lower_bound(zeros.begin(), zeros.end(), l);
            if (it != zeros.end()) nextZero = *it;
            ans += (nextZero - l);     // all r in [l, nextZero-1] are zero-free substrings

            // ======= case k >= 1 zeros =======
            int startIndex = int(it - zeros.begin()); // index of first zero >= l

            for (int k = 1; k <= B; ++k) {
                int idx = startIndex + k - 1;
                if (idx >= Z) break;          // not enough zeros

                int pos = zeros[idx];         // position of k-th zero after l
                int need = k * k;             // ones required
                int base = P1[l];             // ones before l (P1[l] counts ones in s[0..l-1])

                // Find smallest r >= pos such that ones in [l..r] >= need
                int lo = pos, hi = n - 1, best = -1;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    if (P1[mid+1] - base >= need) {
                        best = mid;
                        hi = mid - 1;
                    } else lo = mid + 1;
                }
                if (best == -1) continue;

                // limit r so substring still has exactly k zeros (rightmost zero is zeros[idx])
                int limit = (idx + 1 < Z) ? (zeros[idx + 1] - 1) : (n - 1);
                if (best <= limit) ans += (limit - best + 1);
            }
        }

        return (int)ans;
    }
};
