#include iostream
#include fstream
#include string
using namespace std;

 ================================================================
         SMART CAMPUS NAVIGATION SYSTEM
         CSC-162 DSA Project  UET Lahore (KSK Campus)
 ================================================================




 ================================================================
  EDGE NODE CLASS
  Purpose  Represents a single road between two locations
  Each edge stores the destination index and road distance
 ================================================================

class EdgeNode {
public
    int destination;
    int distance;
    EdgeNode next;

    EdgeNode(int dest, int dist) {
        destination = dest;
        distance = dist;
        next = nullptr;
    }
};




 ================================================================
  LOCATION NODE CLASS
  Purpose  Stores a campus location and its adjacency list
 ================================================================

class LocationNode {
public
    string name;
    EdgeNode head;

    LocationNode() {
        head = nullptr;
    }
};




 ================================================================
  STACK CLASS
  Purpose  Tracks search history using LIFO order
  Operations push O(1), pop O(1), display O(n)
 ================================================================

class Stack {
private
    string data[50];
    int top;

public
    Stack() { top = -1; }

    void push(string value) {
        if (top  49) data[++top] = value;
    }

    void pop() {
        if (top = 0) {
            cout    [UNDONE]   data[top]  endl;
            top--;
        }
        else {
            cout    No history to undo.  endl;
        }
    }

    void display() {
        if (top == -1) {
            cout    No search history yet.  endl;
            return;
        }
        cout    Search History (latest first)  endl;
        for (int i = top; i = 0; i--)
            cout        (top - i + 1)  .   data[i]  endl;
    }

     Save history to file
    void saveToFile(ofstream& file) {
        file  n=== SEARCH HISTORY ===n;
        if (top == -1) { file    (empty)n; return; }
        for (int i = top; i = 0; i--)
            file      (top - i + 1)  .   data[i]  n;
    }
};




 ================================================================
  QUEUE CLASS
  Purpose  Handles user requests in FIFO order
  Operations enqueue O(1), dequeue O(1), display O(n)
 ================================================================

class Queue {
private
    string data[50];
    int front, rear;

public
    Queue() { front = rear = 0; }

    void enqueue(string value) {
        if (rear  50) data[rear++] = value;
        else cout    Request queue is full.  endl;
    }

    void dequeue() {
        if (front  rear) {
            cout    [PROCESSING]   data[front]  endl;
            front++;
            cout    Request processed successfully.  endl;
        }
        else {
            cout    No pending requests to process.  endl;
        }
    }

    void display() {
        if (front == rear) {
            cout    No pending requests.  endl;
            return;
        }
        cout    Pending Requests  endl;
        for (int i = front; i  rear; i++)
            cout        (i - front + 1)  .   data[i]  endl;
    }

    void saveToFile(ofstream& file) {
        file  n=== PENDING REQUESTS ===n;
        if (front == rear) { file    (empty)n; return; }
        for (int i = front; i  rear; i++)
            file      (i - front + 1)  .   data[i]  n;
    }
};




 ================================================================
  BST NODE
  Purpose  Single node for Binary Search Tree
 ================================================================

class BSTNode {
public
    string name;
    BSTNode left;
    BSTNode right;

    BSTNode(string value) {
        name = value;
        left = right = nullptr;
    }
};




 ================================================================
  BST CLASS
  Purpose  Stores locations sorted alphabetically
  Search   O(log n) average, O(n) worst case
  Insert   O(log n) average
 ================================================================

class BST {
private
    BSTNode root;

    BSTNode insertNode(BSTNode node, string value) {
        if (!node) return new BSTNode(value);
        if (value  node-name)      node-left = insertNode(node-left, value);
        else if (value  node-name) node-right = insertNode(node-right, value);
        else cout    Location already exists in BST.  endl;
        return node;
    }

    bool searchNode(BSTNode node, string value) {
        if (!node)              return false;
        if (node-name == value) return true;
        if (value  node-name) return searchNode(node-left, value);
        return searchNode(node-right, value);
    }

