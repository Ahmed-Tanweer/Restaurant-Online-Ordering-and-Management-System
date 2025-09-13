#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <cstring>
#include <string>
#include <conio.h>
using namespace std;

class Employee {
private:
    static int nextId;
    int id;
    string name;
    string email;
    string password;
    int restaurantId;
    int processedOrderIds[100];
    int processedOrderCount;

    static bool validatePassword(const string& pwd) {
        if (pwd.length() < 8 || pwd.length() > 12) return false;

        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char ch : pwd) {
            if (isupper(ch)) hasUpper = true;
            else if (islower(ch)) hasLower = true;
            else if (isdigit(ch)) hasDigit = true;
            else if (ispunct(ch)) hasSpecial = true;
        }
        return hasUpper && hasLower && hasDigit && hasSpecial;
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

public:
    Employee(const string& name, const string& email, const string& password, int restaurantId)
        : name(name), email(email), restaurantId(restaurantId), processedOrderCount(0) {
        id = nextId++;
        if (validatePassword(password)) {
            this->password = password;
        }
        else {
            cout << "Password must be 8-12 characters long and include uppercase, "
                "lowercase, digits, and special characters.\n";
        }
        memset(processedOrderIds, 0, sizeof(processedOrderIds));
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    int getRestaurantId() const { return restaurantId; }

    void printDetails() const {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Restaurant ID: " << restaurantId << endl;
    }

    bool login() const {
        cout << "Enter password: ";
        string enteredPassword = getMaskedInput();
        if (password == enteredPassword) {
            return true;
        }
        else {
            cout << "Incorrect password. Please try again.\n";
            return false;
        }
    }

    void addProcessedOrder(int orderId) {
        if (processedOrderCount < 100) {
            processedOrderIds[processedOrderCount++] = orderId;
            cout << "Order ID " << orderId << " processed successfully.\n";
        }
        else {
            cout << "Order storage limit reached!\n";
        }
    }

    void viewProcessedOrders() const {
        cout << "Processed Orders:\n";
        for (int i = 0; i < processedOrderCount; ++i) {
            cout << "Order ID: " << processedOrderIds[i] << endl;
        }
    }

    void resetPassword() {
        cout << "Enter new password: ";
        string newPwd = getMaskedInput();
        if (validatePassword(newPwd)) {
            password = newPwd;
            cout << "Password successfully updated!\n";
        }
        else {
            cout << "New password does not meet complexity requirements.\n";
        }
    }

    void editName(const string& newName) {
        name = newName;
    }

    void deliverOrder(int orderId) {
        cout << "Delivering Order ID: " << orderId << " for Restaurant ID: " << restaurantId << endl;
        addProcessedOrder(orderId);
    }

    void viewOrderHistory() const {
        cout << "Order History for Restaurant ID: " << restaurantId << endl;
        viewProcessedOrders();
    }

    void updateOrderStatus(int orderId, const string& status) {
        cout << "Order ID " << orderId << " status updated to: " << status << endl;
    }

    void assignToRestaurant(int newRestaurantId) {
        restaurantId = newRestaurantId;
        cout << "Assigned to Restaurant ID: " << newRestaurantId << endl;
    }
};

#endif