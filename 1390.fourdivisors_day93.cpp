class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;

        for (int x : nums) {
            int cnt = 0;
            int sum = 0;

            for (int i = 1; i * i <= x; i++) {
                if (x % i == 0) {
                    int d1 = i;
                    int d2 = x / i;

                    cnt++;
                    sum += d1;

                    if (d1 != d2) {
                        cnt++;
                        sum += d2;
                    }

                    if (cnt > 4) break;
                }
            }

            if (cnt == 4) ans += sum;
        }

        return ans;
    }
};
