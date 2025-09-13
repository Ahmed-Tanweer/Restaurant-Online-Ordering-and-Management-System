#ifndef ORDER_H
#define ORDER_H

#include "Customer.h"
#include "Employee.h"
#include "Driver.h"
#include "Dish.h"
#include <iostream>
#include <string>
using namespace std;

class Order {
public:
    int id;
    Dish* dishes[50];
    int dishCount;
    float total;
    int type;
    Customer* customer;
    Employee* employee;
    Driver* deliveryDriver;
    string deliveryLocation;
    int promotionCount;
    static int nextId;
    int totalOrders;
    string status;

    Order(Customer* customer, int type)
        : customer(customer), type(type), employee(nullptr), deliveryDriver(nullptr),
        dishCount(0), total(0.0), promotionCount(0), totalOrders(0),
        status("Pending"), deliveryLocation("") {
        id = nextId++;
    }

    void addDish(Dish* dish) {
        if (dishCount < 50) {
            dishes[dishCount++] = dish;
            total += dish->price;
        }
        else {
            cout << "Cannot add more dishes, maximum limit reached." << endl;
        }
    }

    void calculateTotal() {
        if (promotionCount > 0) {
            float discount = 0;
            if (promotionCount == 1) {
                discount = 0.05f;
            }
            else if (promotionCount == 2) {
                discount = 0.10f;
            }
            else if (promotionCount > 2) {
                discount = 0.15f;
            }
            total -= total * discount;
            cout << "Promotions applied: " << (discount * 100) << "% off" << endl;
        }

        if (type == 2) {
            total += 200;
        }
        else if (type == 3) {
            total += 100;
        }

        if (type == 2) {
            total *= 1.10;
        }
    }

    void printOrderDetails() {
        cout << "Order ID: " << id << endl;
        cout << "Customer: " << (customer ? customer->name : "Unknown") << endl;
        cout << "Order Type: " << (type == 1 ? "Premium" : (type == 2 ? "Express" : "Normal")) << endl;
        cout << "Total: Rs. " << total << endl;
        cout << "Status: " << status << endl;
        cout << "Delivery Location: " << (deliveryLocation.empty() ? "Not Set" : deliveryLocation) << endl;
        cout << "Delivery Driver: " << (deliveryDriver ? deliveryDriver->getName() : "Not Assigned") << endl;
        cout << "Dishes Ordered:" << endl;
        for (int i = 0; i < dishCount; i++) {
            cout << "  - " << dishes[i]->getName() << " | Rs. " << dishes[i]->price << endl;
        }
    }

    void assignDeliveryDriver(Driver* driver) {
        deliveryDriver = driver;
    }

    void setDeliveryLocation(const string& location) {
        deliveryLocation = location;
    }

    void processOrder(Employee* employee, const string& newStatus) {
        this->employee = employee;
        this->status = newStatus;
        cout << "Order processed by: " << employee->getName() << endl;
    }

    bool operator<(const Order& other) const {
        return type > other.type;
    }

    void setTotalOrders(int total) {
        totalOrders = total;
    }

    Employee* getEmployee() const {
        return employee;
    }

    void setStatus(const string& newStatus) {
        status = newStatus;
    }

    void addPromotion() {
        promotionCount++;
        cout << "Promotion added. Total promotions: " << promotionCount << endl;
    }

    void viewBill() {
        cout << "Order ID: " << id << endl;
        cout << "Customer: " << (customer ? customer->name : "Unknown") << endl;
        cout << "Order Type: " << (type == 1 ? "Premium" : (type == 2 ? "Express" : "Normal")) << endl;
        cout << "Dishes Ordered:" << endl;
        for (int i = 0; i < dishCount; i++) {
            cout << "  - " << dishes[i]->getName() << " | Rs. " << dishes[i]->price << endl;
        }
        cout << "Total: Rs. " << total << endl;
        cout << "Status: " << status << endl;
    }
};

#endif