    void inorder(BSTNode node) {
        if (!node) return;
        inorder(node-left);
        cout      -   node-name  endl;
        inorder(node-right);
    }

    void inorderToFile(BSTNode node, ofstream& file) {
        if (!node) return;
        inorderToFile(node-left, file);
        file    -   node-name  n;
        inorderToFile(node-right, file);
    }

     Collect all names into array for sorting
    void collectNames(BSTNode node, string arr[], int& count) {
        if (!node) return;
        collectNames(node-left, arr, count);
        arr[count++] = node-name;
        collectNames(node-right, arr, count);
    }

public
    BST() { root = nullptr; }

    void insert(string value) {
        root = insertNode(root, value);
        cout      value   added to location list.  endl;
    }

    void search(string value) {
        if (searchNode(root, value))
            cout    [FOUND]   value   exists in the campus.  endl;
        else
            cout    [NOT FOUND]   value   is not in the campus.  endl;
    }

    void display() {
        cout    All Locations (A to Z)  endl;
        inorder(root);
    }

    void saveToFile(ofstream& file) {
        file  n=== CAMPUS LOCATIONS (A-Z) ===n;
        inorderToFile(root, file);
    }

     Sort by name using bubble sort and display
    void sortByName() {
        string arr[50];
        int count = 0;
        collectNames(root, arr, count);
         Bubble sort
        for (int i = 0; i  count - 1; i++)
            for (int j = 0; j  count - i - 1; j++)
                if (arr[j]  arr[j + 1]) swap(arr[j], arr[j + 1]);
        cout    Locations sorted by name  endl;
        for (int i = 0; i  count; i++)
            cout        (i + 1)  .   arr[i]  endl;
    }
};




 ================================================================
  HASH TABLE CLASS
  Purpose  Fast O(1) average lookup of campus locations
  Method   Division hashing with chaining (linked list)
 ================================================================

struct HashEntry {
    string key;
    HashEntry next;
    HashEntry(string k)  key(k), next(nullptr) {}
};

class HashTable {
private
    static const int SIZE = 53;   Prime number for better distribution
    HashEntry table[SIZE];

    int hashFunction(string key) {
        int hash = 0;
        for (char c  key) hash = (hash  31 + c) % SIZE;
        return hash;
    }

public
    HashTable() {
        for (int i = 0; i  SIZE; i++) table[i] = nullptr;
    }

    void insert(string key) {
        int idx = hashFunction(key);
         Check duplicate
        HashEntry cur = table[idx];
        while (cur) {
            if (cur-key == key) return;   already exists
            cur = cur-next;
        }
        HashEntry entry = new HashEntry(key);
        entry-next = table[idx];
        table[idx] = entry;
    }

    bool search(string key) {
        int idx = hashFunction(key);
        HashEntry cur = table[idx];
        while (cur) {
            if (cur-key == key) return true;
            cur = cur-next;
        }
        return false;
    }

    void remove(string key) {
        int idx = hashFunction(key);
        HashEntry cur = table[idx];
        HashEntry prev = nullptr;
        while (cur) {
            if (cur-key == key) {
                if (prev) prev-next = cur-next;
                else table[idx] = cur-next;
                delete cur;
                cout      key   removed from hash table.  endl;
                return;
            }
            prev = cur;
            cur = cur-next;
        }
        cout      key   not found in hash table.  endl;
    }
};




 ================================================================
  GRAPH CLASS
  Purpose  Represents the campus map using adjacency list
  Supports Dijkstra shortest path, BFS (Level-Order Exploration),
            DFS (Deep-Path Exploration)
 ================================================================

class Graph {
private
    LocationNode location[50];
    int locationCount;

public
    Graph() { locationCount = 0; }

    int getLocationIndex(string name) {
        for (int i = 0; i  locationCount; i++)
            if (location[i].name == name) return i;
        return -1;
    }

