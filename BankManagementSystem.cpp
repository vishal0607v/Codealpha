#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Customer {
public:
    string name;
    int customerId;

    Customer(string name, int customerId) : name(name), customerId(customerId) {}
};

class Account {
public:
    int accountNumber;
    double balance;

    Account(int accountNumber, double initialBalance) : accountNumber(accountNumber), balance(initialBalance) {}

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
            return true;
        } else {
            cout << "Insufficient funds." << endl;
            return false;
        }
    }
};

class Transaction {
public:
    int transactionId;
    int accountNumber;
    string type;
    double amount;

    Transaction(int transactionId, int accountNumber, string type, double amount)
        : transactionId(transactionId), accountNumber(accountNumber), type(type), amount(amount) {}
};

class BankingServices {
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> transactions;
    int nextTransactionId;

public:
    BankingServices() : nextTransactionId(1) {}

    void addCustomer(string name, int customerId) {
        customers.push_back(Customer(name, customerId));
        cout << "Customer added successfully." << endl;
    }

    void addAccount(int accountNumber, double initialBalance) {
        accounts.push_back(Account(accountNumber, initialBalance));
        cout << "Account added successfully." << endl;
    }

    void deposit(int accountNumber, double amount) {
        for (auto &account : accounts) {
            if (account.accountNumber == accountNumber) {
                account.deposit(amount);
                transactions.push_back(Transaction(nextTransactionId++, accountNumber, "Deposit", amount));
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void withdraw(int accountNumber, double amount) {
        for (auto &account : accounts) {
            if (account.accountNumber == accountNumber) {
                if (account.withdraw(amount)) {
                    transactions.push_back(Transaction(nextTransactionId++, accountNumber, "Withdraw", amount));
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void transfer(int fromAccountNumber, int toAccountNumber, double amount) {
        Account *fromAccount = nullptr, *toAccount = nullptr;
        for (auto &account : accounts) {
            if (account.accountNumber == fromAccountNumber) {
                fromAccount = &account;
            } else if (account.accountNumber == toAccountNumber) {
                toAccount = &account;
            }
        }
        if (fromAccount && toAccount) {
            if (fromAccount->withdraw(amount)) {
                toAccount->deposit(amount);
                transactions.push_back(Transaction(nextTransactionId++, fromAccountNumber, "Transfer", amount));
                transactions.push_back(Transaction(nextTransactionId++, toAccountNumber, "Receive Transfer", amount));
                cout << "Transfer successful." << endl;
            }
        } else {
            cout << "One or both accounts not found." << endl;
        }
    }

    void viewAccount(int accountNumber) {
        for (const auto &account : accounts) {
            if (account.accountNumber == accountNumber) {
                cout << "Account Number: " << account.accountNumber << endl;
                cout << "Balance: " << account.balance << endl;
                cout << "Recent Transactions:" << endl;
                for (const auto &transaction : transactions) {
                    if (transaction.accountNumber == accountNumber) {
                        cout << "Transaction ID: " << transaction.transactionId << ", Type: " << transaction.type << ", Amount: " << transaction.amount << endl;
                    }
                }
                return;
            }
        }
        cout << "Account not found." << endl;
    }
};

int main() {
    BankingServices bank;
    
    bank.addCustomer("Alice", 1);
    bank.addCustomer("Bob", 2);
    
    bank.addAccount(1001, 500.0);
    bank.addAccount(1002, 300.0);

    bank.deposit(1001, 200.0);
    bank.withdraw(1001, 100.0);
    bank.transfer(1001, 1002, 50.0);
    
    bank.viewAccount(1001);
    bank.viewAccount(1002);
    
    return 0;
}
