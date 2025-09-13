#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Menu.h"
#include "Employee.h"
#include "Order.h"
#include "ReviewHeap.h"
#include "Admin.h"
#include <iostream>
#include <string>
using namespace std;

class Restaurant {
public:
    int id;
    string name;
    string type;
    Menu* menu;
    Employee* manager;
    Employee* employees[50];
    int employeeCount;
    Order* orderQueue[50];
    int orderCount;
    ReviewHeap* goodReviews;
    ReviewHeap* badReviews;
    string location;

    static int nextId;

    Restaurant(string name, string type, Employee* manager, string location)
        : name(name), type(type), manager(manager), location(location), employeeCount(0), orderCount(0), menu(nullptr) {
        id = nextId++;

        EmployeeHashTable* employeeTable = new EmployeeHashTable();
        goodReviews = new ReviewHeap(employeeTable);
        badReviews = new ReviewHeap(employeeTable);
        delete employeeTable;
    }

    ~Restaurant() {
        delete menu;
        delete goodReviews;
        delete badReviews;
    }

    Menu* getMenu() const {
        return menu;
    }

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    string getLocation() const {
        return location;
    }

    void addDishToMenu(const string& dishName, const string& dishType, double price, Employee* employee) {
        if (menu) {
            Dish* newDish = new Dish(dishName, dishType, price);
            menu->addDish(newDish, *employee);
            cout << "Dish " << dishName << " added successfully to the menu.\n";
        }
        else {
            cout << "No menu assigned to this restaurant.\n";
        }
    }

    void removeDishFromMenu(int dishId, Employee* employee) {
        if (menu) {
            Dish* dishToRemove = menu->getDishById(dishId);
            if (dishToRemove) {
                menu->removeDish(dishToRemove, *employee);
                cout << "Dish with ID " << dishId << " removed successfully from the menu.\n";
            }
            else {
                cout << "Dish with ID " << dishId << " not found in the menu.\n";
            }
        }
        else {
            cout << "No menu assigned to this restaurant.\n";
        }
    }

    void updateOrder(int orderId) {
        bool orderFound = false;

        for (int i = 0; i < orderCount; ++i) {
            if (orderQueue[i]->id == orderId) {
                orderFound = true;
                Order* existingOrder = orderQueue[i];

                if (existingOrder) {
                    cout << "Order found! Adding new dishes...\n";
                    int dishId;
                    while (true) {
                        cout << "Enter Dish ID to add to the order (-1 to stop): ";
                        cin >> dishId;
                        if (dishId == -1) break;

                        Dish* selectedDish = menu->getDishById(dishId);
                        if (selectedDish) {
                            existingOrder->addDish(selectedDish);
                            cout << "Added " << selectedDish->getName() << " to the order.\n";
                        }
                        else {
                            cout << "Invalid Dish ID.\n";
                        }
                    }

                    existingOrder->calculateTotal();
                    existingOrder->printOrderDetails();
                    cout << "Order updated successfully!\n";
                }
                else {
                    cout << "Order not found.\n";
                }
                break;
            }
        }

        if (!orderFound) {
            cout << "Order ID not found in this restaurant.\n";
        }
    }

    void addEmployee(Employee* employee, Admin* admin) {
        if (admin && admin->isDefaultAdmin()) {
            if (employeeCount < 50) {
                employees[employeeCount++] = employee;
                cout << "Employee " << employee->getName() << " added by admin to restaurant " << name << endl;
            }
            else {
                cout << "Cannot add more employees. Maximum limit reached." << endl;
            }
        }
        else {
            cout << "Only the admin can add employees to the restaurant." << endl;
        }
    }

    void removeEmployee(int employeeId, Admin* admin) {
        if (admin && admin->isDefaultAdmin()) {
            for (int i = 0; i < employeeCount; ++i) {
                if (employees[i]->getId() == employeeId) {
                    for (int j = i; j < employeeCount - 1; ++j) {
                        employees[j] = employees[j + 1];
                    }
                    employeeCount--;
                    cout << "Employee with ID " << employeeId << " removed by admin from restaurant " << name << endl;
                    return;
                }
            }
            cout << "Employee with ID " << employeeId << " not found." << endl;
        }
        else {
            cout << "Only the admin can remove employees from the restaurant." << endl;
        }
    }

    void setMenu(Menu* newMenu, Admin* admin) {
        if (admin && admin->isDefaultAdmin()) {
            menu = newMenu;
            cout << "Menu set successfully by admin for restaurant " << name << endl;
        }
        else {
            cout << "Only the admin can set the menu." << endl;
        }
    }

    void updateDetails(string newName, string newType, Employee* newManager, Admin* admin) {
        if (admin && admin->isDefaultAdmin()) {
            name = newName;
            type = newType;
            manager = newManager;
            cout << "Restaurant details updated by admin." << endl;
        }
        else {
            cout << "Only the admin can update restaurant details." << endl;
        }
    }

    void addOrder(Order* newOrder, Admin* admin) {
        if (orderCount < 50) {
            newOrder->setTotalOrders(orderCount + 1);
            orderQueue[orderCount++] = newOrder;
            sortOrders();
            cout << "Order added to queue by admin." << endl;
        }
        else {
            cout << "Order queue is full. Cannot add more orders." << endl;
        }
    }

