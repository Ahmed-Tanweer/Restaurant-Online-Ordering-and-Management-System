#ifndef REVIEWHEAP_H
#define REVIEWHEAP_H

#include "Review.h"
#include "EmployeeHashTable.h"

class ReviewHeap {
public:
    Review* heap[100];
    int heapSize;
    EmployeeHashTable* employeeTable;

    ReviewHeap(EmployeeHashTable* employeeTable) : heapSize(0), employeeTable(employeeTable) {}

    void addReview(Review* review) {
        if (heapSize >= 100) {
            cout << "Heap is full. Cannot add more reviews." << endl;
            return;
        }

        heap[heapSize++] = review;
        heapifyUp(heapSize - 1);
    }

    Review* removeTop(int employeeId) {
        Employee* employee = employeeTable->getEmployee(employeeId);
        if (!employee) {
            cout << "Access Denied: Employee not found." << endl;
            return nullptr;
        }

        if (employee->getRestaurantId() != heap[0]->restaurantId) {
            cout << "Access Denied: Employee does not belong to this restaurant." << endl;
            return nullptr;
        }

        Review* top = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;
        heapifyDown(0);

        return top;
    }

    void printTopReviews(int n) {
        int count = 0;
        for (int i = 0; i < heapSize && count < n; i++) {
            heap[i]->printReview();
            count++;
        }
    }

    void printAllReviews(int employeeId) {
        Employee* employee = employeeTable->getEmployee(employeeId);
        if (!employee) {
            cout << "Access Denied: Employee not found." << endl;
            return;
        }

        if (employee->getRestaurantId() != heap[0]->restaurantId) {
            cout << "Access Denied: Employee does not belong to this restaurant." << endl;
            return;
        }

        for (int i = 0; i < heapSize; i++) {
            heap[i]->printReview();
        }
    }

private:
    void heapifyUp(int index) {
        while (index > 0 && *heap[index] < *heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heapSize && *heap[left] < *heap[smallest]) {
            smallest = left;
        }
        if (right < heapSize && *heap[right] < *heap[smallest]) {
            smallest = right;
        }
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
};

#endif