#ifndef DISH_H
#define DISH_H

#include <iostream>
#include <string>
using namespace std;

class Dish {
public:
    int id;
    string name;
    string type;
    float price;
    Dish* left, * right;

    Dish(string dishName, string dishType, float dishPrice) {
        static int nextDishId = 10000;
        id = nextDishId++;
        name = dishName;
        type = dishType;
        price = dishPrice;
        left = right = nullptr;
    }

    void displayDish() {
        cout << "Dish ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Price: Rs. " << price << endl;
    }

    string getName() const {
        return name;
    }
};

class DishNode {
public:
    Dish* dish;
    DishNode* next;

    DishNode(Dish* dish) : dish(dish), next(nullptr) {}
};

#endif