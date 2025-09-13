#include <iostream>
#include <conio.h>
#include "Graph.h"
#include "Review.h"
#include "Driver.h"
#include "DeliveryManager.h"
#include "Customer.h"
#include "Admin.h"
#include "Dish.h"
#include "Employee.h"
#include "EmployeeHashTable.h"
#include "User.h"
#include "UserManager.h"
#include "HashMap.h"
#include "Menu.h"
#include "Order.h"
#include "Promotion.h"
#include "PromotionStack.h"
#include "ReviewHeap.h"
#include "Delivery.h"
#include "Restaurant.h"
#include "RestaurantList.h"
#include "FunctionHandlers.h"

using namespace std;

// Initialize static variables
int Review::nextId = 10000;
int Driver::nextDriverId = 1;
int Customer::nextId = 10000;
Customer* Customer::customerList[100] = { nullptr };
string Customer::availableLocations[10] = { "I-11", "Uptown", "Midtown", "Suburbs", "Airport", "Beach", "Park", "Mall", "Hospital", "University" };
int Admin::nextId = 1;
Admin* Admin::adminList[10] = { nullptr };
Admin* Admin::defaultAdmin = nullptr;
int Employee::nextId = 10000;
int Order::nextId = 10000;
int Promotion::nextId = 10000;
int Restaurant::nextId = 10000;

