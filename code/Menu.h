#ifndef MENU_H
#define MENU_H

#include "Dish.h"
#include "Employee.h"

class Menu {
public:
    int id;
    string restaurantName;
    int totalDishes;
    Dish* root;

    Menu(string restName) {
        static int nextMenuId = 10000;
        id = nextMenuId++;
        restaurantName = restName;
        totalDishes = 0;
        root = nullptr;
    }

    void addDish(Dish* newDish, const Employee& employee) {
        if (employee.getRestaurantId() == id) {
            if (root == nullptr) {
                root = newDish;
                totalDishes++;
            }
            else {
                addDishToTree(root, newDish);
            }
        }
        else {
            cout << "Access Denied: Employee does not belong to this restaurant." << endl;
        }
    }

    void removeDish(Dish* dishToRemove, const Employee& employee) {
        if (employee.getRestaurantId() == id) {
            removeDishFromTree(root, dishToRemove);
            totalDishes--;
        }
        else {
            cout << "Access Denied: Employee does not belong to this restaurant." << endl;
        }
    }

    void displayMenu() {
        displayMenu(root);
    }

    void displayAllDishes() {
        if (root == nullptr) {
            cout << "No dishes available in the menu." << endl;
        }
        else {
            cout << "Menu for " << restaurantName << ":\n";
            displayMenu();
        }
    }

    Dish* getDish(const string& dishName) {
        return getDishFromTree(root, dishName);
    }

    Dish* getDishById(int dishId) {
        return getDishByIdFromTree(root, dishId);
    }

private:
    void addDishToTree(Dish* current, Dish* newDish) {
        if (newDish->price < current->price) {
            if (current->left == nullptr) {
                current->left = newDish;
                totalDishes++;
            }
            else {
                addDishToTree(current->left, newDish);
            }
        }
        else {
            if (current->right == nullptr) {
                current->right = newDish;
                totalDishes++;
            }
            else {
                addDishToTree(current->right, newDish);
            }
        }
    }

    void removeDishFromTree(Dish* current, Dish* dishToRemove) {
        if (current == nullptr) return;

        if (current->left == dishToRemove) {
            current->left = nullptr;
        }
        else if (current->right == dishToRemove) {
            current->right = nullptr;
        }
        else {
            removeDishFromTree(current->left, dishToRemove);
            removeDishFromTree(current->right, dishToRemove);
        }
    }

    void displayMenu(Dish* current) {
        if (current == nullptr) return;
        displayMenu(current->left);
        current->displayDish();
        displayMenu(current->right);
    }

    Dish* getDishFromTree(Dish* current, const string& dishName) {
        if (current == nullptr) {
            return nullptr;
        }
        if (current->name == dishName) {
            return current;
        }
        Dish* leftResult = getDishFromTree(current->left, dishName);
        if (leftResult) {
            return leftResult;
        }
        return getDishFromTree(current->right, dishName);
    }

    Dish* getDishByIdFromTree(Dish* current, int dishId) {
        if (current == nullptr) {
            return nullptr;
        }
        if (current->id == dishId) {
            return current;
        }
        Dish* leftResult = getDishByIdFromTree(current->left, dishId);
        if (leftResult) {
            return leftResult;
        }
        return getDishByIdFromTree(current->right, dishId);
    }
};

#endif