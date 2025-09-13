#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <conio.h>
#include "Customer.h"
using namespace std;

class Admin {
public:
    int id;
    string username;
    string password;
    static int nextId;
    static Admin* adminList[10];
    static Admin* defaultAdmin;
    string promoStack[10];
    int promoCount;

    string restaurantNames[10];
    string restaurantTypes[10];
    string restaurantManagers[10];
    int restaurantCount;

    Admin(string username, string password)
        : username(username), password(password), promoCount(0), restaurantCount(0) {
        id = nextId++;
        adminList[id] = this;
    }

    static void initializeDefaultAdmin() {
        if (defaultAdmin == nullptr) {
            defaultAdmin = new Admin("Inam", "Pass0123!");
            defaultAdmin->id = 0;
        }
    }

    ~Admin() {}

    static bool logIn(string username, string password) {
        for (int i = 0; i < nextId; ++i) {
            if (adminList[i] && adminList[i]->username == username && adminList[i]->password == password) {
                cout << "Login successful for " << username << endl;
                return true;
            }
        }
        cout << "Invalid username or password." << endl;
        return false;
    }

    static string getMaskedInput() {
        string input;
        char ch;
        while (true) {
            ch = _getch();
            if (ch == '\r') break;
            if (ch == '\b' && !input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
            else if (ch != '\b') {
                input += ch;
                cout << '*';
            }
        }
        cout << endl;
        return input;
    }

    static void addRestaurant(string name, string type, string manager) {
        if (defaultAdmin != nullptr && defaultAdmin->isDefaultAdmin()) {
            if (!manager.empty()) {
                if (defaultAdmin->restaurantCount < 10) {
                    defaultAdmin->restaurantNames[defaultAdmin->restaurantCount] = name;
                    defaultAdmin->restaurantTypes[defaultAdmin->restaurantCount] = type;
                    defaultAdmin->restaurantManagers[defaultAdmin->restaurantCount] = manager;
                    defaultAdmin->restaurantCount++;
                    cout << "Restaurant '" << name << "' added successfully!" << endl;
                }
                else {
                    cout << "Restaurant limit reached. Cannot add more restaurants." << endl;
                }
            }
            else {
                cout << "A manager must be assigned to the restaurant." << endl;
            }
        }
        else {
            cout << "Insufficient permissions to add a restaurant." << endl;
        }
    }

    bool isDefaultAdmin() {
        return this == defaultAdmin;
    }

    void addPromoCode(const string& promoCode) {
        if (promoCount < 10) {
            promoStack[promoCount++] = promoCode;
            cout << "Promo code '" << promoCode << "' added successfully!" << endl;
        }
        else {
            cout << "Promo stack is full. Cannot add more promo codes." << endl;
        }
    }

    void viewPromoCodes() {
        if (promoCount == 0) {
            cout << "No promo codes available." << endl;
        }
        else {
            cout << "Promo codes available:" << endl;
            for (int i = 0; i < promoCount; ++i) {
                cout << "  - " << promoStack[i] << endl;
            }
        }
    }

    string* getPromoStack() {
        return promoStack;
    }

    void viewAllRestaurants() {
        if (restaurantCount == 0) {
            cout << "No restaurants found." << endl;
        }
        else {
            cout << "List of restaurants:" << endl;
            for (int i = 0; i < restaurantCount; ++i) {
                cout << "Restaurant Name: " << restaurantNames[i]
                    << ", Type: " << restaurantTypes[i]
                    << ", Manager: " << restaurantManagers[i] << endl;
            }
        }
    }

    static void viewAllAdmins() {
        cout << "List of admins:" << endl;
        for (int i = 0; i < nextId; ++i) {
            if (adminList[i] != nullptr) {
                cout << "Admin ID: " << adminList[i]->id << " Username: " << adminList[i]->username << endl;
            }
        }
    }

    static void viewAllCustomers() {
        cout << "List of customers:" << endl;
        for (int i = 0; i < 100; ++i) {
            if (Customer::customerList[i] != nullptr) {
                cout << "Customer ID: " << Customer::customerList[i]->id
                    << " Name: " << Customer::customerList[i]->name << endl;
            }
        }
    }

    static void removeAdmin(int adminId) {
        if (adminList[adminId] != nullptr && adminList[adminId] != defaultAdmin) {
            delete adminList[adminId];
            adminList[adminId] = nullptr;
            cout << "Admin removed successfully!" << endl;
        }
        else {
            cout << "Cannot remove the default admin or an invalid admin." << endl;
        }
    }

    static void resetPassword(int adminId, string newPassword) {
        if (adminList[adminId] != nullptr && adminList[adminId] != defaultAdmin) {
            adminList[adminId]->password = newPassword;
            cout << "Password reset successfully!" << endl;
        }
        else {
            cout << "Password reset not allowed for the default admin." << endl;
        }
    }
};

#endif