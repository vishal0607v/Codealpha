#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Create or open the file
    ofstream file;
    file.open(username + ".txt");
    
    // Store the username and password
    file << username << endl;
    file << password << endl;
    file.close();

    cout << "Registration successful!" << endl;
}

bool loginUser() {
    string username, password, un, pw;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Open the file
    ifstream file;
    file.open(username + ".txt");
    
    if (file.is_open()) {
        getline(file, un);
        getline(file, pw);
        file.close();
        
        if (un == username && pw == password) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid username or password." << endl;
            return false;
        }
    } else {
        cout << "User not found." << endl;
        return false;
    }
}

int main() {
    int choice;
    cout << "1. Register\n2. Login\nChoose an option: ";
    cin >> choice;

    if (choice == 1) {
        registerUser();
    } else if (choice == 2) {
        loginUser();
    } else {
        cout << "Invalid option." << endl;
    }

    return 0;
}
