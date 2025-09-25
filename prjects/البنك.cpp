#include <iostream>
#include <fstream>  // For file handling
#include <vector>   // For dynamic account storage
using namespace std;

struct BankAccount {
    int password;
    double balance_YER;
    double balance_SAR;
};

// List of accounts
vector<BankAccount> accounts;

// Function to save accounts to a file
void saveAccounts() {
    ofstream file("accounts.txt");
    if (file.is_open()) {
        int acc = accounts.size();
        file << acc << endl; // Save number of accounts first

        for (int i = 0; i < acc; i++) {
            file << accounts[i].password << " " << accounts[i].balance_YER << " " << accounts[i].balance_SAR << endl;
        }
        file.close();
    } else {
        cout << "⚠️ Error opening file for saving!" << endl;
    }
}

// Function to load accounts from a file
void loadAccounts() {
    ifstream file("accounts.txt");
    if (file.is_open()) {
        int count;
        file >> count;
        accounts.resize(count);
        for (int i = 0; i < count; i++) {
            file >> accounts[i].password >> accounts[i].balance_YER >> accounts[i].balance_SAR;
        }
        file.close();
    } else {
        cout << "📁 No account file found. A new file will be created upon saving." << endl;
    }
}

// Function to create a new account
void createAccount() {
    BankAccount newAccount;
    cout << "🔹 Creating a New Account" << endl;
    cout << "Enter password: ";
    cin >> newAccount.password;
    cout << "Enter initial balance in Yemeni Riyals (YER): ";
    cin >> newAccount.balance_YER;
    cout << "Enter initial balance in Saudi Riyals (SAR): ";
    cin >> newAccount.balance_SAR;

    accounts.push_back(newAccount);
    saveAccounts();
    cout << "✅ Account created successfully!" << endl;
}

// Function to check balance
void checkBalance(BankAccount &account) {
    cout << "💰 Your Current Balance:" << endl;
    cout << "🇾🇪 Yemeni Riyals: " << account.balance_YER << " YER" << endl;
    cout << "🇸🇦 Saudi Riyals: " << account.balance_SAR << " SAR" << endl;
}

// Function to withdraw money
void withdraw(BankAccount &account) {
    int currencyChoice;
    double amount;
    
    cout << "🔹 Select currency to withdraw:" << endl;
    cout << "1. Yemeni Riyals (YER)" << endl;
    cout << "2. Saudi Riyals (SAR)" << endl;
    cout << "Enter choice: ";
    cin >> currencyChoice;

    cout << "Enter withdrawal amount: ";
    cin >> amount;

    if (currencyChoice == 1) {
        if (amount > account.balance_YER) {
            cout << "❌ Insufficient funds!" << endl;
        } else {
            account.balance_YER -= amount;
            cout << "✅ Withdrawal successful! New balance: " << account.balance_YER << " YER" << endl;
            saveAccounts();
        }
    } else if (currencyChoice == 2) {
        if (amount > account.balance_SAR) {
            cout << "❌ Insufficient funds!" << endl;
        } else {
            account.balance_SAR -= amount;
            cout << "✅ Withdrawal successful! New balance: " << account.balance_SAR << " SAR" << endl;
            saveAccounts();
        }
    } else {
        cout << "⚠️ Invalid choice!" << endl;
    }
}

// Function to deposit money
void deposit(BankAccount &account) {
    int currencyChoice;
    double amount;
    
    cout << "🔹 Select currency to deposit:" << endl;
    cout << "1. Yemeni Riyals (YER)" << endl;
    cout << "2. Saudi Riyals (SAR)" << endl;
    cout << "Enter choice: ";
    cin >> currencyChoice;

    cout << "Enter deposit amount: ";
    cin >> amount;

    if (currencyChoice == 1) {
        account.balance_YER += amount;
        cout << "✅ Deposit successful! New balance: " << account.balance_YER << " YER" << endl;
        saveAccounts();
    } else if (currencyChoice == 2) {
        account.balance_SAR += amount;
        cout << "✅ Deposit successful! New balance: " << account.balance_SAR << " SAR" << endl;
        saveAccounts();
    } else {
        cout << "⚠️ Invalid choice!" << endl;
    }
}

int main() {
    loadAccounts();  // Load accounts when the program starts

    int password, choice;
    bool exitProgram = false;

    while (!exitProgram) {
        cout << "\n🔹 **Main Menu** 🔹" << endl;
        cout << "1️⃣ Log in" << endl;
        cout << "2️⃣ Create a New Account" << endl;
        cout << "3️⃣ Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 2) {
            createAccount();
            continue;
        } else if (choice == 3) {
            cout << "👋 Thank you for using our service!" << endl;
            break;
        }

        cout << "🔐 Enter your password: ";
        cin >> password;

        int accountIndex = -1;
        for (size_t i = 0; i < accounts.size(); i++) {
            if (password == accounts[i].password) {
                accountIndex = i;
                break;
            }
        }

        if (accountIndex != -1) {
            BankAccount &account = accounts[accountIndex];
            cout << "🎉 Welcome to the bank!" << endl;

            do {
                cout << "\n🔹 **Banking Services** 🔹" << endl;
                cout << "1️⃣ Check Balance" << endl;
                cout << "2️⃣ Withdraw" << endl;
                cout << "3️⃣ Deposit" << endl;
                cout << "4️⃣ Log out" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        checkBalance(account);
                        break;
                    case 2:
                        withdraw(account);
                        break;
                    case 3:
                        deposit(account);
                        break;
                    case 4:
                        cout << "👋 Thank you for using our service!" << endl;
                        exitProgram = true;
                        break;
                    default:
                        cout << "⚠️ Invalid choice!" << endl;
                }
            } while (choice != 4);
        } else {
            cout << "❌ Incorrect password!" << endl;
        }
    }

    return 0;
}