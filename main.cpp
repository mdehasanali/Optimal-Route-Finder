#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// Graph Edge: destination node, fare (Taka), travel time (Minutes)
struct Edge {
    int to;
    int fare;
    int time;
};

// Global Graph data structures
unordered_map<string, int> nameToId;
unordered_map<int, string> idToName;
unordered_map<string, string> lowerToName; // Case-insensitive input resolver
int nodeCount = 0;
vector<vector<Edge>> adj;

// Helper: Convert string to lowercase
string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

// Add a location to the graph
void addLocation(string name) {
    if (nameToId.find(name) == nameToId.end()) {
        nameToId[name] = nodeCount;
        idToName[nodeCount] = name;
        lowerToName[toLower(name)] = name;
        nodeCount++;
        adj.push_back(vector<Edge>());
    }
}

// Add a bidirectional road segment
void addRoute(string u, string v, int fare, int time) {
    addLocation(u);
    addLocation(v);
    int idU = nameToId[u];
    int idV = nameToId[v];
    adj[idU].push_back({idV, fare, time});
    adj[idV].push_back({idU, fare, time});
}

// Dijkstra's Algorithm implementation
void findRouteToVU(string startInput, int priority) {
    string lowerInput = toLower(startInput);

    // Direct case-insensitive match or common alias matching
    string startLocation = "";
    if (lowerToName.find(lowerInput) != lowerToName.end()) {
        startLocation = lowerToName[lowerInput];
    } else if (lowerInput == "vu" || lowerInput == "kharkhari" || lowerInput == "varendra" || lowerInput == "varendra university") {
        startLocation = "Varendra University (VU)";
    } else if (lowerInput == "ruet") {
        startLocation = "Kazla";
    } else if (lowerInput == "ru" || lowerInput == "varsity") {
        startLocation = "Binodpur";
    } else if (lowerInput == "shaheb bazar" || lowerInput == "saheb bazar") {
        startLocation = "Zero Point";
    } else if (lowerInput == "medical" || lowerInput == "rmch") {
        startLocation = "Laxmipur";
    } else if (lowerInput == "court") {
        startLocation = "Court";
    } else if (lowerInput == "station" || lowerInput == "shiroil") {
        startLocation = "Railgate";
    } else if (lowerInput == "airport") {
        startLocation = "Biman Chattar";
    } else if (lowerInput == "stadium") {
        startLocation = "Terokhadia";
    } else {
        cout << "\n[!] Error: Location '" << startInput << "' not found! Please check spelling from the list.\n";
        return;
    }

    // Target Destination is ALWAYS Varendra University (VU)
    string endLocation = "Varendra University (VU)";
    int startId = nameToId[startLocation];
    int endId = nameToId[endLocation];

    if (startId == endId) {
        cout << "\nYou are already at Varendra University!\n";
        return;
    }

    // Min-Priority Queue storing pair<currentCost, nodeId>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> minCost(nodeCount, INT_MAX);
    vector<int> parent(nodeCount, -1);

    minCost[startId] = 0;
    pq.push({0, startId});

    while (!pq.empty()) {
        int currentCost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currentCost > minCost[u]) continue;
        if (u == endId) break;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            // 1 = Minimize Fare (Taka), 2 = Minimize Time (Minutes)
            int weight = (priority == 1) ? edge.fare : edge.time;

            if (minCost[u] + weight < minCost[v]) {
                minCost[v] = minCost[u] + weight;
                parent[v] = u;
                pq.push({minCost[v], v});
            }
        }
    }

    if (minCost[endId] == INT_MAX) {
        cout << "\nNo route found to Varendra University.\n";
        return;
    }

    // Reconstruct optimal path from parent pointers
    vector<int> path;
    int curr = endId;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());

    // Calculate total fare and time along the optimal path
    int totalFare = 0;
    int totalTime = 0;

    cout << "\n=======================================================\n";
    cout << "  Optimal Route to Varendra University (VU Campus)\n";
    cout << "  Criteria: " << ((priority == 1) ? "Cheapest Route (Lowest Fare)\n" : "Fastest Route (Minimum Time)\n");
    cout << "=======================================================\n";
    cout << "Route: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << idToName[path[i]];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\n\nStep-by-Step Travel Details:\n";

    for (size_t i = 0; i + 1 < path.size(); i++) {
        int u = path[i];
        int v = path[i + 1];
        int segFare = 0, segTime = 0;

        for (const auto& edge : adj[u]) {
            if (edge.to == v) {
                segFare = edge.fare;
                segTime = edge.time;
                break;
            }
        }
        totalFare += segFare;
        totalTime += segTime;

        cout << "  " << (i + 1) << ". " << idToName[u] << " -> " << idToName[v]
             << " (" << segFare << " Tk, " << segTime << " mins)\n";
    }

    cout << "-------------------------------------------------------\n";
    cout << "Total Auto / Easybike Fare : " << totalFare << " Taka\n";
    cout << "Total Estimated Time       : " << totalTime << " Minutes\n";
    cout << "=======================================================\n";
}

