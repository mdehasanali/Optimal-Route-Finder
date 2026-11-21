# VARENDRA UNIVERSITY
### Department of Computer Science and Engineering
**4th Semester (Summer-2026)**  
**Course Code:** CSE 2204  
**Course Title:** Computer Algorithms Lab  

---

# LAB PROJECT REPORT

### **Project Title:**  
## Optimal Route Finder to Varendra University Campus Using Dijkstra’s Algorithm  
*(A Comprehensive Study Across 24 Rajshahi City Transit Locations: Lowest Fare vs. Fastest Time)*

---

### **Submitted By (Group Members):**

| Name | Student ID | Section | Role / Contribution |
| :--- | :---: | :---: | :--- |
| **[Student Name 1]** | [e.g., 221311117] | C | Project Lead & Algorithm Design |
| **[Student Name 2]** | [e.g., 221311118] | C | Graph Modeling & C++ Implementation |
| **[Student Name 3]** | [e.g., 221311119] | C | Testing, Verification & Report Writing |

**Semester:** 4th Semester  
**Session:** Summer-2026  
**Submission Date:** [Insert Date]  

---

## 1. Problem Statement

### 1.1 Context & Background
Varendra University (VU) has shifted its primary academic activities to its permanent campus located at **Kharkhari, Rajshahi**, situated alongside the northern-eastern bypass corridor. As a consequence, thousands of students, faculty members, and administrative staff commute daily from various residential, commercial, and transit zones across Rajshahi City—such as **Zero Point, Alupatti, Laxmipur, Railgate, Bhadra, Padma Residential, Talaimari, Kazla, Binodpur, Choddopai, Shalbagan, and Naodapara**.

Unlike cities with centralized rapid transit or unified metro rail services, daily commuters in Rajshahi rely predominantly on **battery-run auto-rickshaws (Easybikes) and local tempos**. Commuting through these transit networks presents daily challenges:
1. Multiple alternative paths exist to reach the university campus.
2. Route variations exhibit significant trade-offs between **monetary fare (in BDT)** and **travel time (in minutes)**.

### 1.2 The Problem to Solve
When commuting to Varendra University, a student’s priority changes depending on the situation:
- **Scenario A (In a Hurry / Exam Time):** When rushing for an exam or morning lecture, the priority is **"Taratari jawa jabe" (Fastest Route)**, where travel time must be minimized, even if it incurs a slightly higher fare via express bypass roads (e.g., direct Talaimari-Kharkhari bypass or Amchattar North Bypass).
- **Scenario B (Budget Conscious / Daily Commute):** On everyday commutes, students with limited monthly allowances prefer **"Vara kom lagbe" (Cheapest Route)**, choosing shared local tempos and student hops (e.g., via Kazla, Binodpur, Choddopai, and Kharkhari Bazar), saving valuable pocket money.

### 1.3 Project Objective
To solve this practical commuting dilemma by designing and implementing an efficient, automated **Route Finder** using **Dijkstra's Shortest Path Algorithm**. The program models Rajshahi’s road network as a dual-weighted graph of 24 detailed locations, allowing any user to input their starting location in Rajshahi, select their optimization criterion (Cheapest Fare vs. Fastest Time), and receive the mathematically guaranteed optimal step-by-step route to Varendra University.

---

## 2. Algorithm of the Solution

### 2.1 Graph Formulation
The road network is represented as an undirected weighted graph $G = (V, E)$:
- **Vertices ($V$):** 24 transit hubs and crossroads in Rajshahi.
- **Edges ($E$):** 41 bidirectional road segments directly connecting two locations.
- **Dual Weights:** Each edge $e = (u, v)$ carries two distinct non-negative values:
  1. $W_{fare}(u, v) \in \mathbb{Z}^+$ (Auto-rickshaw fare in Taka)
  2. $W_{time}(u, v) \in \mathbb{Z}^+$ (Average transit time in minutes from Google Maps)

### 2.2 Step-by-Step Algorithm (Dijkstra with Priority Selector)

