class Solution {
public:
    int countCollisions(string directions) {
        int n = directions.size();
        int left = 0, right = n - 1;

        // Skip all leading 'L' — they move left forever and never collide
        while (left < n && directions[left] == 'L') left++;

        // Skip all trailing 'R' — they move right forever and never collide
        while (right >= 0 && directions[right] == 'R') right--;

        int collisions = 0;

        // Between left and right, every moving car ('L' or 'R') will collide
        for (int i = left; i <= right; i++) {
            if (directions[i] != 'S') collisions++;
        }

        return collisions;
    }
};
