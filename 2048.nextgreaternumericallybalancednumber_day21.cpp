class Solution {
public:
    bool isBalanced(int x) {
        string s = to_string(x);
        vector<int> freq(10, 0);
        for (char c : s) freq[c - '0']++;
        // For every digit d: if it appears, it must appear exactly d times.
        for (int d = 0; d <= 9; ++d) {
            if (freq[d] != 0 && freq[d] != d) return false;
        }
        return true;
    }

    int nextBeautifulNumber(int n) {
        for (int x = n + 1; ; ++x) {
            if (isBalanced(x)) return x;
        }
        // never reached
        return -1;
    }
};
