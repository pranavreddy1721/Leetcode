class Solution {
public:
    int numberOfWays(string corridor) {
        const long long MOD = 1e9 + 7;
        
        int totalSeats = 0;
        for (char c : corridor)
            if (c == 'S') totalSeats++;
        
        if (totalSeats == 0 || totalSeats % 2 != 0)
            return 0;
        
        long long ways = 1;
        int seatCount = 0;
        int plantsBetween = 0;
        bool betweenSegments = false;
        
        for (char c : corridor) {
            if (c == 'S') {
                seatCount++;
                
                if (seatCount % 2 == 0) {
                    // Finished a segment
                    betweenSegments = true;
                } 
                else if (betweenSegments) {
                    // Starting next segment
                    ways = (ways * (plantsBetween + 1)) % MOD;
                    plantsBetween = 0;
                    betweenSegments = false;
                }
            } 
            else if (betweenSegments) {
                plantsBetween++;
            }
        }
        
        return ways;
    }
};