```text
Step 1: [Initialize Graph]
        Map all 24 location names to unique integer IDs (0 to N-1).
        Build adjacency list adj[u] storing destination node v, fare, and time.

Step 2: [Input Selection]
        Read starting location (startNode) and user optimization priority:
        - Priority 1: Minimize Total Fare
        - Priority 2: Minimize Total Travel Time
        Fixed Destination: "Varendra University" (endNode).

Step 3: [Initialize Data Structures]
        Create an array minCost[0 ... N-1] initialized to INFINITY.
        Create a parent array parent[0 ... N-1] initialized to -1.
        Create a Min-Priority Queue PQ storing pairs (currentCost, u).

Step 4: [Source Initialization]
        Set minCost[startNode] = 0.
        Push (0, startNode) into PQ.

Step 5: [Shortest Path Exploration Loop]
        While PQ is not empty:
            a. Extract (currentCost, u) with minimum cost from PQ.
            b. If currentCost > minCost[u], continue (stale entry).
            c. If u == endNode, break (target reached).
            d. For each adjacent edge (u -> v):
                   Determine weight w based on chosen priority:
                       If priority == 1: w = edge.fare
                       If priority == 2: w = edge.time
                   If minCost[u] + w < minCost[v]:
                       minCost[v] = minCost[u] + w
                       parent[v] = u
                       Push (minCost[v], v) into PQ.

Step 6: [Path Reconstruction]
        Start at endNode and backtrack using parent[curr] until reaching startNode.
        Reverse the collected nodes to produce the source-to-destination path.

Step 7: [Calculate Total Fare & Time]
        Traverse the reconstructed path and sum the individual fares and transit times.
        Print the optimal path and step-by-step breakdown.
```

---

## 3. Road Network Reference Table (Google Maps & RCC Fare)

| Sl. | Route Segment (Bidirectional) | Standard Fare (BDT) | Travel Time (Google Maps) | Corridor Zone |
| :---: | :--- | :---: | :---: | :--- |
| 1 | **Kharkhari Bazar ⇄ Varendra University** | 5 Tk | 3 min | VU Campus Link |
| 2 | **Choddopai ⇄ Kharkhari Bazar** | 5 Tk | 5 min | East Bypass Approach |
| 3 | **Binodpur ⇄ Choddopai** | 5 Tk | 3 min | RU East Boundary |
| 4 | **Kazla ⇄ Binodpur** | 5 Tk | 3 min | Student Mess Corridor |
| 5 | **Talaimari ⇄ Kazla** | 5 Tk | 4 min | RUET Connector |
| 6 | **Talaimari ⇄ Varendra University** (Direct Bypass) | 30 Tk | 12 min | Express Bypass Highway |
| 7 | **Talaimari ⇄ Choddopai** | 10 Tk | 7 min | RU South-East Link |
| 8 | **Binodpur ⇄ Katakhali** | 15 Tk | 10 min | Highway Eastern Link |
| 9 | **Katakhali ⇄ Kharkhari Bazar** | 15 Tk | 10 min | Kapasia Eastern Bypass |
| 10 | **Zero Point ⇄ Alupatti** | 5 Tk | 4 min | Shaheb Bazar Core |
| 11 | **Alupatti ⇄ Talaimari** | 10 Tk | 8 min | Main City Highway |
| 12 | **Zero Point ⇄ New Market** | 5 Tk | 4 min | Rani Bazar Link |
| 13 | **New Market ⇄ Bornali Mor** | 5 Tk | 4 min | Greater Road Crossing |
| 14 | **New Market ⇄ Railgate** | 10 Tk | 5 min | Station Approach |
| 15 | **Bhadra ⇄ Zero Point** | 10 Tk | 7 min | Sagarpara Connector |
| 16 | **Railgate ⇄ Bhadra** | 10 Tk | 5 min | Central Transit Hub |
| 17 | **Bhadra ⇄ Talaimari** | 10 Tk | 5 min | Inner Link |
| 18 | **Bhadra ⇄ Padma Residential** | 5 Tk | 4 min | Residential Hub |
| 19 | **Padma Residential ⇄ Talaimari** | 5 Tk | 4 min | South Link |
| 20 | **Railgate ⇄ Bornali Mor** | 10 Tk | 5 min | Greater Road |
| 21 | **Bornali Mor ⇄ Laxmipur** | 5 Tk | 4 min | Medical Connector |
| 22 | **Laxmipur ⇄ Zero Point** | 10 Tk | 7 min | Ghoramara Link |
| 23 | **Laxmipur ⇄ C&B Mor** | 5 Tk | 4 min | River Road Connector |
| 24 | **C&B Mor ⇄ Court Station** | 10 Tk | 6 min | Court Approach |
| 25 | **Laxmipur ⇄ Court Station** (Direct) | 10 Tk | 7 min | Main Road |
| 26 | **Court Station ⇄ Kashiadanga** | 15 Tk | 12 min | Western Highway |
| 27 | **Railgate ⇄ Shalbagan** | 10 Tk | 7 min | Sopura BSCIC Road |
| 28 | **Bhadra ⇄ Shalbagan** | 10 Tk | 7 min | Shiroil Bypass Link |
| 29 | **Bhadra ⇄ Naodapara** | 15 Tk | 11 min | Northern Terminal Link |
| 30 | **Railgate ⇄ Amchattar** | 15 Tk | 9 min | Airport Highway |
| 31 | **Shalbagan ⇄ Naodapara** | 10 Tk | 6 min | Northern Road |
| 32 | **Shalbagan ⇄ Amchattar** | 10 Tk | 6 min | North Bypass Link |
| 33 | **Bornali Mor ⇄ Terokhadia** | 10 Tk | 5 min | Stadium Road |
| 34 | **Terokhadia ⇄ Shalbagan** | 10 Tk | 6 min | Stadium Bypass |
| 35 | **Naodapara ⇄ Amchattar** | 10 Tk | 5 min | Terminal-Roundabout |
| 36 | **Amchattar ⇄ Biman Chattar** | 10 Tk | 5 min | Airport Road |
| 37 | **Biman Chattar ⇄ Naodapara** | 10 Tk | 6 min | Bypass Approach |
| 38 | **Amchattar ⇄ Varendra University** (North Bypass) | 15 Tk | 8 min | 4-Lane North Bypass |
| 39 | **Naodapara ⇄ Kharkhari Bazar** | 10 Tk | 8 min | Bypass Link |
| 40 | **Zero Point ⇄ Padma Garden** | 5 Tk | 4 min | Riverfront Embankment |
| 41 | **C&B Mor ⇄ Padma Garden** | 10 Tk | 5 min | Boro Kuthi Riverside |

