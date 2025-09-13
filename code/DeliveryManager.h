#ifndef DELIVERYMANAGER_H
#define DELIVERYMANAGER_H

#include <iostream>
#include <climits>
#include <string>
#include "Driver.h"
using namespace std;

class DeliveryManager {
public:
    static const int MAX_LOCATIONS = 50;
    static const int MAX_DRIVERS = 10;
    string locations[MAX_LOCATIONS];
    float distances[MAX_LOCATIONS][MAX_LOCATIONS];
    Driver* drivers[MAX_DRIVERS];
    int locationCount;
    int driverCount;

    DeliveryManager() {
        locationCount = 0;
        driverCount = 0;

        for (int i = 0; i < MAX_LOCATIONS; i++) {
            for (int j = 0; j < MAX_LOCATIONS; j++) {
                distances[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }
    }

    void addDriver(Driver* driver) {
        if (driverCount < MAX_DRIVERS) {
            drivers[driverCount++] = driver;
        }
        else {
            cout << "Cannot add more drivers, maximum limit reached." << endl;
        }
    }

    Driver* assignDriver() {
        for (int i = 0; i < driverCount; ++i) {
            if (drivers[i]->getAvailability()) {
                drivers[i]->setAvailability(false);
                return drivers[i];
            }
        }
        return nullptr;
    }

    void releaseDriver(Driver* driver) {
        driver->setAvailability(true);
    }

    void addEdge(string location1, string location2, float distance) {
        int loc1Index = findLocationIndex(location1);
        int loc2Index = findLocationIndex(location2);

        if (loc1Index == -1) {
            if (locationCount < MAX_LOCATIONS) {
                locations[locationCount++] = location1;
                loc1Index = locationCount - 1;
            }
        }
        if (loc2Index == -1) {
            if (locationCount < MAX_LOCATIONS) {
                locations[locationCount++] = location2;
                loc2Index = locationCount - 1;
            }
        }

        distances[loc1Index][loc2Index] = distance;
        distances[loc2Index][loc1Index] = distance;
    }

    int findLocationIndex(string location) {
        for (int i = 0; i < locationCount; i++) {
            if (locations[i] == location) {
                return i;
            }
        }
        return -1;
    }

    float calculateShortestPath(string startLocation, string endLocation) {
        int startIdx = findLocationIndex(startLocation);
        int endIdx = findLocationIndex(endLocation);

        if (startIdx == -1 || endIdx == -1) {
            cout << "Location not found!" << endl;
            return -1;
        }

        float dist[MAX_LOCATIONS];
        bool visited[MAX_LOCATIONS] = { false };

        for (int i = 0; i < locationCount; i++) {
            dist[i] = INT_MAX;
        }
        dist[startIdx] = 0;

        for (int i = 0; i < locationCount; i++) {
            int u = -1;
            for (int j = 0; j < locationCount; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INT_MAX) break;

            visited[u] = true;

            for (int v = 0; v < locationCount; v++) {
                if (distances[u][v] != INT_MAX && dist[u] + distances[u][v] < dist[v]) {
                    dist[v] = dist[u] + distances[u][v];
                }
            }
        }

        return dist[endIdx];
    }
};

#endif