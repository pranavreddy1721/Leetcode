class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        // 0: empty, 1: guard, 2: wall, 3: guarded

        for (auto& g : guards)
            grid[g[0]][g[1]] = 1;

        for (auto& w : walls)
            grid[w[0]][w[1]] = 2;

        // 4 directions: up, down, left, right
        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        for (auto& g : guards) {
            int r = g[0], c = g[1];
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                while (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != 1 && grid[nr][nc] != 2) {
                    if (grid[nr][nc] == 0) grid[nr][nc] = 3; // mark guarded
                    nr += d[0];
                    nc += d[1];
                }
            }
        }

        int unguarded = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 0)
                    unguarded++;

        return unguarded;
    }
};
