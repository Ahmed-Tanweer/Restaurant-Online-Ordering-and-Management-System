#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"

class UserManager {
private:
    struct Node {
        User* user;
        Node* next;
    };

    Node* head;

public:
    UserManager() {
        head = nullptr;
    }

    ~UserManager() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp->user;
            delete temp;
        }
    }

    void addUser(User* user) {
        Node* newNode = new Node();
        newNode->user = user;
        newNode->next = head;
        head = newNode;
    }

    User* loginUser(string userName, string password) {
        Node* current = head;
        while (current != nullptr) {
            if (current->user->name == userName && current->user->password == password) {
                cout << "Login successful!" << endl;
                return current->user;
            }
            current = current->next;
        }
        cout << "Login failed!" << endl;
        return nullptr;
    }

    void createAdmin(string adminName, string adminPassword) {
        User* admin = new User(adminName, adminPassword, true);
        addUser(admin);
        cout << "Admin account created successfully!" << endl;
    }

    void registerUser() {
        string userName, password;
        bool isAdmin;

        cout << "Enter username: ";
        cin >> userName;
        cout << "Enter password: ";
        cin >> password;
        cout << "Is this an admin account? (1 for Yes, 0 for No): ";
        cin >> isAdmin;

        User* newUser = new User(userName, password, isAdmin);
        addUser(newUser);
        cout << (isAdmin ? "Admin" : "User") << " registered successfully!" << endl;
    }

    void displayUsers() {
        Node* current = head;
        while (current != nullptr) {
            cout << "User ID: " << current->user->id << ", Username: "
                << current->user->name << ", Role: "
                << (current->user->isAdmin ? "Admin" : "User") << endl;
            current = current->next;
        }
    }
};

#endif