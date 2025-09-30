class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for(char c : s) {
            if(c=='(' || c=='{' || c=='[') {
                stk.push(c);
            } else {
                if(stk.empty()) return false;
                char last = stk.top();
                stk.pop();
                if((c==')' && last!='(') ||
                   (c==']' && last!='[') ||
                   (c=='}' && last!='{')) {
                    return false;
                }
            }
        }
        return stk.empty();
    }
};
