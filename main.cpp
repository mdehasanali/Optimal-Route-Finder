#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int to; int fare; int time;
};

// গ্লোবাল ভেরিয়েবল
unordered_map<string, int> nameToId;
unordered_map<int, string> idToName;
vector<vector<Edge>> adj;
int nodeCount = 0;

// গন্তব্য সবসময় বরেন্দ্র বিশ্ববিদ্যালয়
const string DESTINATION = "Varendra University";

// ছোট হাতের অক্ষরে রূপান্তর (ইউজার যেভাবে খুশি টাইপ করতে পারবে)
string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

// নতুন লোকেশন গ্রাফে যুক্ত করা
void addLocation(string name) {
    if (nameToId.find(name) == nameToId.end()) {
        nameToId[name] = nodeCount;
        idToName[nodeCount] = name;
        adj.push_back(vector<Edge>());
        nodeCount++;
    }
}

// দুটি লোকেশনের মাঝে দ্বিমুখী রাস্তা (Route) যোগ করা
void addRoute(string u, string v, int fare, int time) {
    addLocation(u);
    addLocation(v);
    int idU = nameToId[u];
    int idV = nameToId[v];
    adj[idU].push_back({idV, fare, time});
    adj[idV].push_back({idU, fare, time});
}

// ইউজারের ইনপুট থেকে সঠিক লোকেশন আইডি বের করা
int findNodeId(string input) {
    string lower = toLower(input);
    if (lower == "vu" || lower == "varendra" || lower == "kharkhari") {
        return nameToId[DESTINATION];
    }
    if (lower == "ruet") return nameToId["Kazla"];
    if (lower == "ru" || lower == "varsity") return nameToId["Binodpur"];

    for (const auto& pair : nameToId) {
        if (toLower(pair.first) == lower) {
            return pair.second;
        }
    }
    return -1; // পাওয়া না গেলে
}

// ২. ডাইজকস্ট্রা অ্যালগরিদম (Dijkstra's Algorithm)
void findRouteToVU(string startInput, int choice) {
    int startId = findNodeId(startInput);
    int endId = nameToId[DESTINATION];

    if (startId == -1) {
        cout << "\n[!] Error: Location not found! Please check spelling from the list.\n";
        return;
    }

    if (startId == endId) {
        cout << "\nYou are already at Varendra University!\n";
        return;
    }

    // Min-Priority Queue: pair<খরচ, নোড আইডি>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> minCost(nodeCount, 1e9); // শুরুতে সব নোডের খরচ ইনফিনিটি (1e9)
    vector<int> parent(nodeCount, -1);   // পথ মনে রাখার জন্য প্যারেন্ট অ্যারে

    // সোর্স নোড ইনিশিয়ালাইজেশন
    minCost[startId] = 0;
    pq.push({0, startId});

    // ডাইজকস্ট্রার মূল লুপ
    while (!pq.empty()) {
        int currentCost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currentCost > minCost[u]) continue;
        if (u == endId) break; // গন্তব্যে পৌঁছালে লুপ শেষ

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            // choice = 1 হলে ভাড়া (fare), choice = 2 হলে সময় (time)
            int weight = (choice == 1) ? edge.fare : edge.time;

            // রিলাক্সেশন (Relaxation)
            if (minCost[u] + weight < minCost[v]) {
                minCost[v] = minCost[u] + weight;
                parent[v] = u;
                pq.push({minCost[v], v});
            }
        }
    }

    if (minCost[endId] == 1e9) {
        cout << "\nNo route found to Varendra University.\n";
        return;
    }

    // ব্যাকট্র্যাকিং করে সঠিক পথ (Path) বের করা
    vector<int> path;
    int curr = endId;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());

    // মোট ভাড়া ও মোট সময় গণনা
    int totalFare = 0;
    int totalTime = 0;

    cout << "\n=======================================================\n";
    cout << "  Optimal Route to Varendra University\n";
    cout << "  Criteria: " << ((choice == 1) ? "Cheapest Route (Lowest Fare)\n" : "Fastest Route (Minimum Time)\n");
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
        for (const auto& edge : adj[u]) {
            if (edge.to == v) {
                totalFare += edge.fare;
                totalTime += edge.time;
                cout << "  " << (i + 1) << ". " << idToName[u] << " -> " << idToName[v]
                     << " (" << edge.fare << " Tk, " << edge.time << " mins)\n";
                break;
            }
        }
    }

    cout << "-------------------------------------------------------\n";
    cout << "Total Auto Fare : " << totalFare << " Taka\n";
    cout << "Total Estimated Time       : " << totalTime << " Minutes\n";
    cout << "=======================================================\n";
}

int main() {
    addRoute("Katakhali", "Varendra University", 30, 18); 
    addRoute("Katakhali", "Binodpur", 10, 8);
    addRoute("Binodpur", "Kazla", 5, 4);
    addRoute("Kazla", "Talaimari", 5, 4);
    addRoute("Talaimari", "Varendra University", 20, 13); 
    addRoute("Talaimari", "Bhadra", 5, 5);
    addRoute("Bhadra", "Varendra University", 15, 15);    
    addRoute("Bhadra", "Railgate", 5, 5);
    addRoute("Bhadra", "Zero Point", 10, 10);
    addRoute("Zero Point", "Alupatti", 5, 4);
    addRoute("Alupatti", "Talaimari", 10, 7);
    addRoute("Zero Point", "New Market", 5, 4);
    addRoute("New Market", "Railgate", 5, 3);
    addRoute("New Market", "Bornali Mor", 5, 5);
    addRoute("Bornali Mor", "Laxmipur", 5, 4);
    addRoute("Laxmipur", "Zero Point", 10, 7);
    addRoute("Laxmipur", "Court", 10, 7);
    addRoute("Court", "Kashiadanga", 15, 12);
    addRoute("Railgate", "Amchattar", 10, 10);
    addRoute("Amchattar", "Naodapara", 5, 5);
    addRoute("Naodapara", "Varendra University", 10, 11);
    addRoute("Amchattar", "Varendra University", 15, 8);

    cout << "=======================================================\n";
    cout << "   VARENDRA UNIVERSITY OPTIMAL ROUTE FINDER (CSE 2204) \n";
    cout << "=======================================================\n";
    cout << "Available Locations:\n";
    cout << " - Katakhali    - Binodpur     - Kazla        - Talaimari\n";
    cout << " - Bhadra       - Railgate     - Zero Point   - Alupatti\n";
    cout << " - New Market   - Bornali Mor  - Laxmipur     - Court\n";
    cout << " - Kashiadanga  - Amchattar    - Naodapara\n";
    cout << "-------------------------------------------------------\n";
    cout << "Destination: Varendra University\n";
    cout << "=======================================================\n";

    string startLocation;
    int choice;

    cout << "\nEnter your starting location: ";
    getline(cin, startLocation);

    cout << "\nChoose Your Option:\n";
    cout << "  1. Cheapest Route (Minimum Fare)\n";
    cout << "  2. Fastest Route  (Minimum Time)\n";
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    findRouteToVU(startLocation, choice);

    return 0;
}
