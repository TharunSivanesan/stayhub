#include <bits/stdc++.h>
using namespace std;

class Guest
{
public:
    vector<int> allotedrooms; // room no alloted by manager(multiple)
    string guestname, bookername, purpose, arrival, departure, remarks;
    int guesthouse_number, no_of_rooms, no_of_persons, category;
    bool undertaking;
    vector<string> food;
    void setDates(string at, string dt)
    {
        arrival = at;
        departure = dt;
    }
    void getDetails()
    {
        cout << "Details:" << endl;
        cout << "---------" << endl;
        cout << "Guest name:" << guestname << endl;
        cout << "No of rooms required:" << no_of_rooms << endl;
        cout << "No of persons:" << no_of_persons << endl;
        cout << "Category of guest:" << category << endl;
        cout << "Person making the booking:" << bookername << endl;
        cout << "Arrival on " << arrival << endl;
        cout << "Departure on " << departure << endl;
        if (food.empty())
            cout << "No food required." << endl;
        else
        {
            cout << "Breakfast:" << food[0] << endl;
            cout << "Lunch:" << food[1] << endl;
            cout << "Dinner:" << food[2] << endl;
        }
        cout << "Remarks:" << remarks;
    }
};
class GuestHouse
{
private:
    string name;
    int numSuiteRooms;
    int numMiniSuiteRooms;
    int numNormalRooms;

public:
    unordered_map<int, Guest> listofresidents;
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
    void viewguestlist()
    {
        if (listofresidents.empty())
            cout << "No residents currently." << endl;
        else
        {
            for (auto i = listofresidents.begin(); i != listofresidents.end(); i++)
            {
                cout << (*i).second.guestname << ":" << (*i).first << endl;
            }
        }
    }
};
GuestHouse kurunji("Kurunji", 3, 11, 22);
GuestHouse marutham("Marutham", 0, 0, 17);

class globalUser
{
protected:
    string username;
    string password;
    string contactno;
    string inbox;
    string remarks;
    void setDetails(string un, string pw, string contact, string email)
    {
        username = un;
        password = pw;
        contactno = contact;
        inbox = "No bookings";
        remarks = "No Remarks";
    }
};
class User : protected globalUser
{
private:
    // string username;
    // string password;
    // Details needed for booking

public:
    void init(string un, string pw, string contact, string mailid)
    {
        setDetails(un, pw, contact, mailid);
    }
    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }
    string getName()
    {
        return username;
    }
    void viewInbox()
    {
        cout << inbox << endl;
    }
    void notification(Guest guest)
    {
        inbox = "Your booking request for " + (guest.no_of_rooms + '0');
        inbox += " rooms for " + guest.guestname;
        inbox += " has been approved. The Guest House will get back to you. Kindly wait. ";
    }
    void notification()
    {
        inbox = "Your booking request has been denied. ";
    }
    void notification(string s)
    {
        inbox = s;
    }
    Guest bookRoom()
    {
        Guest guest;
        guest.bookername = getName();
        cout << "Enter name of guest:";
        cin >> guest.guestname;
        cout << "Enter Category proposed : ";
        cin >> guest.category;
        cout << "Enter no of rooms needed : ";
        cin >> guest.no_of_rooms;
        cout << "Enter no of persons:";
        cin >> guest.no_of_persons;
        string at, dt, t, purpose;
        cout << "Enter purpose of visit:";
        cin >> guest.purpose;
        cout << "Check-in(dd-mm-yyyy)";
        cin >> at;
        cout << "Check-out(dd-mm-yyyy)";
        cin >> dt;
        guest.setDates(at, dt);
        cout << "Undertaking:" << endl;
        cout << "(To be given by the faculty members/ non-teaching staff/ student(s) requiring accommodation for their guests/parents)" << endl;
        cout << "a. Certified that the visit of the guest(s) is related to the activities of official/personal. I take responsibility for the payment of bills including food charges (if any) of the Guest House." << endl;
        cout << "b. The guest(s) is (are) personally known to me and I am responsible for his/her conduct." << endl;
        cout << "c. I hereby undertake to vacate the room in the Guest House, if allotted, on the expiry of the sanctioned period. In case I fail to do so, I will be liable to be charged penal rent (if any)." << endl;
        cout << "d. I have read the NITT Guest house terms & conditions of and these are acceptable." << endl;
        cout << "Do you accept:(enter 1):";
        int accept, food;
        cin >> accept;
        if (accept == 1)
            guest.undertaking = true;
        cout << "Do you need food to be provided:(Enter 1)";
        cin >> food;
        if (food == 1)
        {
            cout << "Enter the food you need to be provided at breakfast lunch and dinner:";
            for (int i = 0; i < 3; i++)
            {
                string meal;
                cin >> meal;
                guest.food.push_back(meal);
            }
        }
        cout << "Any remarks?";
        cin >> guest.remarks;
        inbox = " Please Wait.Your request is been processed.";
        return guest;
    }
};
unordered_map<string, User> listofusers;
unordered_map<string, Guest> bookings;
unordered_map<string, Guest> approvedRequests;
class Manager : protected globalUser
{
    /*private:
        string username;
        string password;
    */
public:
    void init(string un, string pw, string contact, string mailid)
    {
        setDetails(un, pw, contact, mailid);
    }
    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }
    void updateRoomAvailability(Guest guest)
    {
        int num = guest.no_of_rooms;
        if (guest.guesthouse_number == 1)
        {
            kurunji.updateAvailability(num, 0, 0);
            cout << "Enter room nos:";
            for (int i = 0; i < num; i++)
            {
                int rn;
                cin >> rn;
                guest.allotedrooms.push_back(rn);
                kurunji.listofresidents[rn] = guest;
            }
        }
        else
        {
            marutham.updateAvailability(0, 0, num);
            cout << "Enter room nos:";
            for (int i = 0; i < num; i++)
            {
                int rn;
                cin >> rn;
                marutham.listofresidents[rn] = guest;
                guest.allotedrooms.push_back(rn);
            }
        }
    }
    void allotRoom(string username, Guest guest)
    {

        if (guest.category <= 2)
            guest.guesthouse_number = 1;
        else
            guest.guesthouse_number = 2;
        updateRoomAvailability(guest);
        string s = "Room allotted for guest: " + guest.guestname;
        cout << s << endl;
        // Send notification to user
        User user = listofusers[username];
        user.notification(s);
    }
    void viewApprovedRequests()
    {
        if (approvedRequests.empty())
            cout << "No approved bookings" << endl;
        else
        {
            cout << "Approved Requests:" << endl;
            for (auto i = approvedRequests.begin(); !(approvedRequests.empty()); i++)
            {
                string username = (*i).first;
                Guest guest = (*i).second;
                guest.getDetails();
                allotRoom(username, guest);
                approvedRequests.erase(i);
            }
        }
    }
};
class Authorizer : protected globalUser
{
private:
    // string username;
    // string password;
    int category;

public:
    void setDetails(string un, string pw, int n)
    {
        username = un;
        password = pw;
        inbox = "No pending requests";
        category = n;
    }
    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }
    void viewBookings()
    {
        int flag = 0;
        for (auto i = bookings.begin(); !(bookings.empty()); i++)
        {
            int approval;
            string username = (*i).first;
            Guest guest = (*i).second;
            if (category <= guest.category)
            {
                flag = 1;
                User user = listofusers[username];
                cout << "Name of the visitor " << guest.guestname << endl;
                cout << "Approve or Decline(1/0):";
                cin >> approval;
                if (approval == 1)
                {
                    cout << "Approved for " << guest.guestname << endl;
                    approvedRequests[username] = guest;
                    user.notification(guest);
                    bookings.erase(i);
                }
                else
                {
                    user.notification();
                    bookings.erase(i);
                }
            }
        }
        if (flag == 0)
            cout << "Need a higher category authorizer to view the requests" << endl;
        else
            cout << "Done authorizing booking requests." << endl;
    }
};
unordered_map<string, Authorizer> listofauthorizers; // the list of all the valid authoriser.for now 5 authorisers.

