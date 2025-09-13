#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>
#include <string>
using namespace std;

class Review {
public:
    int id;
    int rating;
    string description;
    int restaurantId;
    int dishId;
    int customerId;

    static int nextId;

    Review(int rating, const string& description, int customerId, int restaurantId = -1, int dishId = -1)
        : rating(rating), description(description), restaurantId(restaurantId), dishId(dishId), customerId(customerId) {
        id = nextId++;
    }

    void printReview() const {
        cout << "Review ID: " << id << endl;
        cout << "Rating: " << rating << " stars" << endl;
        cout << "Description: " << description << endl;
        cout << "Customer ID: " << customerId << endl;

        if (restaurantId != -1) {
            cout << "Restaurant ID: " << restaurantId << endl;
        }
        if (dishId != -1) {
            cout << "Dish ID: " << dishId << endl;
        }
    }

    bool operator<(const Review& other) const {
        return rating < other.rating;
    }

    bool operator>(const Review& other) const {
        return rating > other.rating;
    }
};

#endif