#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PairHash {
    size_t operator()(pair<ll,ll> const &p) const noexcept {
        // 64-bit splitmix style combine
        auto splitmix64 = [](uint64_t x) {
            x += 0x9e3779b97f4a7c15ULL;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
            x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
            return x ^ (x >> 31);
        };
        uint64_t a = (uint64_t)p.first + 0x9e3779b97f4a7c15ULL;
        uint64_t b = (uint64_t)p.second + 0x9e3779b97f4a7c15ULL;
        return (size_t)splitmix64(a ^ (b << 1));
    }
};

pair<int,int> normalizeSlope(int x1,int y1,int x2,int y2){
    int dx = x2 - x1, dy = y2 - y1;
    if (dx == 0) return {1,0};
    if (dy == 0) return {0,1};
    int g = std::gcd(dx, dy);
    dx /= g; dy /= g;
    if (dx < 0) { dx = -dx; dy = -dy; }
    return {dy, dx};
}

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        if (n < 4) return 0;

        // slope -> list of lineIds (one per segment)
        unordered_map<pair<ll,ll>, vector<ll>, PairHash> slopeToIntercept;
        slopeToIntercept.reserve(n * 8);

        // midpoint -> list of slope-keys (one per segment)
        unordered_map<pair<ll,ll>, vector<pair<int,int>>, PairHash> midToSlopes;
        midToSlopes.reserve(n * 8);

        // build all segments
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];

                auto s = normalizeSlope(x1,y1,x2,y2);
                int dy = s.first, dx = s.second;
                // line invariant: dy * x - dx * y (same for all points on the same line with this slope)
                ll lineId = (ll)dy * x1 - (ll)dx * y1;

                // slope key as pair<ll,ll> to avoid packing problems
                pair<ll,ll> slopeKey = { (ll)dy, (ll)dx };
                slopeToIntercept[slopeKey].push_back(lineId);

                // midpoint sums (no divide)
                ll mx = (ll)x1 + x2;
                ll my = (ll)y1 + y2;
                midToSlopes[{mx, my}].push_back({dy, dx});
            }
        }

        // count valid base-pairs across slopes
        long long totalValidPairs = 0;

        for (auto &kv : slopeToIntercept) {
            auto &vec = kv.second;
            int k = (int)vec.size();
            if (k < 2) continue;

            // count how many segments lie on each distinct line (lineId)
            unordered_map<ll,int> cnt;
            cnt.reserve(vec.size()*2);
            for (ll id : vec) cnt[id]++;

            // get counts c1, c2, ...
            long long S = 0;
            long long sumsq = 0;
            for (auto &p : cnt) {
                long long c = p.second;
                S += c;
                sumsq += c * c;
            }
            // sum_{i<j} ci * cj = (S^2 - sumsq) / 2
            long long bucketPairs = (S * S - sumsq) / 2;
            totalValidPairs += bucketPairs;
        }

        // count parallelograms via midpoints
        long long parallelograms = 0;
        for (auto &kv : midToSlopes) {
            auto &vec = kv.second;
            int m = (int)vec.size();
            if (m < 2) continue;
            // count per slope within this midpoint
            unordered_map<pair<int,int>, int, function<size_t(pair<int,int> const&)>> slopeCnt(
                0, [](pair<int,int> const &p)->size_t{
                    // small custom hash for pair<int,int>
                    uint64_t a = (uint32_t)p.first;
                    uint64_t b = (uint32_t)p.second;
                    uint64_t x = a * 1000003ULL + b;
                    x ^= x >> 33;
                    return (size_t)x;
                }
            );
            for (auto &s : vec) slopeCnt[s]++;

            long long total = m;
            long long sumsq = 0;
            for (auto &p : slopeCnt) {
                long long c = p.second;
                sumsq += c * c;
            }
            // number of unordered pairs with different slopes:
            // C(total,2) - sum_s C(cnt_s,2) = (total^2 - sumsq)/2
            parallelograms += (total * total - sumsq) / 2;
        }

        long long ans = totalValidPairs - parallelograms;
        if (ans < 0) ans = 0;
        return (int)ans;
    }
};