int main() {
    // -----------------------------------------------------------------
    // REALISTIC ROAD NETWORK IN RAJSHAHI CONNECTING TO VARENDRA UNIVERSITY
    // Format: addRoute(From, To, Fare_in_Taka, Time_in_Minutes)
    // -----------------------------------------------------------------

    // [1] Academic & University Corridor (VU, RUET, RU, Katakhali)
    // Notice: Local shared tempo gives CHEAPEST route, while direct bypass gives FASTEST route!
    addRoute("Talaimari", "Kazla", 5, 4);
    addRoute("Kazla", "Binodpur", 5, 4);
    addRoute("Binodpur", "Choddopai", 5, 4);
    addRoute("Choddopai", "Varendra University (VU)", 5, 8);         // Local shared tempo (5 Tk, 8 mins)
    addRoute("Talaimari", "Varendra University (VU)", 30, 12);        // Direct express bypass auto (30 Tk, 12 mins)
    addRoute("Binodpur", "Katakhali", 10, 8);
    addRoute("Katakhali", "Varendra University (VU)", 30, 11);        // Direct bypass from Katakhali (30 Tk, 11 mins)

    // [2] City Center & Commercial Corridors
    addRoute("Zero Point", "Alupatti", 5, 4);
    addRoute("Alupatti", "Talaimari", 10, 7);
    addRoute("Zero Point", "New Market", 5, 4);
    addRoute("New Market", "Bornali Mor", 5, 4);
    addRoute("New Market", "Railgate", 5, 5);
    addRoute("Zero Point", "Padma Garden", 5, 4);
    addRoute("Bhadra", "Zero Point", 10, 8);

    // [3] Railgate, Bhadra & Central Hubs
    addRoute("Railgate", "Bhadra", 5, 5);
    addRoute("Talaimari", "Bhadra", 5, 5);
    addRoute("Railgate", "Bornali Mor", 10, 5);
    addRoute("Railgate", "Shalbagan", 10, 7);
    addRoute("Bhadra", "Shalbagan", 10, 7);
    addRoute("Bhadra", "Naodapara", 10, 12);
    addRoute("Railgate", "Amchattar", 15, 8);                         // Fast bypass road

    // [4] Medical, West Zone & Court Corridors
    addRoute("Bornali Mor", "Laxmipur", 5, 4);
    addRoute("Laxmipur", "Zero Point", 10, 7);
    addRoute("Laxmipur", "C&B Mor", 5, 4);
    addRoute("C&B Mor", "Court", 10, 6);
    addRoute("Laxmipur", "Court", 10, 7);
    addRoute("C&B Mor", "Padma Garden", 10, 5);
    addRoute("Court", "Kashiadanga", 15, 12);

    // [5] Northern Hubs, Stadium & Bypass Highway
    addRoute("Shalbagan", "Naodapara", 5, 6);
    addRoute("Shalbagan", "Amchattar", 10, 6);
    addRoute("Bornali Mor", "Terokhadia", 5, 5);
    addRoute("Terokhadia", "Shalbagan", 5, 5);
    addRoute("Naodapara", "Amchattar", 5, 5);
    addRoute("Amchattar", "Biman Chattar", 5, 4);
    addRoute("Biman Chattar", "Naodapara", 5, 5);
    addRoute("Amchattar", "Varendra University (VU)", 15, 8);         // 4-lane north bypass (15 Tk, 8 mins)
    addRoute("Naodapara", "Varendra University (VU)", 10, 11);        // Regular bypass link (10 Tk, 11 mins)

    // -----------------------------------------------------------------
    // USER INTERFACE
    // -----------------------------------------------------------------
    cout << "=================================================================\n";
    cout << "       VARENDRA UNIVERSITY OPTIMAL ROUTE FINDER (CSE 2204)       \n";
    cout << "=================================================================\n";
    cout << "Available Locations in Rajshahi:\n";
    cout << " - Katakhali      - Binodpur       - Kazla          - Talaimari\n";
    cout << " - Bhadra         - Railgate       - Zero Point     - Alupatti\n";
    cout << " - New Market     - Bornali Mor    - Laxmipur       - C&B Mor\n";
    cout << " - Court          - Kashiadanga    - Shalbagan      - Terokhadia\n";
    cout << " - Naodapara      - Amchattar      - Biman Chattar  - Choddopai\n";
    cout << "-----------------------------------------------------------------\n";
    cout << "Target Destination: Varendra University (Permanent Campus)\n";
    cout << "-----------------------------------------------------------------\n";

    string startLocation;
    int priority;

    cout << "\nEnter your starting location: ";
    getline(cin, startLocation);

    cout << "\nChoose Your Option:\n";
    cout << "  1. Cheapest Route (Vara kom lagbe / Minimum Fare)\n";
    cout << "  2. Fastest Route  (Taratari jawa jabe / Minimum Time)\n";
    cout << "Enter choice (1 or 2): ";
    cin >> priority;

    findRouteToVU(startLocation, priority);

    return 0;
}
