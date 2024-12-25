#include <iostream>
#include <cmath>
#include <string>
#include <climits>
#include <vector>
using namespace std;
class graph1 {
private:
    float** adjmatrix;
    int numvertices;

public:
    string airports[10] = {"JFK", "LAX", "ORD", "ATL", "DFW", "DEN", "SEA", "MIA", "PHX", "BOS"};
    float latitude[10] = {40.6413, 33.9416, 41.9742, 33.6407, 32.8998, 39.8561, 47.6062, 25.7959, 33.4484, 42.3656};
    float longitude[10] = {-73.7781, -118.4085, -87.9073, -84.4277, -97.0403, -104.6737, -122.3321, -80.2871, -112.0740, -71.0096};

    graph1() {
        numvertices = 10;
        adjmatrix = new float*[numvertices];
        for (int i = 0; i < numvertices; i++) {
            adjmatrix[i] = new float[numvertices];
            for (int j = 0; j < numvertices; j++) {
                adjmatrix[i][j] = -1;
            }
        }
    }

    float distance(float lo1, float lo2, float la1, float la2) {
        const int r = 6371; // Radius of Earth in km
        float dis;
        dis = 2 * r * asin(sqrt(sin((la2 - la1) / 2) * sin((la2 - la1) / 2) +
                                cos(la1) * cos(la2) * sin((lo2 - lo1) / 2) * sin((lo2 - lo1) / 2)));
        return dis;
    }

    float radian(float a) {
        return a * M_PI / 180;
    }

    void addedge(int i, int j) {
        float la1 = radian(latitude[i]);
        float lo1 = radian(longitude[i]);
        float la2 = radian(latitude[j]);
        float lo2 = radian(longitude[j]);
        adjmatrix[i][j] = distance(lo1, lo2, la1, la2);
        adjmatrix[j][i] = adjmatrix[i][j];
    }

    void removeedge(int i, int j) {
        adjmatrix[i][j] = -1;
        adjmatrix[j][i] = -1;
    }

    void display() {
        cout << "Graph representation (distance in km)" << endl;
        for (int i = 0; i < numvertices; i++) {
            cout << airports[i] << " : ";
            for (int j = 0; j < numvertices; j++) {
                if (adjmatrix[i][j] != -1) {
                    cout << airports[j] << "(" << adjmatrix[i][j] << " km) ";
                }
            }
            cout << endl;
        }
    }

    int minkey(float key[], bool mstset[]) {
        float min = INT_MAX;
        int minindex;
        for (int v = 0; v < numvertices; v++) {
            if (!mstset[v] && key[v] < min) {
                min = key[v];
                minindex = v;
            }
        }
        return minindex;
    }

    void primMST() {
        float key[numvertices];
        bool mstset[numvertices];
        int parent[numvertices];

        for (int i = 0; i < numvertices; i++) {
            key[i] = INT_MAX;
            mstset[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < numvertices - 1; count++) {
            int u = minkey(key, mstset);
            mstset[u] = true;

            for (int v = 0; v < numvertices; v++) {
                if (adjmatrix[u][v] != -1 && !mstset[v] && adjmatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjmatrix[u][v];
                }
            }
        }

        cout << "Minimum Spanning Tree:" << endl;
        cout << "Edge\tWeight" << endl;
        for (int i = 1; i < numvertices; i++) {
            cout << airports[parent[i]] << " - " << airports[i] << " \t" << adjmatrix[i][parent[i]] << " km" << endl;
        }
    }
};
struct Passenger {
    string name;
    int id;
    string seatNumber;
    Passenger* next;

    Passenger(string n, int i, string s) {
    	name = n ;
    	id = i ;
    	seatNumber = s;
    	next = NULL;
	}
};
class PassengerQueue {
private:
    Passenger* front;
    Passenger* rear;

public:
    PassengerQueue() {
    	front = NULL;
    	rear = NULL;

	}


    void enqueue(string name, int id, string seatNumber) {

        Passenger* newPassenger = new Passenger(name, id, seatNumber);

        if (rear == NULL) {
            front = rear = newPassenger;
        } else {
            rear->next = newPassenger;
            rear = newPassenger;
        }

        cout << "Passenger " << name << " with ID " << id << " added to the queue.\n";
    }


    void dequeue() {
        if (front == NULL) {
            cout << "No passengers in the queue." << endl;
            return;
        }

        Passenger* temp = front;


        cout << "Passenger " << front->name << " with ID " << front->id << " boarded." << endl;
        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete temp;
    }


    void displayQueue() {
        if (front == NULL) {
            cout << "The queue is empty." << endl;

            return;
        }

        Passenger* current = front;
        cout << "Passengers in the queue:  " << endl;
        while (current != NULL) {
            cout << "Name: " << current->name
                 << ", ID: " << current->id
                 << ", Seat: " << current->seatNumber << "\n";
            current = current->next;
        }
    }


