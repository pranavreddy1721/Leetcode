class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
        pq.push({grid[0][0], 0, 0});
        dist[0][0] = grid[0][0];
        vector<int> dirs = {0,1,0,-1,0};
        while(!pq.empty()){
            auto cur = pq.top(); pq.pop();
            int t = cur[0], r = cur[1], c = cur[2];
            if(r==n-1 && c==n-1) return t;
            for(int k=0;k<4;k++){
                int nr=r+dirs[k], nc=c+dirs[k+1];
                if(nr>=0 && nr<n && nc>=0 && nc<n){
                    int nt=max(t,grid[nr][nc]);
                    if(nt<dist[nr][nc]){
                        dist[nr][nc]=nt;
                        pq.push({nt,nr,nc});
                    }
                }
            }
        }
        return -1;
    }
};






