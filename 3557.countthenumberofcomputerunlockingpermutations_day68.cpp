#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const long long MOD = 1000000007LL;

    long long modpow(long long a, long long b){
        long long r = 1;
        while(b){
            if(b & 1) r = (r * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return r;
    }
    long long modinv(long long x){ return modpow(x, MOD-2); }

    long long comb(long long n, long long k){
        if(k < 0 || k > n) return 0;
        // compute C(n,k) by multiplicative formula using modular inverse for factorial division
        if(k > n-k) k = n-k;
        long long num = 1, den = 1;
        for(long long i = 1; i <= k; ++i){
            num = num * (n - k + i) % MOD;
            den = den * i % MOD;
        }
        return num * modinv(den) % MOD;
    }

    int countPermutations(vector<int>& complexity) {
        int n = complexity.size();

        // Feasibility: for every i >= 1 there must exist j < i with complexity[j] < complexity[i].
        vector<int> prefixMin(n);
        prefixMin[0] = complexity[0];
        for(int i = 1; i < n; ++i) prefixMin[i] = min(prefixMin[i-1], complexity[i]);

        for(int i = 1; i < n; ++i){
            if(prefixMin[i-1] >= complexity[i]) return 0;
        }

        // Build array of (complexity, index) and sort by complexity ascending.
        vector<pair<int,int>> arr;
        arr.reserve(n);
        for(int i = 0; i < n; ++i) arr.emplace_back(complexity[i], i);
        sort(arr.begin(), arr.end());

        long long ans = 1;
        long long L = 1; // computer 0 is initially unlocked

        // Count ways group-by-group in ascending complexity.
        for(int i = 0; i < n; ){
            int j = i;
            int val = arr[i].first;
            int k = 0;
            // Count how many elements in this group are NOT the root (index 0)
            while(j < n && arr[j].first == val){
                if(arr[j].second != 0) ++k;
                ++j;
            }

            if(k == 0){
                // group only contained the root (index 0) or nothing to insert
                i = j;
                continue;
            }

            // ways to interleave k new items with L existing ones, requiring at least
            // one earlier element before the first of this group:
            // choose positions = C(L + k - 1, k)
            long long waysChoose = comb(L + k - 1, k);
            // internal permutations of the k distinct indices:
            long long fact = 1;
            for(int t = 1; t <= k; ++t) fact = fact * t % MOD;

            ans = ans * waysChoose % MOD;
            ans = ans * fact % MOD;

            L += k;
            i = j;
        }

        return (int)ans;
    }
};
