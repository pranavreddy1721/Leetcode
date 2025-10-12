class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> pac(m, vector<int>(n, 0)), atl(m, vector<int>(n, 0));
        vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
        
        function<void(int,int,vector<vector<int>>&)> dfs = [&](int r, int c, vector<vector<int>>& ocean) {
            ocean[r][c] = 1;
            for (auto [dr,dc]: dirs) {
                int nr = r+dr, nc = c+dc;
                if (nr>=0 && nr<m && nc>=0 && nc<n && !ocean[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                    dfs(nr, nc, ocean);
                }
            }
        };
        
        for (int i=0;i<m;i++) {
            dfs(i,0,pac);
            dfs(i,n-1,atl);
        }
        for (int j=0;j<n;j++) {
            dfs(0,j,pac);
            dfs(m-1,j,atl);
        }
        
        vector<vector<int>> res;
        for (int i=0;i<m;i++) {
            for (int j=0;j<n;j++) {
                if (pac[i][j] && atl[i][j]) res.push_back({i,j});
            }
        }
        return res;
    }
};






