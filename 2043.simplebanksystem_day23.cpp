class Bank {
private:
    vector<long long> balance;
    int n;

public:
    // Constructor
    Bank(vector<long long>& balance) {
        this->balance = balance;
        n = balance.size();
    }

    // Transfer money from account1 → account2
    bool transfer(int account1, int account2, long long money) {
        if (account1 < 1 || account1 > n || account2 < 1 || account2 > n)
            return false;
        if (balance[account1 - 1] < money)
            return false;

        balance[account1 - 1] -= money;
        balance[account2 - 1] += money;
        return true;
    }

    // Deposit money into an account
    bool deposit(int account, long long money) {
        if (account < 1 || account > n)
            return false;

        balance[account - 1] += money;
        return true;
    }

    // Withdraw money from an account
    bool withdraw(int account, long long money) {
        if (account < 1 || account > n)
            return false;
        if (balance[account - 1] < money)
            return false;

        balance[account - 1] -= money;
        return true;
    }
};
