#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <set>


struct Edge {
    std::string target;
    double weight;
};

typedef std::map<std::string, std::vector<Edge>> Graph;

Graph readGraphFromFile(const std::string& filename) {
    Graph graph;
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return graph;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty())
            continue;

        size_t pos = line.find(':');
        if (pos == std::string::npos) continue;

        std::string parent = line.substr(0, pos);
        std::string childrenStr = line.substr(pos + 1);

        std::stringstream ss(childrenStr);
        std::string childInfo;
        while (std::getline(ss, childInfo, ';')) {
            if (childInfo.empty()) continue;

            std::stringstream childStream(childInfo);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(childStream, token, ',')) {
                tokens.push_back(token);
            }
            if (tokens.size() != 3) continue;

            std::string target = tokens[0] + "," + tokens[1];
            double weight = std::stod(tokens[2]);

            graph[parent].push_back({ target, weight });
        }
    }

    infile.close();
    return graph;
}

std::vector<std::string> reconstructPath(const std::map<std::string, std::string>& parent,
    const std::string& start, const std::string& goal) {
    std::vector<std::string> path;
    std::string current = goal;
    while (current != start) {
        path.push_back(current);
        auto it = parent.find(current);
        if (it == parent.end()) {
            return std::vector<std::string>();
        }
        current = it->second;
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::string> bfs(const Graph& graph, const std::string& start, const std::string& goal) {
    std::queue<std::string> q;
    std::set<std::string> visited;
    std::map<std::string, std::string> parent;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        if (current == goal) {
            return reconstructPath(parent, start, goal);
        }

        if (graph.find(current) != graph.end()) {
            for (const Edge& edge : graph.at(current)) {
                if (visited.find(edge.target) == visited.end()) {
                    visited.insert(edge.target);
                    parent[edge.target] = current;
                    q.push(edge.target);
                }
            }
        }
    }
    return std::vector<std::string>();
}

std::vector<std::string> dfs(const Graph& graph, const std::string& start, const std::string& goal) {
    std::stack<std::string> st;
    std::set<std::string> visited;
    std::map<std::string, std::string> parent;

    st.push(start);

    while (!st.empty()) {
        std::string current = st.top();
        st.pop();

        if (visited.find(current) != visited.end())
            continue;
        visited.insert(current);

        if (current == goal) {
            return reconstructPath(parent, start, goal);
        }

        if (graph.find(current) != graph.end()) {
            for (const Edge& edge : graph.at(current)) {
                if (visited.find(edge.target) == visited.end()) {
                    parent[edge.target] = current;
                    st.push(edge.target);
                }
            }
        }
    }
    return std::vector<std::string>();
}


std::vector<std::string> dijkstra(const Graph& graph, const std::string& start, const std::string& goal) {
    std::map<std::string, double> distance;
    std::map<std::string, std::string> parent;


    for (const auto& pair : graph) {
        distance[pair.first] = std::numeric_limits<double>::infinity();
        for (const Edge& edge : pair.second) {
            if (distance.find(edge.target) == distance.end()) {
                distance[edge.target] = std::numeric_limits<double>::infinity();
            }
        }
    }
    distance[start] = 0;

    typedef std::pair<double, std::string> NodePair;
    std::set<NodePair> queue;
    queue.insert({ 0, start });

    while (!queue.empty()) {
        auto it = queue.begin();
        double dist = it->first;
        std::string current = it->second;
        queue.erase(it);

        if (current == goal) {
            return reconstructPath(parent, start, goal);
        }

        if (graph.find(current) != graph.end()) {
            for (const Edge& edge : graph.at(current)) {
                double newDist = dist + edge.weight;
                if (newDist < distance[edge.target]) {
                    auto found = queue.find({ distance[edge.target], edge.target });
                    if (found != queue.end()) {
                        queue.erase(found);
                    }
                    distance[edge.target] = newDist;
                    parent[edge.target] = current;
                    queue.insert({ newDist, edge.target });
                }
            }
        }
    }
    return std::vector<std::string>();
}


void testSmallGraph() {
    Graph smallGraph;
    smallGraph["A"] = { {"B", 2}, {"C", 5} };
    smallGraph["B"] = { {"A", 2}, {"C", 1}, {"D", 3} };
    smallGraph["C"] = { {"A", 5}, {"B", 1}, {"D", 2}, {"E", 3} };
    smallGraph["D"] = { {"B", 3}, {"C", 2}, {"F", 4} };
    smallGraph["E"] = { {"C", 3}, {"F", 1} };
    smallGraph["F"] = { {"D", 4}, {"E", 1} };

    std::string start = "A";
    std::string goal = "F";

    std::cout << "Testing on small graph:" << std::endl;

    std::vector<std::string> pathBFS = bfs(smallGraph, start, goal);
    std::cout << "BFS: ";
    if (pathBFS.empty()) {
        std::cout << "Path not found";
    }
    else {
        for (const auto& node : pathBFS) {
            std::cout << node << " ";
        }
    }
    std::cout << std::endl;

    std::vector<std::string> pathDFS = dfs(smallGraph, start, goal);
    std::cout << "DFS: ";
    if (pathDFS.empty()) {
        std::cout << "Path not found";
    }
    else {
        for (const auto& node : pathDFS) {
            std::cout << node << " ";
        }
    }
    std::cout << std::endl;

    std::vector<std::string> pathDijkstra = dijkstra(smallGraph, start, goal);
    std::cout << "Dijkstra: ";
    if (pathDijkstra.empty()) {
        std::cout << "Path not found";
    }
    else {
        for (const auto& node : pathDijkstra) {
            std::cout << node << " ";
        }
    }
    std::cout << std::endl;
}


int main() {
    std::string homeCoordinates = "30.4750516,59.9836159";
    std::string itmoCoordinates = "30.3377953,59.9210607";



    testSmallGraph();


    Graph spbGraph = readGraphFromFile("spb_graph.txt");

    if (spbGraph.empty()) {
        std::cerr << "Graph from file is empty or not loaded!" << std::endl;
        return 1;
    }

    std::vector<std::string> pathBFS = bfs(spbGraph, homeCoordinates, itmoCoordinates);
    std::vector<std::string> pathDFS = dfs(spbGraph, homeCoordinates, itmoCoordinates);
    std::vector<std::string> pathDijkstra = dijkstra(spbGraph, homeCoordinates, itmoCoordinates);

    std::cout << "Path from home to ITMO (BFS):" << std::endl;
    if (pathBFS.empty()) {
        std::cout << "Path not found" << std::endl;
    }
    else {
        for (const auto& node : pathBFS) {
            std::cout << node << " -> ";
        }
        std::cout << "END" << std::endl;
    }

    std::cout << "Path from home to ITMO (DFS):" << std::endl;
    if (pathDFS.empty()) {
        std::cout << "Path not found" << std::endl;
    }
    else {
        for (const auto& node : pathDFS) {
            std::cout << node << " -> ";
        }
        std::cout << "END" << std::endl;
    }

    std::cout << "Shortest path from home to ITMO (Dijkstra):" << std::endl;
    if (pathDijkstra.empty()) {
        std::cout << "Path not found" << std::endl;
    }
    else {
        for (const auto& node : pathDijkstra) {
            std::cout << node << " -> ";
        }
        std::cout << "END" << std::endl;
    }

    return 0;
}
