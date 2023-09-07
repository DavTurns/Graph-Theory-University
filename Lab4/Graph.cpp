#include "Graph.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <list>

using namespace std;

Graph::Graph(string datei) {
    ifstream in(datei);

    in >> node_count;
    in >> edge_count;
    int x, y;
    //generate Matrix
    for (int i = 0; i < edge_count; i++) {

        in >> x >> y;
        addEdge(x, y);
    }
    in.close();
}

void Graph::addEdge(int x, int y) {
    //lets say x is parent and y is left/right child
    //verify if x exists
    Node *parent = nullptr;
    Node *child = nullptr;

    for (auto node: nodelist) {
        if (node->info == x) {
            parent = node;
        } else if (node->info == y) {
            child = node;
        }
        if (child != nullptr and parent != nullptr) {
            break;
        }
    }

    if (parent == nullptr) {
        parent = new Node;
        parent->info = x;
        nodelist.push_back(parent);
    }

    if (child == nullptr) {
        child = new Node;
        child->info = y;
        nodelist.push_back(child);
    }

    if (parent->info == child->info) {
        parent->adjacent_node_list.push_back(parent);
    }
    parent->adjacent_node_list.push_back(child);
    child->adjacent_node_list.push_back(parent);
}

int Graph::max_degree() {
    int maximum_degree = 0;
    int current_node_degree;
    for (int i = 0; i < edge_count; i++) {
        current_node_degree = nodelist[i]->adjacent_node_list.size();
        if (current_node_degree > maximum_degree)
            maximum_degree = current_node_degree;
    }
    return maximum_degree;
}

int Graph::special_BFS() {
    // returns false if graph is cyclic OR graph has more than 1 conexcomponent

    list<Node *> queue;
    int count_visited_nodes = 1;
    Node *current_node = nullptr;
    vector<int> parent(node_count, -1);
    vector<bool> visited_nodes(node_count, false);

    //select the first node of the list (it is not important which node)
    visited_nodes[nodelist[0]->info] = true;
    queue.push_back(nodelist[0]);

    while (!queue.empty()) {

        current_node = queue.front();
        //cout << current_node->info <<" ";
        queue.erase(queue.begin());

        int adjazenzliste_size = current_node->adjacent_node_list.size();

        for (int i = 0; i < adjazenzliste_size; ++i) {

            Node *current_node_in_adjacency_list = current_node->adjacent_node_list[i];

            if (!visited_nodes[current_node_in_adjacency_list->info]) {
                queue.push_back(current_node_in_adjacency_list);
                visited_nodes[current_node_in_adjacency_list->info] = true;
                parent[current_node_in_adjacency_list->info] = current_node->info;
                count_visited_nodes++;
            } else {
                if (parent[current_node->info] != current_node_in_adjacency_list->info) {
                    //cycle found
                    return false;
                }
            }
        }
    }

    if (count_visited_nodes < this->node_count) return false;
    return true;
}

bool Graph::isBinaryTree() {

    //verify m = n - 1
    if (edge_count != node_count - 1) return false;

    //verify Maxdegree <= 2
    if (max_degree() > 3) return false;

    for (auto node: nodelist) {
        for (auto adjacent_node: node->adjacent_node_list) {
            if (adjacent_node->info == node->info) return false;
        }
    }

    //verify if Graph contains cycles or multiple conexcomponents
    if (!special_BFS()) return false;
    return true;
}

void Graph::print_preorder() {
    //print W - L - R
    //lets assume that the first node in the adjacency list, which isnt its parent,  is L and second node is R

    if (!isBinaryTree()) {
        cout << "Graph isnt a binary tree";
        return;
    }

    cout << "\npreorder: ";
    vector<int> parent(node_count, -1);
    preorder_help_function(nodelist[0], parent);
}

void Graph::preorder_help_function(Node *current_node, vector<int> &parent) {

    cout << current_node->info << " ";
    for (auto node: current_node->adjacent_node_list) {
        if (parent[current_node->info] != node->info) {
            parent[node->info] = current_node->info;
            preorder_help_function(node, parent);
        }

    }
}