int main() {
    DeliveryManager* deliveryManager = new DeliveryManager();

    // Add locations and edges
    deliveryManager->addEdge("F-12", "G-6", 12);
    deliveryManager->addEdge("G-12", "H-9", 8);
    deliveryManager->addEdge("G-8", "F-12", 7);
    deliveryManager->addEdge("F-9", "I-8", 11);
    deliveryManager->addEdge("G-6", "F-9", 6);
    deliveryManager->addEdge("H-8", "I-10", 2);
    deliveryManager->addEdge("F-11", "H-9", 5);
    deliveryManager->addEdge("F-5", "F-8", 15);
    deliveryManager->addEdge("I-11", "I-9", 7);
    deliveryManager->addEdge("F-12", "F-6", 13);
    deliveryManager->addEdge("H-11", "G-7", 1);
    deliveryManager->addEdge("I-15", "G-12", 3);
    deliveryManager->addEdge("I-12", "H-8", 9);
    deliveryManager->addEdge("I-14", "G-6", 2);
    deliveryManager->addEdge("I-12", "I-9", 8);
    deliveryManager->addEdge("F-12", "I-16", 10);
    deliveryManager->addEdge("F-9", "F-12", 9);
    deliveryManager->addEdge("F-11", "G-9", 10);
    deliveryManager->addEdge("I-14", "G-11", 1);
    deliveryManager->addEdge("F-7", "G-9", 15);
    deliveryManager->addEdge("I-9", "H-10", 4);
    deliveryManager->addEdge("I-16", "G-14", 2);
    deliveryManager->addEdge("F-6", "I-15", 8);
    deliveryManager->addEdge("F-12", "I-14", 13);
    deliveryManager->addEdge("F-9", "H-11", 10);
    deliveryManager->addEdge("H-10", "I-10", 5);
    deliveryManager->addEdge("G-14", "G-12", 14);
    deliveryManager->addEdge("H-11", "G-13", 1);
    deliveryManager->addEdge("I-12", "I-15", 6);
    deliveryManager->addEdge("F-9", "G-10", 3);
    deliveryManager->addEdge("F-5", "F-10", 2);
    deliveryManager->addEdge("G-9", "G-14", 12);
    deliveryManager->addEdge("I-9", "F-11", 14);
    deliveryManager->addEdge("I-16", "F-7", 5);
    deliveryManager->addEdge("F-9", "I-11", 8);
    deliveryManager->addEdge("H-9", "G-7", 2);
    deliveryManager->addEdge("I-8", "G-11", 10);
    deliveryManager->addEdge("H-11", "I-12", 9);
    deliveryManager->addEdge("G-12", "F-8", 4);
    deliveryManager->addEdge("F-10", "F-7", 6);
    deliveryManager->addEdge("F-5", "I-16", 7);
    deliveryManager->addEdge("H-8", "I-16", 13);
    deliveryManager->addEdge("H-9", "G-8", 6);
    deliveryManager->addEdge("I-11", "F-8", 4);
    deliveryManager->addEdge("I-12", "G-12", 15);
    deliveryManager->addEdge("F-6", "I-9", 3);
    deliveryManager->addEdge("I-14", "I-12", 8);
    deliveryManager->addEdge("F-11", "G-5", 1);
    deliveryManager->addEdge("G-8", "I-9", 5);
    deliveryManager->addEdge("H-8", "G-5", 11);
    deliveryManager->addEdge("F-10", "F-11", 6);
    deliveryManager->addEdge("G-10", "F-12", 5);
    deliveryManager->addEdge("G-9", "H-11", 7);
    deliveryManager->addEdge("H-9", "F-9", 11);
    deliveryManager->addEdge("F-12", "F-5", 2);
    deliveryManager->addEdge("F-6", "I-12", 9);
    deliveryManager->addEdge("I-15", "F-12", 14);
    deliveryManager->addEdge("G-5", "I-14", 12);
    deliveryManager->addEdge("F-9", "G-6", 15);
    deliveryManager->addEdge("I-15", "F-9", 7);
    deliveryManager->addEdge("G-8", "G-7", 2);
    deliveryManager->addEdge("F-12", "F-6", 14);
    deliveryManager->addEdge("H-9", "I-8", 3);
    deliveryManager->addEdge("G-10", "F-11", 1);
    deliveryManager->addEdge("I-8", "I-15", 2);
    deliveryManager->addEdge("F-9", "I-16", 9);
    deliveryManager->addEdge("H-9", "I-10", 3);
    deliveryManager->addEdge("H-8", "G-11", 6);
    deliveryManager->addEdge("H-11", "G-12", 4);
    deliveryManager->addEdge("I-9", "G-12", 7);
    deliveryManager->addEdge("I-8", "G-8", 10);
    deliveryManager->addEdge("H-10", "I-8", 5);
    deliveryManager->addEdge("G-12", "I-11", 12);
    deliveryManager->addEdge("I-10", "F-5", 15);
    deliveryManager->addEdge("F-10", "G-10", 13);
    deliveryManager->addEdge("F-6", "F-12", 1);
    deliveryManager->addEdge("I-14", "H-11", 2);
    deliveryManager->addEdge("G-11", "F-10", 5);
    deliveryManager->addEdge("I-10", "I-16", 14);
    deliveryManager->addEdge("F-10", "F-6", 3);
    deliveryManager->addEdge("F-12", "F-8", 6);
    deliveryManager->addEdge("F-8", "F-6", 7);
    deliveryManager->addEdge("G-9", "F-11", 11);
    deliveryManager->addEdge("F-6", "H-9", 12);
    deliveryManager->addEdge("F-8", "G-9", 4);
    deliveryManager->addEdge("F-12", "H-11", 3);
    deliveryManager->addEdge("H-11", "I-15", 5);
    deliveryManager->addEdge("I-12", "G-14", 8);
    deliveryManager->addEdge("G-6", "F-9", 10);
    deliveryManager->addEdge("I-9", "G-11", 9);

    // Initialize global objects
    UserManager userManager;
    RestaurantList restaurantList;
    EmployeeHashTable empTable;
    PromotionStack promoStack;
    Admin* admin = nullptr;

    // Initialize sample data
    initializeSampleData(userManager, restaurantList, admin, empTable, deliveryManager);

    while (true) {
        cout << "\nRestaurant Management System\n"
            << "1. Admin Login\n"
            << "2. Employee Login/Register\n"
            << "3. Customer Login/Register\n"
            << "4. Exit\n"
            << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Enter your Admin Username: ";
            cin >> username;
            cout << "Enter your Admin Password: ";
            password = Admin::getMaskedInput();

            if (Admin::logIn(username, password)) {
                cout << "Admin Login successful.\n";
                handleAdminTasks(admin, restaurantList, empTable, promoStack);
            }
            else {
                cout << "Invalid username or password.\n";
            }
        }
        else if (choice == 2) {
            handleEmployeeLogin(empTable, restaurantList);
        }
        else if (choice == 3) {
            handleCustomerLogin(restaurantList, deliveryManager);
        }
        else if (choice == 4) {
            cout << "Exiting system. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    delete deliveryManager;
    return 0;
}