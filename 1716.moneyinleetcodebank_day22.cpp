class Solution {
public:
    int totalMoney(int n) {
        int weeks = n / 7;
        int days = n % 7;
        int total = 0;
        
        // Sum of complete weeks
        for (int i = 0; i < weeks; ++i) {
            total += 7 * (1 + i) + 21; // (1+i) + (2+i) + ... + (7+i) = 28 + 7*i
        }
        
        // Remaining days in the last week
        for (int d = 0; d < days; ++d) {
            total += (weeks + 1) + d;
        }
        
        return total;
    }
};