    ~PassengerQueue() {
        while (front != NULL) {
            Passenger* temp = front;
            front = front->next;
            delete temp;
        }
    }
};
class Flight {
public:
    string flightNumber;
    string source;
    string destination;
    string arrivalTime;
    string departureTime;
    string gate;

    // Constructor
    Flight(string fn, string src, string dest, string arr, string dep, string g)
        : flightNumber(fn), source(src), destination(dest), arrivalTime(arr), departureTime(dep), gate(g) {}

    // Display flight details (marked as const)
    void displayFlight() const {
        cout << "Flight Number: " << flightNumber
             << ", Source: " << source
             << ", Destination: " << destination
             << ", Arrival: " << arrivalTime
             << ", Departure: " << departureTime
             << ", Gate: " << gate << endl;
    }
};

// FlightScheduler class to manage flights
class FlightScheduler {
private:
    vector<Flight> flights;

public:
    // Add a flight to the schedule
    void addFlight(Flight flight) {
        flights.push_back(flight);
        cout << "Flight added successfully.\n";
    }

    // Remove a flight from the schedule
    void removeFlight(const string &flightNumber) {
        for (size_t i = 0; i < flights.size(); ++i) {
            if (flights[i].flightNumber == flightNumber) {
                flights.erase(flights.begin() + i);
                cout << "Flight removed successfully.\n";
                return;
            }
        }
        cout << "Flight not found.\n";
    }

    // Display all flights in the schedule
    void displaySchedule() const {
        if (flights.empty()) {
            cout << "No flights scheduled.\n";
            return;
        }
        cout << "\n--- Flight Schedule ---\n";
        for (size_t i = 0; i < flights.size(); ++i) {
            flights[i].displayFlight();
        }
    }

    // Search for a specific flight by flight number
    void searchFlight(const string &flightNumber) const {
        for (size_t i = 0; i < flights.size(); ++i) {
            if (flights[i].flightNumber == flightNumber) {
                cout << "Flight found:\n";
                flights[i].displayFlight();
                return;
            }
        }
        cout << "Flight not found.\n";
    }
};
int main()
{
	int a;
	cout<<"1. Passenger management system "<<endl;
	cout<<"2. Flight scheduling "<<endl;
	cout<<"3. Airport navigation "<<endl;
	cout<<"Please enter your choice :";cin>>a;
	if (a==1)
    {
	PassengerQueue queue;
    int choice;

    do {
        cout << "\n--- Airlines Passenger Management System ---\n";
        cout << "1.   Add Passenger\n";
        cout << "2.   Remove Passenger (Boarding)\n";
        cout << "3.   Display Passengers\n";
        cout << "4.   Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, seatNumber;
            int id;
            cout << "Enter passenger name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter passenger ID: ";
            cin >> id;
            cout << "Enter seat number: ";
            cin.ignore();
            getline(cin, seatNumber);
            queue.enqueue(name, id, seatNumber);
            break;
        }
        case 2:
            queue.dequeue();
            break;
        case 3:
            queue.displayQueue();
            break;
        case 4:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
	while (choice != 4);
    }
    if (a==2)
    {
    	FlightScheduler scheduler;
    int choice;
    do {
        cout << "\n--- Flight Scheduling System ---\n";
        cout << "1. Add Flight\n";
        cout << "2. Remove Flight\n";
        cout << "3. Display Schedule\n";
        cout << "4. Search Flight\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string fn, src, dest, arr, dep, gate;
                cout << "Enter Flight Number: ";
                cin >> fn;
                cout << "Enter Source: ";
                cin >> src;
                cout << "Enter Destination: ";
                cin >> dest;
                cout << "Enter Arrival Time: ";
                cin >> arr;
                cout << "Enter Departure Time: ";
                cin >> dep;
                cout << "Enter Gate: ";
                cin >> gate;
                scheduler.addFlight(Flight(fn, src, dest, arr, dep, gate));
                break;
            }
            case 2: {
                string fn;
                cout << "Enter Flight Number to Remove: ";
                cin >> fn;
                scheduler.removeFlight(fn);
                break;
            }
            case 3:
                scheduler.displaySchedule();
                break;
            case 4: {
                string fn;
                cout << "Enter Flight Number to Search: ";
                cin >> fn;
                scheduler.searchFlight(fn);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
	}
	if (a==3)
	{
		graph1 g;
    for(int i=0; i<10; i++)
    {
    	for(int j=0; j<10; j++)
    	{
    		if(i!=j)
    		g.addedge(i,j);
		}
	}
    g.primMST();
	}
	else
	cout<<"Invalid entry ...."<<endl;
}