    void processNextOrder(Employee* employee) {
        if (orderCount > 0) {
            Order* order = orderQueue[0];
            order->processOrder(employee, "Processed");
            for (int i = 1; i < orderCount; ++i) {
                orderQueue[i - 1] = orderQueue[i];
            }
            orderCount--;
        }
        else {
            cout << "No orders to process." << endl;
        }
    }

    void clearOrders(Admin* admin) {
        if (admin && admin->isDefaultAdmin()) {
            orderCount = 0;
            cout << "All orders cleared by admin." << endl;
        }
        else {
            cout << "Only the admin can clear all orders." << endl;
        }
    }

    void addReview(Review* review) {
        if (review->rating >= 4) {
            goodReviews->addReview(review);
        }
        else {
            badReviews->addReview(review);
        }
    }

    void printOrders() const {
        if (orderCount > 0) {
            cout << "Orders in the queue:\n";
            for (int i = 0; i < orderCount; ++i) {
                orderQueue[i]->printOrderDetails();
            }
        }
        else {
            cout << "No orders in the queue.\n";
        }
    }

    void printReviews() const {
        cout << "Top good reviews:\n";
        goodReviews->printTopReviews(5);
        cout << "Top bad reviews:\n";
        badReviews->printTopReviews(5);
    }

    void printDetails() const {
        cout << "Restaurant ID: " << id << "\n"
            << "Name: " << name << "\n"
            << "Type: " << type << "\n"
            << "Location: " << location << "\n";
        if (manager) {
            cout << "Manager: " << manager->getName() << "\n";
        }
        if (employeeCount > 0) {
            cout << "Employees:\n";
            for (int i = 0; i < employeeCount; ++i) {
                cout << "  - " << employees[i]->getName() << " (ID: " << employees[i]->getId() << ")\n";
            }
        }
        if (menu) {
            cout << "Menu available for this restaurant:\n";
            menu->displayMenu();
        }
        cout << "Top good reviews:\n";
        goodReviews->printTopReviews(5);
        cout << "Top bad reviews:\n";
        badReviews->printTopReviews(5);
    }

    void displayPendingOrders() const {
        if (orderCount > 0) {
            cout << "Pending Orders for Restaurant " << name << ":\n";
            for (int i = 0; i < orderCount; ++i) {
                cout << "Order ID: " << orderQueue[i]->id << " - Status: " << orderQueue[i]->status << endl;
            }
        }
        else {
            cout << "No pending orders for Restaurant " << name << ".\n";
        }
    }

    void viewOrderHistory() const {
        if (orderCount == 0) {
            cout << "No orders found in this restaurant." << endl;
        }
        else {
            cout << "Order history for Restaurant: " << name << endl;
            for (int i = 0; i < orderCount; ++i) {
                Order* order = orderQueue[i];
                if (order) {
                    cout << "Order ID: " << order->id << endl;
                    cout << "Customer ID: " << order->customer->id << endl;
                    cout << "Status: " << order->status << endl;
                    cout << "Total: Rs. " << order->total << endl;
                    cout << "Dishes Ordered:" << endl;
                    for (int j = 0; j < order->dishCount; ++j) {
                        cout << "  - " << order->dishes[j]->getName() << " | Rs. " << order->dishes[j]->price << endl;
                    }
                }
            }
        }
    }

    bool checkDeliveryService(const string& city) const {
        if (city == location) {
            return true;
        }
        else {
            return false;
        }
    }

    void viewOrderHistoryByCustomer(int customerId) const {
        bool foundOrders = false;
        cout << "Order history for Customer ID: " << customerId << " at Restaurant: " << name << endl;

        for (int i = 0; i < orderCount; ++i) {
            Order* order = orderQueue[i];
            if (order && order->customer && order->customer->id == customerId) {
                foundOrders = true;
                cout << "Order ID: " << order->id << endl;
                cout << "Status: " << order->status << endl;
                cout << "Total: Rs. " << order->total << endl;
                cout << "Dishes Ordered:" << endl;
                for (int j = 0; j < order->dishCount; ++j) {
                    cout << "  - " << order->dishes[j]->getName() << " | Rs. " << order->dishes[j]->price << endl;
                }
                cout << "--------------------------" << endl;
            }
        }

        if (!foundOrders) {
            cout << "No orders found for this customer in this restaurant." << endl;
        }
    }

    void viewCustomerBill(int customerId) const {
        for (int i = 0; i < orderCount; ++i) {
            if (orderQueue[i]->customer && orderQueue[i]->customer->id == customerId) {
                orderQueue[i]->viewBill();
            }
        }
    }

private:
    void sortOrders() {
        for (int i = 0; i < orderCount - 1; ++i) {
            for (int j = i + 1; j < orderCount; ++j) {
                if (*orderQueue[i] < *orderQueue[j]) {
                    Order* temp = orderQueue[i];
                    orderQueue[i] = orderQueue[j];
                    orderQueue[j] = temp;
                }
            }
        }
    }
};

#endif