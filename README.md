# Varendra University Optimal Route Finder (CSE 2204)

An optimal transit route finder to **Varendra University (Permanent Campus, Kharkhari)** from any location across Rajshahi City implemented in C++ using **Dijkstra's Shortest Path Algorithm**.

The program calculates the most optimal path based on two student commuting priorities:
1. **Cheapest Route ("Vara kom lagbe" / Minimum Fare in BDT)**
2. **Fastest Route ("Taratari jawa jabe" / Minimum Time in Minutes)**

---

## 🗺️ Coverage & Specified Location Network (24 Locations)

The network encompasses **24 detailed locations** and **41 bidirectional road corridors** covering all zones of Rajshahi city:

### 1. Varendra University & Academic Corridors
- **Varendra University** (Permanent Campus, Kharkhari) — Target Destination
- **Kharkhari Bazar** — Transit point just before the VU campus
- **Choddopai** — RU East perimeter / Bypass link (Student mess zone)
- **Binodpur** — RU 2nd Gate & student market
- **Kazla** — RUET main entrance & RU 1st gate
- **Talaimari** — Major southern roundabout connecting the university corridor
- **Katakhali** — Eastern highway junction (Dhaka / Natore approach)

### 2. City Center & Commercial Corridors
- **Zero Point (Shaheb Bazar)** — Commercial heart of Rajshahi
- **Alupatti** — Major connecting junction between Shaheb Bazar and Talaimari
- **New Market (Rani Bazar)** — Central shopping hub
- **Bornali Mor** — Primary crossroads linking Greater Road, New Market, and Medical

### 3. Medical, West Zone & Court Corridors
- **Laxmipur** — Rajshahi Medical College Hospital (RMCH) & health district
- **C&B Mor** — Riverfront and administrative junction
- **Court Station** — Judicial, administrative & railway station in the west
- **Kashiadanga** — Western entry/exit towards Chapainawabganj highway

### 4. Northern Hubs, Bypass Highway & Transport Hubs
- **Railgate (Shiroil Station)** — Central railway station & bus terminal area
- **Bhadra** — Major transit crossroads
- **Padma Residential** — Major residential neighborhood near Bhadra/Talaimari
- **Shalbagan (Sopura)** — Industrial (BSCIC) & transit junction
- **Terokhadia** — Shahid Kamruzzaman Stadium & residential area
- **Naodapara** — Inter-district Bus Terminal
- **Amchattar** — Northern bypass roundabout & airport approach
- **Biman Chattar** — Rajshahi Airport entrance roundabout

### 5. Scenic Riverside
- **Padma Garden** — Boro Kuthi riverbank recreation area

---

## 📊 Comprehensive Route, Fare & Travel Time Reference Table

All distances and travel times are based on **Google Maps** auto-rickshaw transit data and official **Rajshahi City Corporation (RCC)** shared Easybike fare standards:

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

## ⚡ How to Compile and Run

### In Code::Blocks or Dev-C++:
Open `main.cpp` and click **Build & Run** (F9 / F11).

### In Terminal / Command Prompt:
```bash
g++ -std=c++11 main.cpp -o route_finder
./route_finder
```