---

## 4. Program Output & Verification

### Test Case: Commuting from **Zero Point (Shaheb Bazar)** to **Varendra University**

#### Option 1: Cheapest Route (Budget Mode)
```text
=======================================================
  Optimal Route to Varendra University (VU Campus)
  Criteria: Cheapest Route (Lowest Fare)
=======================================================
Route: Zero Point -> Alupatti -> Talaimari -> Choddopai -> Kharkhari Bazar -> Varendra University

Step-by-Step Travel Details:
  1. Zero Point -> Alupatti (5 Tk, 4 mins)
  2. Alupatti -> Talaimari (10 Tk, 8 mins)
  3. Talaimari -> Choddopai (10 Tk, 7 mins)
  4. Choddopai -> Kharkhari Bazar (5 Tk, 5 mins)
  5. Kharkhari Bazar -> Varendra University (5 Tk, 3 mins)
-------------------------------------------------------
Total Auto / Easybike Fare : 35 Taka
Total Estimated Time       : 27 Minutes
=======================================================
```

#### Option 2: Fastest Route (Rush/Exam Mode)
```text
=======================================================
  Optimal Route to Varendra University (VU Campus)
  Criteria: Fastest Route (Minimum Time)
=======================================================
Route: Zero Point -> Alupatti -> Talaimari -> Varendra University

Step-by-Step Travel Details:
  1. Zero Point -> Alupatti (5 Tk, 4 mins)
  2. Alupatti -> Talaimari (10 Tk, 8 mins)
  3. Talaimari -> Varendra University (30 Tk, 12 mins)
-------------------------------------------------------
Total Auto / Easybike Fare : 45 Taka
Total Estimated Time       : 24 Minutes
=======================================================
```

> **Evaluation:** The algorithm demonstrates genuine multi-criteria intelligence. The student rushing for an exam saves 3 minutes via the direct bypass auto, while the student on a budget saves **10 Taka** by taking the local shared tempo link!

---

## 5. Discussion

### 5.1 Time and Space Complexity
- **Time Complexity:** $\mathcal{O}((V + E) \log V)$ where $|V| = 24$ and $|E| = 41$. Because $(24 + 41) \log_2(24) \approx 300$ operations, the execution time is below **1 millisecond**.
- **Space Complexity:** $\mathcal{O}(V + E)$ utilizing standard adjacency list and linear priority queue space.

### 5.2 Technical Challenges
- Handling dual weights without distorting shortest path guarantees was accomplished by keeping fare and time decoupled during relaxation.
- Incorporating 24 specific locations while keeping the C++ source code under 170 lines was achieved through modular mapping functions and standard STL templates.

---

## 6. Team Management

| Member Name | Student ID | Assigned Tasks & Responsibilities | Contribution |
| :--- | :---: | :--- | :---: |
| **[Student 1 Name]** | 221311117 | Problem formulation, surveying 24 Rajshahi locations, algorithm flowchart. | 35% |
| **[Student 2 Name]** | 221311118 | Data structure design, Dijkstra dual-priority engine, path backtracking. | 35% |
| **[Student 3 Name]** | 221311119 | Calibrating Google Maps times & RCC fares, test execution, report formatting. | 30% |
