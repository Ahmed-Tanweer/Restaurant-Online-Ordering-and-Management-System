#ifndef HASHMAP_H
#define HASHMAP_H

#include "User.h"

class HashMap {
private:
    static const int SIZE = 10;
    User* table[SIZE];

    int hashFunction(int id) {
        return id % SIZE;
    }

public:
    HashMap() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void addUser(string name, string password) {
        User* newUser = new User(name, password, false);
        int index = hashFunction(newUser->id);

        if (!table[index]) {
            table[index] = newUser;
        }
        else {
            User* temp = table[index];
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newUser;
        }
        cout << "User " << name << " added with ID: " << newUser->id << endl;
    }

    User* findUser(int id) {
        int index = hashFunction(id);
        User* temp = table[index];
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void displayUsers() {
        for (int i = 0; i < SIZE; i++) {
            if (table[i]) {
                User* temp = table[i];
                while (temp) {
                    cout << "User ID: " << temp->id << ", Name: " << temp->name << endl;
                    temp = temp->next;
                }
            }
        }
    }
};

#endif