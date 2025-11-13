#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxOperations(string s) {
        long long ones = 0;
        long long ops = 0;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                ones++;
            } else {
                // s[i] == '0'
                // If this ‘0’ is followed by end or a 1,
                // then all the ones before can each perform an operation crossing this zero.
                if (i + 1 == n || s[i + 1] == '1') {
                    ops += ones;
                }
            }
        }
        return ops;
    }
};
