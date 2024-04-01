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
GuestHouse kurunji("Kurunji", 3, 11, 22);
GuestHouse marutham("Marutham", 0, 0, 17);
class User
{
private:
    string username;
    string password;

public:
    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }
    void putDetails(string un, string pw)
    {
        username = un;
        password = pw;
    }
    string getName()
    {
        return username;
    }

    void bookRoom()
    {
        // Logic for booking a room
        cout << "Booking a room..." << endl;
    }
};
vector<User> bookings;
vector<User> approvedRequests;
unordered_map<string, User> listofusers;

class Authorizer
{
private:
    string username;
    string password;
    int category;

public:
    void setDetails(string un, string pw)
    {
        username = un;
        password = pw;
    }

    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }
};
unordered_map<string, Authorizer> listofauthorizers;//the list of all the valid authoriser.for now 5 authorisers.

class Manager
{
private:
    string username;
    string password;

public:
    Manager(const string &u, const string &p) : username(u), password(p) {}
    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }
    void viewApprovedRequests()
    {
        //maintain a vector which holds approved requests.
        cout << "Approved Requests:" << endl;
        for (auto user : approvedRequests)
        {
            cout << "- " << user.getName() << endl;
            // manager.allotRoom(user);
        }
    }

    void allotRoom(User user)
    {
        // Logic for allotting a room
        cout << "Room allotted for user: " << user.getName() << endl;
    }

    void updateRoomAvailability()
    {

        cout << "Room availability updated." << endl;
    }
};
Manager manager("manager", "manager123");

int main()
{
    // init authorizers
    for (int i = 0; i < 5; i++)
    {
        string username = "authorizer";
        username += i + '0';
        string password = "auth";
        password += (i + '0');
        password += "@123";
        Authorizer authorizer;
        authorizer.setDetails(username, password);
        listofauthorizers[username] = authorizer;
    }
    while (1)
    {
        int mode;
        string username, password;
        int choice;
        cout << "Signin(0)/Signup(1):";
        cin >> mode;
        if (mode == 1)
        {
            while (1)
            {
                cout << "Enter username:";
                cin >> username;
                if (listofusers.find(username) != listofusers.end())
                {
                    cout << "Username already exists.Try another username." << endl;
                }
                else
                {
                    cout << "Enter password:";
                    cin >> password;
                    User user;
                    user.putDetails(username, password);
                    listofusers[username] = user;
                    break;
                }
            }
        }
        else
        {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (manager.login(username, password))
            {
                cout << "Logged in as Manager." << endl;
                manager.viewApprovedRequests();
                cout << "Update rooms?";
                int update;
                cin >> update;
                if (update)
                    manager.updateRoomAvailability();
            }
            else if (listofauthorizers.find(username) != listofauthorizers.end())
            {
                Authorizer authorizer = listofauthorizers[username];
                if (authorizer.login(username, password))
                {
                    cout << "Logged in as Authorizer." << endl;
                    if (bookings.empty())
                        cout << "No requests";
                    else
                    {
                        cout << "Pending Requests:" << endl;
                    }
                }
                else
                {
                    cout << "Wrong password." << endl;
                }
            }
            else if (listofusers.find(username) != listofusers.end())
            {
                User user = listofusers[username];
                if (user.login(username, password))
                {
                    cout << "Logged in as User." << endl;
                    kurunji.displayAvailability();
                    marutham.displayAvailability();
                    int book;
                    cin >> book;
                    if (book){
                        user.bookRoom();/*logic for room booking for user.maintain
                         a vector of requests which the authoriser can approve*/
                    }
                }
                else{
                    cout<<"Wrong password";
                }
            }
            else
            {
                cout << "Username doesnt exist or incoorect password" << endl;
            }
        }
    }
}
