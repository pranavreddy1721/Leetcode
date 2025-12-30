class Solution {
public:
    bool isMagic(vector<vector<int>>& g, int r, int c) {
        // Center must be 5
        if (g[r+1][c+1] != 5) return false;

        vector<bool> seen(10, false);
        for (int i = r; i < r + 3; i++) {
            for (int j = c; j < c + 3; j++) {
                int v = g[i][j];
                if (v < 1 || v > 9 || seen[v]) return false;
                seen[v] = true;
            }
        }

        int s = g[r][c] + g[r][c+1] + g[r][c+2];

        // rows
        for (int i = 0; i < 3; i++)
            if (g[r+i][c] + g[r+i][c+1] + g[r+i][c+2] != s)
                return false;

        // columns
        for (int j = 0; j < 3; j++)
            if (g[r][c+j] + g[r+1][c+j] + g[r+2][c+j] != s)
                return false;

        // diagonals
        if (g[r][c] + g[r+1][c+1] + g[r+2][c+2] != s) return false;
        if (g[r][c+2] + g[r+1][c+1] + g[r+2][c] != s) return false;

        return true;
    }

    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        int count = 0;

        for (int i = 0; i + 2 < R; i++) {
            for (int j = 0; j + 2 < C; j++) {
                if (isMagic(grid, i, j))
                    count++;
            }
        }
        return count;
    }
};
