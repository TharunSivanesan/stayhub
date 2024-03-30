#include <bits/stdc++.h>
using namespace std;

class GuestHouse
{
private:
    string name;
    int numSuiteRooms;
    int numMiniSuiteRooms;
    int numNormalRooms;

public:
    GuestHouse(const string &n, int suite, int miniSuite, int normal)
        : name(n), numSuiteRooms(suite), numMiniSuiteRooms(miniSuite), numNormalRooms(normal) {}

    string getName() const
    {
        return name;
    }

    int getNumSuiteRooms() const
    {
        return numSuiteRooms;
    }

    int getNumMiniSuiteRooms() const
    {
        return numMiniSuiteRooms;
    }

    int getNumNormalRooms() const
    {
        return numNormalRooms;
    }

    void updateAvailability(int numSuite, int numMiniSuite, int numNormal)
    {
        numSuiteRooms -= numSuite;
        numMiniSuiteRooms -= numMiniSuite;
        numNormalRooms -= numNormal;
    }

    void displayAvailability() const
    {
        cout << "Availability for " << name << " Guest House:" << endl;
        cout << "Suite Rooms: " << numSuiteRooms << endl;
        cout << "Mini Suite Rooms: " << numMiniSuiteRooms << endl;
        cout << "Normal Rooms: " << numNormalRooms << endl;
    }
};

class User
{
private:
    string username;
    string password;

public:
    User(const string &u, const string &p) : username(u), password(p) {}

    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }

    void bookRoom()
    {
        // Logic for booking a room
        cout << "Booking a room..." << endl;
    }
};

class Authorizer
{
private:
    string username;
    string password;

public:
    Authorizer(const string &u, const string &p) : username(u), password(p) {}

    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }

    void approveRequest(User &user)
    {
        // Logic for approving a request
        cout << "Request approved for user: " << user.getUsername() << endl;
    }

    void declineRequest(User &user)
    {
        // Logic for declining a request
        cout << "Request declined for user: " << user.getUsername() << endl;
    }
};

class Manager
{
private:
    string username;
    string password;
    vector<User> approvedRequests;

public:
    Manager(const string &u, const string &p) : username(u), password(p) {}

    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }

    void viewApprovedRequests()
    {
        cout << "Approved Requests:" << endl;
        for (const auto &user : approvedRequests)
        {
            cout << "- " << user.getUsername() << endl;
        }
    }

    void allotRoom(User &user)
    {
        // Logic for allotting a room
        cout << "Room allotted for user: " << user.getUsername() << endl;
    }

    void updateRoomAvailability()
    {
        // Logic for updating room availability
        cout << "Room availability updated." << endl;
    }

    void addApprovedRequest(const User &user)
    {
        approvedRequests.push_back(user);
    }
};

int main()
{
    GuestHouse kurunji("Kurunji", 10, 20, 30);
    GuestHouse marutham("Marutham", 15, 25, 35);
    User user("user", "user123");
    Authorizer authorizer("authorizer", "auth123");
    Manager manager("manager", "manager123");
    while (1)
    {
        string username, password;
        int choice;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (user.login(username, password))
        {
            cout << "Logged in as User." << endl;
            kurunji.displayAvailability();
            marutham.displayAvailability();
            user.bookRoom();
        }
        else if (authorizer.login(username, password))
        {
            cout << "Logged in as Authorizer." << endl;
            cout << "1. Approve Request\n2. Decline Request\nEnter choice: ";
            cin >> choice;
            if (choice == 1)
            {
                authorizer.approveRequest(user);
                manager.addApprovedRequest(user);
            }
            else if (choice == 2)
            {
                authorizer.declineRequest(user);
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
        }
        else if (manager.login(username, password))
        {
            cout << "Logged in as Manager." << endl;
            manager.viewApprovedRequests();
            cout << "Allotting room..." << endl;
            manager.allotRoom(user);
            manager.updateRoomAvailability();
        }
        else
        {
            cout << "Invalid username or password." << endl;
        }
    }
}
