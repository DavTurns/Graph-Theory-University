#include "Graph.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <list>
#include <queue>
#include <unordered_set>
#include <algorithm>


Graph::Graph(string file) {
    ifstream filestream(file);
    string line, node1, node2;
    bool node1_found, node2_found;

    while (getline(filestream, line)) {
        stringstream ss(line);

        ss >> node1 >> node2;
        node1_found = false;
        node2_found = false;

        for (auto node: nodes) {
            if (node1 == node) node1_found = true;
            if (node2 == node) node2_found = true;
        }

        if (!node1_found) nodes.push_back(node1);
        if (!node2_found) nodes.push_back(node2);

        Edge new_edge;
        new_edge.node1 = node1;
        new_edge.node2 = node2;
        edges.push_back(new_edge);
    }

    node_count = nodes.size();
    edge_count = edges.size();
}

bool Graph::every_node_has_even_degree() {
    int degree;

    for (auto node: nodes) {
        degree = 0;

        //count degree
        for (auto edge: edges) {
            if (edge.node1 == node or edge.node2 == node) degree++;
        }
        if (degree % 2 == 1) return false;
    }
    return true;
}

bool Graph::has_multiple_conex_components() {

    list<string> queue;
    unordered_set<string> visited;
    string current_node;

    //select any node
    queue.push_back(nodes[0]);
    visited.insert(nodes[0]);

    while (!queue.empty()) {
        current_node = queue.front();
        queue.pop_front();

        for (auto edge: edges) {
            if (edge.node1 == current_node and visited.find(edge.node2) == visited.end()) {
                queue.push_back(edge.node2);
                visited.insert(edge.node2);
            }
            if (edge.node2 == current_node and visited.find(edge.node1) == visited.end()) {
                queue.push_back(edge.node1);
                visited.insert(edge.node1);
            }
        }
    }

    //if not every node was visited -> multiple conex components
    if (visited.size() < this->node_count) return true;
    return false;
}

void Graph::printEulerianCycle(string start_node) {

    assert(every_node_has_even_degree());
    assert(!has_multiple_conex_components());

    vector<Edge> edges_copy;
    for (auto edge: edges) edges_copy.push_back(edge);

    vector<string> visited_nodes;

    string end_node;
    bool first_edge_added;

    visited_nodes.push_back(start_node);


    while (edges_copy.size() != 0) {

        end_node = start_node;
        first_edge_added = false;
        vector<string> path_nodes;

        while (end_node != start_node or !first_edge_added) {
            for (int i = 0; i< edges_copy.size();i++) {
                if (edges_copy[i].node1 == end_node) {
                    end_node = edges_copy[i].node2;
                    path_nodes.push_back(edges_copy[i].node2);
                    edges_copy.erase(edges_copy.begin() + i);
                    break;
                }

                if (edges_copy[i].node2 == end_node) {
                    end_node = edges_copy[i].node1;
                    path_nodes.push_back(edges_copy[i].node1);
                    edges_copy.erase(edges_copy.begin() + i);
                    break;
                }
            }
            first_edge_added = true;
        }

        //insert closed path into eulerian cycle
        visited_nodes.insert(std::find(visited_nodes.begin(), visited_nodes.end(), start_node)+1,
                             path_nodes.begin(),
                             path_nodes.end());

        //select new start node of next closed path
        int degree;
        for (auto node: visited_nodes) {
            degree = 0;

            //count degree
            for (auto edge: edges_copy) {
                if (edge.node1 == node or edge.node2 == node) degree++;
            }
            if (degree >= 2) {
                start_node = node;
                break;
            }
        }
    }
    cout << "Eulerian cycle: ";
    for(auto node: visited_nodes) cout << node << " ";
}
