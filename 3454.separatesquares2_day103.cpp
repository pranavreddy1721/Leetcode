#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Event {
        long long y, x1, x2;
        int type; // +1 add, -1 remove
    };

    struct SegTree {
        int n;
        vector<long long> len;
        vector<int> cover;
        vector<long long> xs;

        SegTree(int n, vector<long long>& xs)
            : n(n), len(4*n), cover(4*n), xs(xs) {}

        void pushUp(int node, int l, int r) {
            if (cover[node] > 0) {
                len[node] = xs[r] - xs[l];
            } else if (l + 1 == r) {
                len[node] = 0;
            } else {
                len[node] = len[node*2] + len[node*2+1];
            }
        }

        void update(int node, int l, int r, int ql, int qr, int val) {
            if (qr <= l || r <= ql) return;
            if (ql <= l && r <= qr) {
                cover[node] += val;
                pushUp(node, l, r);
                return;
            }
            int mid = (l + r) / 2;
            update(node*2, l, mid, ql, qr, val);
            update(node*2+1, mid, r, ql, qr, val);
            pushUp(node, l, r);
        }
    };

    double separateSquares(vector<vector<int>>& squares) {
        vector<Event> events;
        vector<long long> xs;

        for (auto& s : squares) {
            long long x = s[0], y = s[1], l = s[2];
            events.push_back({y, x, x + l, +1});
            events.push_back({y + l, x, x + l, -1});
            xs.push_back(x);
            xs.push_back(x + l);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        auto getX = [&](long long x) {
            return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        };

        sort(events.begin(), events.end(),
             [](auto& a, auto& b) { return a.y < b.y; });

        SegTree st(xs.size(), xs);

        vector<tuple<long long, long long, long long>> slabs;
        long long prevY = events[0].y;

        for (int i = 0; i < events.size(); ) {
            long long y = events[i].y;
            long long width = st.len[1];
            if (y > prevY && width > 0) {
                slabs.emplace_back(prevY, y, width);
            }

            while (i < events.size() && events[i].y == y) {
                int l = getX(events[i].x1);
                int r = getX(events[i].x2);
                st.update(1, 0, xs.size() - 1, l, r, events[i].type);
                i++;
            }
            prevY = y;
        }

        long double total = 0;
        for (auto& [y1, y2, w] : slabs)
            total += (long double)(y2 - y1) * w;

        long double half = total / 2.0;
        long double cur = 0;

        for (auto& [y1, y2, w] : slabs) {
            long double area = (long double)(y2 - y1) * w;
            if (cur + area >= half) {
                return (double)(y1 + (half - cur) / w);
            }
            cur += area;
        }
        return 0.0;
    }
};
