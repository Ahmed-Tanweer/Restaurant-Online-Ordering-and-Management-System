#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

class Graph {
public:
    struct Node {
        int id;
        int x, y;
        Node* next;
    };

    struct Edge {
        Node* from;
        Node* to;
        float weight;
        Edge* next;
    };

    Node* nodes;
    Edge* edges;
    int nodeCount;
    int edgeCount;

    Graph() : nodes(nullptr), edges(nullptr), nodeCount(0), edgeCount(0) {}

    void addNode(int id, int x, int y) {
        Node* newNode = new Node{ id, x, y, nullptr };
        if (!nodes) {
            nodes = newNode;
        }
        else {
            Node* temp = nodes;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        nodeCount++;
    }

    void addEdge(Node* from, Node* to, float weight) {
        Edge* newEdge = new Edge{ from, to, weight, nullptr };
        if (!edges) {
            edges = newEdge;
        }
        else {
            Edge* temp = edges;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newEdge;
        }
        edgeCount++;
    }

    float calculateDistance(int x1, int y1, int x2, int y2) {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    float calculateShortestPath(Node* startNode, Node* endNode) {
        float* dist = new float[nodeCount];
        Node** prev = new Node * [nodeCount];
        bool* visited = new bool[nodeCount] { false };

        for (int i = 0; i < nodeCount; i++) {
            dist[i] = numeric_limits<float>::infinity();
            prev[i] = nullptr;
        }

        dist[startNode->id] = 0;

        for (int i = 0; i < nodeCount; i++) {
            Node* u = nullptr;
            for (Node* temp = nodes; temp != nullptr; temp = temp->next) {
                if (!visited[temp->id] && (u == nullptr || dist[temp->id] < dist[u->id])) {
                    u = temp;
                }
            }

            if (dist[u->id] == numeric_limits<float>::infinity()) break;

            visited[u->id] = true;

            for (Edge* e = edges; e != nullptr; e = e->next) {
                if (e->from == u) {
                    Node* v = e->to;
                    float alt = dist[u->id] + e->weight;
                    if (alt < dist[v->id]) {
                        dist[v->id] = alt;
                        prev[v->id] = u;
                    }
                }
            }
        }

        float shortestPath = dist[endNode->id];
        delete[] dist;
        delete[] prev;
        delete[] visited;
        return shortestPath;
    }
};

#endif