    void addLocation(string name) {
        if (locationCount = 50) {
            cout    Location limit reached (max 50).  endl;
            return;
        }
        if (getLocationIndex(name) != -1) {
            cout    Location already exists.  endl;
            return;
        }
        location[locationCount++].name = name;
        cout      name   added to campus map.  endl;
    }

    void addRoad(string source, string destination, int distance) {
        int src = getLocationIndex(source);
        int dest = getLocationIndex(destination);
        if (src == -1  dest == -1) {
            cout    Invalid location. Add locations first.  endl;
            return;
        }
        EdgeNode n1 = new EdgeNode(dest, distance);
        n1-next = location[src].head;
        location[src].head = n1;

        EdgeNode n2 = new EdgeNode(src, distance);
        n2-next = location[dest].head;
        location[dest].head = n2;

        cout    Road added   source   - 
             destination   (  distance  m)  endl;
    }

    void displayMap() {
        if (locationCount == 0) {
            cout    No locations added yet.  endl;
            return;
        }
        cout  n  +----------- CAMPUS MAP -----------+  endl;
        for (int i = 0; i  locationCount; i++) {
            cout       location[i].name   -- ;
            EdgeNode temp = location[i].head;
            if (!temp) cout  (no roads);
            while (temp) {
                cout  location[temp-destination].name
                      [  temp-distance  m];
                if (temp-next) cout    ;
                temp = temp-next;
            }
            cout  endl;
        }
        cout    +-----------------------------------+  endl;
    }

    void saveMapToFile(ofstream& file) {
        file  n=== CAMPUS MAP ===n;
        for (int i = 0; i  locationCount; i++) {
            file  location[i].name   -- ;
            EdgeNode temp = location[i].head;
            if (!temp) file  (no roads);
            while (temp) {
                file  location[temp-destination].name
                      [  temp-distance  m];
                if (temp-next) file    ;
                temp = temp-next;
            }
            file  n;
        }
    }

     Dijkstra Shortest Path — O(V^2)
    void shortestPath(string start, string end, ofstream logFile = nullptr) {
        int src = getLocationIndex(start);
        int dest = getLocationIndex(end);
        if (src == -1  dest == -1) {
            cout    Invalid location name.  endl;
            return;
        }

        int  dist[50], previous[50];
        bool visited[50];
        for (int i = 0; i  locationCount; i++) {
            dist[i] = 999999999;
            visited[i] = false;
            previous[i] = -1;
        }
        dist[src] = 0;

        for (int i = 0; i  locationCount; i++) {
            int minDist = 999999999, curr = -1;
            for (int j = 0; j  locationCount; j++)
                if (!visited[j] && dist[j]  minDist) { minDist = dist[j]; curr = j; }

            if (curr == -1) break;
            visited[curr] = true;

            EdgeNode temp = location[curr].head;
            while (temp) {
                int nb = temp-destination;
                int nd = dist[curr] + temp-distance;
                if (nd  dist[nb]) { dist[nb] = nd; previous[nb] = curr; }
                temp = temp-next;
            }
        }

        if (dist[dest] == 999999999) {
            cout    No path found between   start   and   end  .  endl;
            return;
        }

         Build path
        int path[50], pathCount = 0, current = dest;
        while (current != -1) { path[pathCount++] = current; current = previous[current]; }

        cout  n  Shortest Distance   dist[dest]  m  endl;
        cout    Route ;
        for (int i = pathCount - 1; i = 0; i--) {
            cout  location[path[i]].name;
            if (i != 0) cout   -- ;
        }
        cout  endl;

         Optionally write to log file
        if (logFile && logFile-is_open()) {
            logFile  n=== SHORTEST PATH ===n;
            logFile  From   start    To   end  n;
            logFile  Distance   dist[dest]  mnRoute ;
            for (int i = pathCount - 1; i = 0; i--) {
                logFile  location[path[i]].name;
                if (i != 0) logFile   -- ;
            }
            logFile  n;
        }
    }

