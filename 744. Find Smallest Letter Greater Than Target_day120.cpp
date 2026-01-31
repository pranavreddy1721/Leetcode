class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int n = letters.size();
        int left = 0, right = n - 1;
        int ans = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (letters[mid] > target) {
                ans = mid;
                right = mid - 1;   // try to find smaller valid index
            } else {
                left = mid + 1;
            }
        }

        // if no character greater than target exists, wrap around
        return (ans == -1) ? letters[0] : letters[ans];
    }
};
