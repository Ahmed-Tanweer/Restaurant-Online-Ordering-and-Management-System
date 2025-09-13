#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <conio.h>
#include <cstring>
#include "DeliveryManager.h"
using namespace std;

class Customer {
public:
    int id;
    string name;
    string email;
    string password;
    int reviewIds[50];
    int orderIds[50];
    int restaurantIds[50];
    string orderLocations;
    int reviewCount;
    int orderCount;

    static int nextId;
    static Customer* customerList[100];
    static string availableLocations[10];
    static const int MAX_LOCATIONS = 10;

    Customer(string name, string email, string password)
        : name(name), email(email), password(password), reviewCount(0), orderCount(0) {
        id = nextId++;
        int hashIndex = hashEmail(email);
        customerList[hashIndex] = this;
    }

    ~Customer() {}

    static bool signUp(string name, string email, string password, string confirmPassword) {
        if (!isValidPassword(password)) {
            cout << "Password does not meet the criteria!" << endl;
            return false;
        }
        if (password != confirmPassword) {
            cout << "Passwords do not match!" << endl;
            return false;
        }
        new Customer(name, email, password);
        cout << "Sign up successful!" << endl;
        return true;
    }

    static Customer* logIn(string email, string password) {
        int hashIndex = hashEmail(email);
        Customer* customer = customerList[hashIndex];
        if (customer && customer->password == password) {
            return customer;
        }
        cout << "Invalid login credentials." << endl;
        return nullptr;
    }

    static bool isValidPassword(const string& password) {
        bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
        if (password.length() < 8 || password.length() > 12) return false;
        for (char c : password) {
            if (isupper(c)) hasUpper = true;
            if (islower(c)) hasLower = true;
            if (isdigit(c)) hasDigit = true;
            if (ispunct(c)) hasSpecial = true;
        }
        return hasLower && hasUpper && hasDigit && hasSpecial;
    }

    void editProfile(string newName = "", string newPassword = "") {
        if (!newName.empty()) {
            name = newName;
            cout << "Name updated successfully!" << endl;
        }
        if (!newPassword.empty() && isValidPassword(newPassword)) {
            password = newPassword;
            cout << "Password updated successfully!" << endl;
        }
    }

    void placeOrder(int orderId, int restaurantId, string location) {
        if (orderCount < 50) {
            orderIds[orderCount] = orderId;
            restaurantIds[orderCount] = restaurantId;
            orderLocations = location;
            orderCount++;
        }
        else {
            cout << "Order limit reached." << endl;
        }
    }

    int getRestaurantForOrder(int orderId) {
        for (int i = 0; i < orderCount; ++i) {
            if (orderIds[i] == orderId) {
                return restaurantIds[i];
            }
        }
        cout << "Order ID not found.\n";
        return -1;
    }

    void assignDelivery(int orderId, float deliveryCost) {
        for (int i = 0; i < orderCount; ++i) {
            if (orderIds[i] == orderId) {
                cout << "Delivery cost Rs. " << deliveryCost << " assigned to Order ID: " << orderId << endl;
                return;
            }
        }
        cout << "Order ID not found. Cannot assign delivery." << endl;
    }

    void requestDelivery(int orderId, int locationIndex, const string& destination, DeliveryManager* deliveryManager) {
        string orderLocation = getOrderLocation(orderId);
        if (orderLocation == "Location not found.") {
            cout << "Invalid Order ID. Cannot request delivery." << endl;
            return;
        }

        float deliveryCost = deliveryManager->calculateShortestPath(orderLocation, destination);
        cout << "Delivery requested for Order ID: " << orderId << " to destination: " << destination
            << " with cost: Rs. " << deliveryCost << endl;
    }

    string getOrderLocation(int orderId) {
        for (int i = 0; i < orderCount; ++i) {
            if (orderIds[i] == orderId) {
                return orderLocations;
            }
        }
        return "Location not found.";
    }

    void viewOrderHistory() const {
        if (orderCount == 0) {
            cout << "No orders found." << endl;
        }
        else {
            cout << "Order history: " << endl;
            for (int i = 0; i < orderCount; ++i) {
                cout << "Order ID: " << orderIds[i] << ", Restaurant ID: " << restaurantIds[i] << ", Location: " << orderLocations[i] << endl;
            }
        }
    }

    void viewCurrentOrders() const {
        bool hasOrders = false;
        for (int i = 0; i < orderCount; ++i) {
            if (orderIds[i] != -1) {
                hasOrders = true;
                cout << "Order ID: " << orderIds[i] << ", Restaurant ID: " << restaurantIds[i] << ", Location: " << orderLocations[i] << endl;
            }
        }
        if (!hasOrders) {
            cout << "No current orders." << endl;
        }
    }

    void viewReviews() const {
        if (reviewCount == 0) {
            cout << "No reviews found." << endl;
        }
        else {
            cout << "Your reviews: " << endl;
            for (int i = 0; i < reviewCount; ++i) {
                cout << "Review ID: " << reviewIds[i] << endl;
            }
        }
    }

    void leaveReview(int reviewId) {
        if (reviewCount < 50) {
            reviewIds[reviewCount++] = reviewId;
        }
        else {
            cout << "Review limit reached." << endl;
        }
    }

    void notifyOrderUpdate(string message) {
        cout << "Notification: " << message << endl;
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

    static int hashEmail(const string& email) {
        int sum = 0;
        for (char c : email) {
            sum += c;
        }
        return sum % 100;
    }
};

#endif