     BFS — Level-Order Campus Exploration
     Visits all locations level by level (nearest first)
    void levelOrderExploration(string start) {
        int src = getLocationIndex(start);
        if (src == -1) { cout    Invalid location.  endl; return; }

        bool visited[50] = { false };
        int  q[50], front = 0, rear = 0;
        q[rear++] = src;
        visited[src] = true;

        cout    Level-Order Exploration (BFS) from   start  n  ;
        while (front  rear) {
            int curr = q[front++];
            cout  location[curr].name   ;
            EdgeNode temp = location[curr].head;
            while (temp) {
                int nb = temp-destination;
                if (!visited[nb]) { visited[nb] = true; q[rear++] = nb; }
                temp = temp-next;
            }
        }
        cout  endl;
    }

     DFS — Deep-Path Campus Exploration
     Dives as deep as possible before backtracking
    void deepPathExploration(string start) {
        int src = getLocationIndex(start);
        if (src == -1) { cout    Invalid location.  endl; return; }

        bool visited[50] = { false };
        int  stk[50], top = -1;
        stk[++top] = src;

        cout    Deep-Path Exploration (DFS) from   start  n  ;
        while (top = 0) {
            int curr = stk[top--];
            if (!visited[curr]) {
                visited[curr] = true;
                cout  location[curr].name   ;
                EdgeNode temp = location[curr].head;
                while (temp) {
                    if (!visited[temp-destination]) stk[++top] = temp-destination;
                    temp = temp-next;
                }
            }
        }
        cout  endl;
    }

     Sort locations by name using selection sort
    void sortLocations() {
        string names[50];
        int count = locationCount;
        for (int i = 0; i  count; i++) names[i] = location[i].name;

        for (int i = 0; i  count - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j  count; j++)
                if (names[j]  names[minIdx]) minIdx = j;
            swap(names[i], names[minIdx]);
        }

        cout    Locations sorted by name  endl;
        for (int i = 0; i  count; i++)
            cout        (i + 1)  .   names[i]  endl;
    }

    int getCount() { return locationCount; }
};




 ================================================================
  FILE HANDLING — Save entire session to a text file
 ================================================================

void saveSession(Graph& campus, Stack& history, Queue& requests, BST& locationList) {
    ofstream file(campus_session.txt);
    if (!file.is_open()) {
        cout    ERROR Could not create session file.  endl;
        return;
    }
    file  ================================================n;
    file     SMART CAMPUS NAVIGATION SYSTEM - SESSION LOGn;
    file     UET Lahore (KSK Campus)  CSC-162 DSAn;
    file  ================================================n;

    campus.saveMapToFile(file);
    locationList.saveToFile(file);
    history.saveToFile(file);
    requests.saveToFile(file);

    file  n================================================n;
    file               END OF SESSION LOGn;
    file  ================================================n;
    file.close();
    cout    Session saved to campus_session.txt  endl;
}




 ================================================================
  DISPLAY HELPERS — Attractive menu design
 ================================================================

void printHeader() {
    cout  n;
    cout    ===========================================  endl;
    cout       SMART CAMPUS NAVIGATION SYSTEM           endl;
    cout       UET Lahore (KSK Campus)  CSC-162        endl;
    cout    ===========================================  endl;
}

void printSectionLine() {
    cout    +-------------------------------------------+  endl;
}

