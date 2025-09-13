#ifndef EMPLOYEEHASHTABLE_H
#define EMPLOYEEHASHTABLE_H

#include "Employee.h"

class EmployeeHashTable {
private:
    static const int TABLE_SIZE = 100;

    struct Node {
        Employee* employee;
        Node* next;
        Node(Employee* emp) : employee(emp), next(nullptr) {}
    };

    Node* table[TABLE_SIZE];

    int hashFunction(int id) const {
        return id % TABLE_SIZE;
    }

public:
    EmployeeHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~EmployeeHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    void addEmployee(Employee* emp) {
        int index = hashFunction(emp->getId());
        Node* newNode = new Node(emp);

        if (!table[index]) {
            table[index] = newNode;
        }
        else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    Employee* getEmployee(int id) const {
        int index = hashFunction(id);
        Node* current = table[index];
        while (current) {
            if (current->employee->getId() == id) {
                return current->employee;
            }
            current = current->next;
        }
        return nullptr;
    }

    void deleteEmployee(int id) {
        int index = hashFunction(id);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->employee->getId() == id) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void printAllEmployees() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current) {
                current->employee->printDetails();
                cout << "-------------------\n";
                current = current->next;
            }
        }
    }
};

#endif