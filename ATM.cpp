#include <iostream>
using namespace std;

class BankAccount {
private:
    string name;
    string pin;
    double balance;

public:
    BankAccount(string nm,string accPin, double initialBalance) {
        name = nm;
        pin = accPin;
        balance = initialBalance;
    }

    bool authenticate(string enteredPin) {
        return (pin == enteredPin);
    }

    string getName() {
        return name;
    }

    string getPin() {
        return pin;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: rs" << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: rs" << balance << endl;
        } else {
            cout << "Insufficient funds. Withdrawal canceled." << endl;
        }
    }

    void changePin(string newPin) {
        pin = newPin;
        cout << "PIN change successful." << endl;
    }
};

int main() {
    BankAccount accounts[] = {
        BankAccount("Devang","1111", 1000.0),
        BankAccount("Pratap","2222", 5000.0),
        BankAccount("Vinay","3333", 3000.0)
    };

    //BankAccount *B;
    const int NUM_ACCOUNTS = sizeof(accounts) / sizeof(accounts[0]);
    const int MAX_ATTEMPTS = 3;

    cout << "*** Welcome to the ATM ***" << endl;

    string enteredPin;
    int attemptsRemaining = MAX_ATTEMPTS;
    bool authenticated = false;
    int accountIndex = -1;

    while (attemptsRemaining > 0 && !authenticated) {
        cout << "Enter PIN: ";
        cin >> enteredPin;

        for (int i = 0; i < NUM_ACCOUNTS; i++) {
            if (accounts[i].authenticate(enteredPin)) {
                authenticated = true;
                accountIndex = i;
                cout << "\nWelcome, " << accounts[accountIndex].getName() << "." << endl<<endl;
            
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

         
        do {
            //cout << "\nWelcome, " << accounts[accountIndex].getName() << "." << endl<<endl;
            cout << "\n*** Menu ***" << endl;
            cout << "1. Check Balance" << endl;
            cout << "2. Deposit" << endl;
            cout << "3. Withdraw" << endl;
            cout << "4. Change PIN" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter option: ";
            cin >> option;

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

                case 4:{
                        cout << "Enter old PIN: ";
                        string oldPIN;
                        cin >> oldPIN;
                        if (oldPIN != accounts[accountIndex].getPin()) {
                                cout << "Invalid PIN. Please try again." << endl;
                        } 
                        else {
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