void printMenu() {
    printHeader();
    cout              -- NAVIGATION MODULE --            endl;
    printSectionLine();
    cout      1.  Add Location                           endl;
    cout      2.  Add Road (Connection)                  endl;
    cout      3.  Display Campus Map                     endl;
    cout      4.  Find Shortest Path (Dijkstra)          endl;
    cout      5.  Level-Order Exploration (BFS)          endl;
    cout      6.  Deep-Path Exploration  (DFS)           endl;
    printSectionLine();
    cout              -- LOCATION MODULE --              endl;
    printSectionLine();
    cout      7.  Search Location (BST)                  endl;
    cout      8.  Display All Locations (A-Z)            endl;
    cout      9.  Sort Locations by Name                 endl;
    cout     10.  Fast Lookup (Hash Table)               endl;
    printSectionLine();
    cout            -- REQUEST & HISTORY --              endl;
    printSectionLine();
    cout     11.  Add Navigation Request                 endl;
    cout     12.  Process Next Request                   endl;
    cout     13.  Display All Requests                   endl;
    cout     14.  View Search History                    endl;
    cout     15.  Undo Last Search                       endl;
    printSectionLine();
    cout               -- FILE HANDLING --               endl;
    printSectionLine();
    cout     16.  Save Session to File                   endl;
    cout     17.  Load & Display Saved Session           endl;
    printSectionLine();
    cout      0.  Exit                                   endl;
    cout    ===========================================  endl;
    cout    Enter choice ;
}




 ================================================================
  MAIN FUNCTION — Menu-driven interface
 ================================================================

int main() {

    Graph     campus;
    Stack     history;
    Queue     requests;
    BST       locationList;
    HashTable hashTable;

    int choice;

    do {
        printMenu();
        cin  choice;
        cout  endl;

        if (choice == 1) {
            string name;
            cout    Enter location name ;
            cin  name;
            campus.addLocation(name);
            locationList.insert(name);
            hashTable.insert(name);
        }

        else if (choice == 2) {
            string source, destination;
            int distance;
            cout    Enter source location ;      cin  source;
            cout    Enter destination location ; cin  destination;
            cout    Enter distance (meters) ;    cin  distance;
            campus.addRoad(source, destination, distance);
        }

        else if (choice == 3) {
            campus.displayMap();
        }

        else if (choice == 4) {
            string start, end;
            cout    Enter start location ; cin  start;
            cout    Enter end location ;   cin  end;
            campus.shortestPath(start, end);
            history.push(start +  --  + end);
        }

        else if (choice == 5) {
            string start;
            cout    Enter starting location for Level-Order Exploration (BFS) ;
            cin  start;
            campus.levelOrderExploration(start);
        }

        else if (choice == 6) {
            string start;
            cout    Enter starting location for Deep-Path Exploration (DFS) ;
            cin  start;
            campus.deepPathExploration(start);
        }

        else if (choice == 7) {
            string name;
            cout    Enter location to search ;
            cin  name;
            locationList.search(name);
        }

        else if (choice == 8) {
            locationList.display();
        }

        else if (choice == 9) {
            campus.sortLocations();
        }

        else if (choice == 10) {
            string name;
            cout    Enter location for fast hash lookup ;
            cin  name;
            if (hashTable.search(name))
                cout    [FOUND]   name   exists (Hash Table lookup).  endl;
            else
                cout    [NOT FOUND]   name   is not in the system.  endl;
        }

        else if (choice == 11) {
            string request;
            cout    Enter your navigation request ;
            cin.ignore();
            getline(cin, request);
            requests.enqueue(request);
            cout    Request added to queue.  endl;
        }

        else if (choice == 12) {
            requests.dequeue();
        }

        else if (choice == 13) {
            requests.display();
        }

        else if (choice == 14) {
            history.display();
        }

        else if (choice == 15) {
            history.pop();
        }

        else if (choice == 16) {
            saveSession(campus, history, requests, locationList);
        }

        else if (choice == 17) {
            ifstream file(campus_session.txt);
            if (!file.is_open()) {
                cout    No saved session found. Save a session first (Option 16).  endl;
            }
            else {
                string line;
                cout  n  ---- Saved Session Content ----n;
                while (getline(file, line)) cout      line  n;
                file.close();
            }
        }

        else if (choice == 0) {
            cout    Thank you for using Smart Campus Navigation System!  endl;
            cout    Goodbye! -- UET Lahore, KSK Campus  endl;
        }

        else {
            cout    Invalid choice. Please enter a number from the menu.  endl;
        }

        if (choice != 0) {
            cout  n  Press Enter to continue...;
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}