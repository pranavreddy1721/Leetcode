class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int totalApples = 0;
        for (int a : apple) totalApples += a;

        sort(capacity.begin(), capacity.end(), greater<int>());

        int used = 0, current = 0;
        for (int c : capacity) {
            current += c;
            used++;
            if (current >= totalApples)
                return used;
        }
        return used; // guaranteed possible by constraints
    }
};
