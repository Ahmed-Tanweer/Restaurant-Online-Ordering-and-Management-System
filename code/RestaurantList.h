#ifndef RESTAURANTLIST_H
#define RESTAURANTLIST_H

#include "Restaurant.h"
#include "Admin.h"

class RestaurantList {
private:
    struct Node {
        Restaurant* restaurant;
        Node* next;

        Node(Restaurant* restaurant) : restaurant(restaurant), next(nullptr) {}
    };

    Node* head;

public:
    RestaurantList() : head(nullptr) {}

    ~RestaurantList() {
        clear();
    }

    void addRestaurant(Restaurant* newRestaurant) {
        Node* newNode = new Node(newRestaurant);
        newNode->next = head;
        head = newNode;
        cout << "Restaurant " << newRestaurant->name << " added successfully.\n";
    }

    void deleteRestaurant(Restaurant* restaurant) {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->restaurant == restaurant) {
                if (previous) {
                    previous->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current->restaurant;
                delete current;
                cout << "Restaurant with ID " << restaurant->getId() << " (" << restaurant->getName() << ") deleted successfully.\n";
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Restaurant not found.\n";
    }

    void deleteRestaurant(int id) {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->restaurant->id == id) {
                if (previous) {
                    previous->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current->restaurant;
                delete current;
                cout << "Restaurant with ID " << id << " deleted successfully.\n";
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Restaurant with ID " << id << " not found.\n";
    }

    int getSize() const {
        int size = 0;
        Node* current = head;
        while (current) {
            ++size;
            current = current->next;
        }
        return size;
    }

    Restaurant* getRestaurant(int index) {
        Node* current = head;
        int count = 0;
        while (current) {
            if (count == index) {
                return current->restaurant;
            }
            current = current->next;
            ++count;
        }
        return nullptr;
    }

    Restaurant* getRestaurantByName(const string& restName) {
        Node* current = head;
        while (current) {
            if (current->restaurant->name == restName) {
                return current->restaurant;
            }
            current = current->next;
        }
        return nullptr;
    }

    Restaurant* getRestaurantById(int id) {
        Node* current = head;
        while (current) {
            if (current->restaurant->id == id) {
                return current->restaurant;
            }
            current = current->next;
        }
        return nullptr;
    }

    void editRestaurant(int id, string newName, string newType, Employee* newManager, Admin* admin) {
        Node* current = head;
        while (current) {
            if (current->restaurant->id == id) {
                current->restaurant->updateDetails(newName, newType, newManager, admin);
                cout << "Restaurant updated successfully.\n";
                return;
            }
            current = current->next;
        }
        cout << "Restaurant with ID " << id << " not found.\n";
    }

    void displayAllRestaurants() {
        Node* current = head;
        if (!current) {
            cout << "No restaurants available.\n";
            return;
        }
        while (current) {
            current->restaurant->printDetails();
            cout << endl;
            current = current->next;
        }
    }

    void displayRestaurantsByType(string type) {
        Node* current = head;
        bool found = false;
        while (current) {
            if (current->restaurant->type == type) {
                current->restaurant->printDetails();
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "No restaurants found with type: " << type << "\n";
        }
    }

    void displayRestaurantById(int id) {
        Restaurant* restaurant = getRestaurantById(id);
        if (restaurant) {
            restaurant->printDetails();
        }
        else {
            cout << "Restaurant with ID " << id << " not found.\n";
        }
    }

    void displayAllPendingOrders() const {
        Node* current = head;
        if (!current) {
            cout << "No restaurants available.\n";
            return;
        }

        bool hasPendingOrders = false;
        while (current) {
            if (current->restaurant->orderCount > 0) {
                current->restaurant->displayPendingOrders();
                hasPendingOrders = true;
            }
            current = current->next;
        }

        if (!hasPendingOrders) {
            cout << "No pending orders in any restaurant.\n";
        }
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete->restaurant;
            delete toDelete;
        }
        head = nullptr;
    }
};

#endif