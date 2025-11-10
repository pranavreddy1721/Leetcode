#include <bits/stdc++.h>
using namespace std;

// Segment tree that returns pair<minValue, indexOfMin> for a range.
// If two values equal, it returns the leftmost index.
struct SegTree {
    int n;
    vector<pair<int,int>> st; // (value, index)
    SegTree(const vector<int>& a) {
        n = (int)a.size();
        st.assign(4*n, {INT_MAX, -1});
        build(1, 0, n-1, a);
    }
    void build(int p, int L, int R, const vector<int>& a) {
        if (L == R) {
            st[p] = {a[L], L};
            return;
        }
        int mid = (L+R)/2;
        build(p<<1, L, mid, a);
        build(p<<1|1, mid+1, R, a);
        st[p] = min(st[p<<1], st[p<<1|1]); // pair compares by first then second
    }
    // query returns {minValue, index}
    pair<int,int> query(int p, int L, int R, int i, int j) {
        if (j < L || R < i) return {INT_MAX, -1};
        if (i <= L && R <= j) return st[p];
        int mid = (L+R)/2;
        return min(query(p<<1, L, mid, i, j), query(p<<1|1, mid+1, R, i, j));
    }
    pair<int,int> query(int i, int j) {
        return query(1, 0, n-1, i, j);
    }
};

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        // Split by zeros: treat each contiguous positive segment separately.
        int ans = 0;
        int i = 0;
        while (i < n) {
            while (i < n && nums[i] == 0) ++i;
            if (i >= n) break;
            int j = i;
            while (j+1 < n && nums[j+1] != 0) ++j;
            // process subarray nums[i..j] (all > 0)
            vector<int> seg(nums.begin()+i, nums.begin()+j+1);
            SegTree st(seg);
            ans += solveSegment(st, seg, 0, (int)seg.size()-1);
            i = j+1;
        }
        return ans;
    }

private:
    // Solve for segment seg[l..r] using segment tree st built on seg
    int solveSegment(SegTree &st, const vector<int>& seg, int l, int r) {
        if (l > r) return 0;
        // Option: remove every element individually
        int optionRemoveAll = r - l + 1;

        // Find minimum value and collect all indices with that minimum within [l,r].
        auto q = st.query(l, r);
        int mn = q.first;
        // Collect all indices with value == mn within [l,r].
        vector<int> positions;
        collectAllMinPositions(st, seg, l, r, mn, positions);

        // Sort positions (collectAllMinPositions may produce arbitrary order)
        sort(positions.begin(), positions.end());

        // cost if we remove all mn in one operation, then solve subsegments between them
        int costUsingMin = 1;
        int curL = l;
        for (int pos : positions) {
            if (curL <= pos - 1) {
                costUsingMin += solveSegment(st, seg, curL, pos - 1);
            }
            curL = pos + 1;
        }
        if (curL <= r) costUsingMin += solveSegment(st, seg, curL, r);

        return min(optionRemoveAll, costUsingMin);
    }

    // Recursively find all indices within [L,R] whose value equals 'mn'
    // Uses queries to locate one min occurrence then recurses left/right.
    void collectAllMinPositions(SegTree &st, const vector<int>& seg,
                                int L, int R, int mn, vector<int>& out) {
        if (L > R) return;
        auto q = st.query(L, R);
        if (q.first != mn) return;
        int idx = q.second;
        out.push_back(idx);
        if (L <= idx-1) collectAllMinPositions(st, seg, L, idx-1, mn, out);
        if (idx+1 <= R) collectAllMinPositions(st, seg, idx+1, R, mn, out);
    }
};

#ifdef LOCAL_TESTING
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> nums1 = {0,2};
    cout << sol.minOperations(nums1) << "\n"; // expected 1

    vector<int> nums2 = {3,1,2,1};
    cout << sol.minOperations(nums2) << "\n"; // expected 3

    vector<int> nums3 = {1,2,1,2,1,2};
    cout << sol.minOperations(nums3) << "\n"; // expected 4

    // Additional small tests
    vector<int> nums4 = {0,0,0};
    cout << sol.minOperations(nums4) << "\n"; // 0

    vector<int> nums5 = {5};
    cout << sol.minOperations(nums5) << "\n"; // 1

    vector<int> nums6 = {2,2,2};
    cout << sol.minOperations(nums6) << "\n"; // 1

    vector<int> nums7 = {2,1,2,1,2};
    cout << sol.minOperations(nums7) << "\n"; // expected 3 (remove all 1s -> then two 2 segments -> 1+1+1=3)
}
#endif