int main()
{
    Manager manager;
    manager.init("manager", "manager123", "0431-250-4810", "guesthouse@gmail.com");

    // init authorizers
    for (int i = 1; i <= 4; i++)
    {
        string username = "authorizer";
        username += i + '0';
        string password = "auth";
        password += (i + '0');
        password += "@123";
        Authorizer authorizer;
        authorizer.setDetails(username, password, i);
        listofauthorizers[username] = authorizer;
    }
    while (1)
    {
        int mode;
        string username, password, contact, mailid;
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
                    cout << "Enter contact no:";
                    cin >> contact;
                    cout << "Enter email:";
                    cin >> mailid;
                    User user;
                    user.init(username, password, contact, mailid);
                    listofusers[username] = user;
                    cout << "   Sign in to proceed" << endl;
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
                while (1)
                {
                    cout << "1)View guest list.\n2)Update room status.\n3)View approved requests.\n4)Log out" << endl;
                    int choice;
                    cin >> choice;
                    if (choice == 1)
                    {
                        int gh;
                        cout << "Kurunji/Mardham(1/2):";
                        cin >> gh;
                        if (gh == 1)
                            kurunji.viewguestlist();

                        else
                            marutham.viewguestlist();
                    }
                    else if (choice == 2)
                    {
                        kurunji.displayAvailability();
                        marutham.displayAvailability();
                        int gh, a, b, c;
                        cout << "Kurunji/Marudham(1/2):";
                        cin >> gh;
                        cout << "Enter three numbers(for suite, mini-suite, normal;give negative number to remove room):";
                        cin >> a >> b >> c;
                        if (gh == 1)
                            kurunji.updateAvailability(a, b, c);
                        else
                            marutham.updateAvailability(a, b, c);
                    }
                    else if (choice == 3)
                        manager.viewApprovedRequests();

                    else
                    {
                        cout << "Logging out.." << endl;
                        break;
                    }
                }
            }
            else if (listofauthorizers.find(username) != listofauthorizers.end())
            {
                Authorizer authorizer = listofauthorizers[username];
                if (authorizer.login(username, password))
                {
                    cout << "Logged in as Authorizer." << endl;
                    while (1)
                    {
                        if (bookings.empty())
                            cout << "No requests" << endl;
                        else
                        {
                            cout << "Pending Requests:" << endl;
                            authorizer.viewBookings();
                        }
                        int log;
                        cout << "Enter 0 to log out:";
                        cin >> log;
                        if (log == 0)
                        {
                            cout << "Logging out.." << endl;
                            break;
                        }
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
                    cout << "Welcome " << user.getName() << endl;
                    kurunji.displayAvailability();
                    marutham.displayAvailability();
                    while (1)
                    {
                        int choice;
                        cout << "1)Book Room\n2)View inbox\n3)Log out: ";
                        cin >> choice;
                        if (choice == 1)
                        {
                            Guest guest = user.bookRoom();
                            bookings[username] = guest;
                        }
                        else if (choice == 2)
                        {
                            user.viewInbox();
                            cout << endl;
                        }
                        else if (choice == 3)
                        {
                            cout << "Logging out" << endl;
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Wrong password";
                }
            }
            else
            {
                cout << "Username doesnt exist or incoorect password" << endl;
            }
        }
    }
}
