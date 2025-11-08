#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumOneBitOperations(int n) {
        if (n == 0) return 0;
        int k = 31 - __builtin_clz(n); // Find most significant bit position
        int mask = 1 << k;
        return (1 << (k + 1)) - 1 - minimumOneBitOperations(n ^ mask);
    }
};
