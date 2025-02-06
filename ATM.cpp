#include <iostream>
using namespace std;

// Class representing a Bank Account
class BankAccount {
private:
    string name; // Account holder's name
    string pin; // Account PIN for authentication
    double balance; // Account balance

public:
    // Constructor to initialize account details
    BankAccount(string nm, string accPin, double initialBalance) {
        name = nm;
        pin = accPin;
        balance = initialBalance;
    }

    // Function to authenticate user with PIN
    bool authenticate(string enteredPin) {
        return (pin == enteredPin);
    }

    // Getter functions to retrieve account details
    string getName() {
        return name;
    }

    string getPin() {
        return pin;
    }

    double getBalance() {
        return balance;
    }

    // Function to deposit money into the account
    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: rs" << balance << endl;
    }

    // Function to withdraw money from the account
    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: rs" << balance << endl;
        } else {
            cout << "Insufficient funds. Withdrawal canceled." << endl;
        }
    }

    // Function to change the PIN of the account
    void changePin(string newPin) {
        pin = newPin;
        cout << "PIN change successful." << endl;
    }
};

int main() {
    // Creating multiple bank accounts
    BankAccount accounts[] = {
        BankAccount("Devang", "1111", 1000.0),
        BankAccount("Pratap", "2222", 5000.0),
        BankAccount("Vinay", "3333", 3000.0)
    };

    // Constants for authentication attempts and number of accounts
    const int NUM_ACCOUNTS = sizeof(accounts) / sizeof(accounts[0]);
    const int MAX_ATTEMPTS = 3;

    cout << "*** Welcome to the ATM ***" << endl;

    string enteredPin;
    int attemptsRemaining = MAX_ATTEMPTS;
    bool authenticated = false;
    int accountIndex = -1;

    // User authentication process
    while (attemptsRemaining > 0 && !authenticated) {
        cout << "Enter PIN: ";
        cin >> enteredPin;

        // Checking PIN against all accounts
        for (int i = 0; i < NUM_ACCOUNTS; i++) {
            if (accounts[i].authenticate(enteredPin)) {
                authenticated = true;
                accountIndex = i;
                cout << "\nWelcome, " << accounts[accountIndex].getName() << "." << endl << endl;
                break;
            }
        }

        if (!authenticated) {
            attemptsRemaining--;
            cout << "Authentication failed. Invalid PIN. Attempts remaining: " << attemptsRemaining << endl;
        }
    }

    if (authenticated) {
        int option;
        double amount;
        string newPin;

        // ATM operations menu
        do {
            cout << "\n*** Menu ***" << endl;
            cout << "1. Check Balance" << endl;
            cout << "2. Deposit" << endl;
            cout << "3. Withdraw" << endl;
            cout << "4. Change PIN" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter option: ";
            cin >> option;

            // Handling user-selected operations
            switch (option) {
                case 1:
                    cout << "Your account balance: rs" << accounts[accountIndex].getBalance() << endl;
                    break;

                case 2:
                    cout << "Enter the amount to deposit: rs";
                    cin >> amount;
                    accounts[accountIndex].deposit(amount);
                    break;

                case 3:
                    cout << "Enter the amount to withdraw: rs";
                    cin >> amount;
                    accounts[accountIndex].withdraw(amount);
                    break;

                case 4: {
                    cout << "Enter old PIN: ";
                    string oldPIN;
                    cin >> oldPIN;
                    if (oldPIN != accounts[accountIndex].getPin()) {
                        cout << "Invalid PIN. Please try again." << endl;
                    } else {
                        cout << "Enter new PIN: ";
                        string newPIN;
                        cin >> newPIN;
                        accounts[accountIndex].changePin(newPIN);
                    }
                    break;
                }
                case 5:
                    cout << "Thank you for using the ATM." << endl;
                    break;

                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } while (option != 5);
    } else {
        cout << "Maximum attempts exceeded. ATM session terminated." << endl;
    }

    return 0;
}
