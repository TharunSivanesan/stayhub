#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Guest
{
public:
    string guestname, bookername, purpose, arrival, departure;
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
    }
};
unordered_map<string, Guest> bookings, approvedRequests;
class GuestHouse
{
private:
    string name;
    int numSuiteRooms;
    int numMiniSuiteRooms;
    int numNormalRooms;

public:
    unordered_map<int, string> roomType;
    unordered_map<int, Guest> listofresidents;
    GuestHouse(const string &n, int suite, int miniSuite, int normal)
    {
        name = (n), numSuiteRooms = (suite), numMiniSuiteRooms = (miniSuite), numNormalRooms = (normal);
        for (int i = 0; i < suite; i++)
        {
            roomType[101 + i] = "SUITE";
        }
        for (int i = 0; i < miniSuite; i++)
        {
            roomType[201 + i] = "MINISUITE";
        }
        for (int i = 0; i < normal; i++)
        {
            roomType[301 + i] = "NORMAL";
        }
    }

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
            cout << this->name << ":" << endl;
            cout << "-----------" << endl;
            cout << "Guest\t\tRoom No\t\tCheck-in\tCheck-out:" << endl;
            for (auto i = listofresidents.begin(); i != listofresidents.end(); i++)
            {
                Guest guest = (*i).second;
                cout << guest.guestname << "\t" << (*i).first << "\t";
                cout << guest.arrival << "\t" << guest.departure << endl;
            }
        }
    }
    Guest checkout()
    {
        cout << "Enter the room you want to check-out:";
        int rn;
        cin >> rn;
        Guest guest;
        guest.guestname = "NIL";
        if (listofresidents.find(rn) == listofresidents.end())
        {
            cout << "Room is not occupied" << endl;
            return guest;
        }
        else
        {
            guest = listofresidents[rn];
            listofresidents.erase(rn);
            cout << "Room no " << rn << " is checked out." << endl;
            if (roomType[rn] == "SUITE")
            {
                this->numSuiteRooms++;
            }
            else if (roomType[rn] == "MINISUITE")
            {
                this->numMiniSuiteRooms++;
            }
            else
            {
                this->numNormalRooms++;
            }
        }
        return guest;
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
    string email;

    void setDetails(string un, string pw, string contact, string email)
    {
        this->username = un;
        this->password = pw;
        this->contactno = contact;
        this->email = email;
    }
};
class User : protected globalUser
{
private:
    string inbox;

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
        if (inbox.empty())
        {
            cout << "No Bookings made. ";
            return;
        }
        cout << inbox << endl;
    }
    void notification(Guest guest)
    {
        string s;
        s = "Your booking request for ";
        s += (guest.no_of_rooms + '0');
        s += " rooms for " + guest.guestname;
        s += " has been approved. The Guest House will get back to you. Kindly wait. ";
        this->inbox = s;
    }
    // void notification()
    // {
    //     this->inbox = "Your booking request has been denied. ";
    // }
    void notification(string s)
    {
        this->inbox = s;
    }
    void bookRoom()
    {
        if (bookings.find(username) != bookings.end())
        {
            cout << "You have a pending booking request.Please wait for approval of the previous booking." << endl;
            return;
        }
        cout << "Undertaking:" << endl;
        cout << "(To be given by the faculty members/ non-teaching staff/ student(s) requiring accommodation for their guests/parents)" << endl;
        cout << "a. Certified that the visit of the guest(s) is related to the activities of official/personal. I take responsibility for the payment of bills including food charges (if any) of the Guest House." << endl;
        cout << "b. The guest(s) is (are) personally known to me and I am responsible for his/her conduct." << endl;
        cout << "c. I hereby undertake to vacate the room in the Guest House, if allotted, on the expiry of the sanctioned period. In case I fail to do so, I will be liable to be charged penal rent (if any)." << endl;
        cout << "d. I have read the NITT Guest house terms & conditions of and these are acceptable." << endl;
        cout << "Do you accept:(enter 1):";
        int accept, food;
        cin >> accept;
        if (accept == 0)
        {
            cout << "Booking aborted as terms were not followed.";
            return;
        }
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
        string at, dt;
        cout << "Check-in(dd-mm-yyyy)";
        cin >> at;
        cout << "Check-out(dd-mm-yyyy)";
        cin >> dt;
        guest.setDates(at, dt);
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
        cout << "Enter purpose of visit:";
        getline(cin, guest.purpose);
        inbox = " Please Wait.Your request is been processed.";
        bookings.insert({this->username, guest});
    }
};
unordered_map<string, User> listofusers;

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
    string getUsername()
    {
        return username;
    }
    void updateRoomAvailability(Guest &guest)
    {
        int num = guest.no_of_rooms;
        if (guest.guesthouse_number == 1)
        {
            int a = 0, b = 0, c = 0;
            cout << "Enter room nos:";
            for (int i = 0; i < num; i++)
            {
                int rn;
                cin >> rn;
                if (kurunji.listofresidents.find(rn) != kurunji.listofresidents.end())
                {
                    cout << "Room is already occupied. Try a different room." << endl;
                    i--;
                }
                else
                {
                    if (kurunji.roomType[rn] == "SUITE")
                    {
                        a++;
                    }
                    else if (kurunji.roomType[rn] == "MINISUITE")
                    {
                        b++;
                    }
                    else if (kurunji.roomType[rn] == "NORMAL")
                    {
                        c++;
                    }
                    else
                    {
                        cout << "Invalid Room number.Try a different room.";
                        i--;
                    }
                    kurunji.listofresidents[rn] = guest;
                }
            }
            kurunji.updateAvailability(a, b, c);
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
            }
        }
    }
    void allotRoom(string username, Guest guest)
    {
        cout << "Accomodation in Kurunji(1)/Marudham(2):";
        cin >> guest.guesthouse_number;
        updateRoomAvailability(guest);
        string s = "Rooms have been allotted for guest " + guest.guestname;
        if (guest.guesthouse_number == 1)
        {
            s += " in Kurunji.";
        }
        else
        {
            s += " in Marudham.";
        }
        cout << s << endl;
        // Send notification to user
        listofusers[username].notification(s);
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
        category = n;
    }
    bool login(const string &u, const string &p)
    {
        return username == u && password == p;
    }
    void viewBookings()
    {
        int approval;
        vector<string> request;
        if (bookings.empty())
        {
            cout << "No requests.";
            return;
        }
        for (auto i = bookings.begin(); i != bookings.end(); i++)
        {
            string username = (*i).first;
            Guest guest = (*i).second;
            if (category <= guest.category)
            {
                request.push_back(username);
            }
        }
        if (request.empty())
        {
            cout << "Need a higher category authorizer to view the requests" << endl;
            return;
        }
        while (!request.empty())
        {
            cout << "Pending requests for users:" << endl;
            for (int i = 0; i < request.size(); i++)
            {

                cout << i + 1 << ")" << request[i] << endl;
            }
            cout << "Enter number to view corresponding User's request or enter 0 to quit:";
            int j;
            cin >> j;
            if (j == 0)
                return;
            j--;
            string username;
            username = request[j];
            Guest guest = bookings[username];
            guest.getDetails();
            cout << "Approve or Decline(1/0):";
            cin >> approval;
            if (approval == 1)
            {
                cout << "Approved the request of " << username << endl;
                approvedRequests.insert({username, guest});
                listofusers[username].notification(guest);
            }
            else
            {
                cout << "Denied the request of " << username << endl;
                cout << "Reason for denial:";
                string s, msg;
                getline(cin, s);
                msg = "Your booking request has been denied.Reason:";
                msg += s;
                listofusers[username].notification(msg);
            }
            bookings.erase(username);
            request.erase(request.begin() + j);
        }
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
        listofauthorizers.insert({username, authorizer});
    }

    while (1)
    {
        int mode;
        string username, password, contact, mailid;
        int choice;
        cout << "Sign up(0)/Log in(1)/Close Window(2):";
        cin >> mode;
        if (mode == 0)
        {
            while (1)
            {
                cout << "Enter username:";
                cin >> username;
                if (listofusers.find(username) != listofusers.end())
                {
                    cout << "Username already exists.Try another username." << endl;
                }
                else if (listofauthorizers.find(username) != listofauthorizers.end())
                {
                    cout << "Username already exists.Try another username." << endl;
                }
                else if (username == manager.getUsername())
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
                    listofusers.insert({username, user});
                    cout << "Sign in to proceed" << endl;
                    break;
                }
            }
        }
        else if (mode == 1)
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
                    if (!approvedRequests.empty())
                        cout << "You have new approved bookings!" << endl;
                    cout << "1)View guest list.\n2)View approved requests.\n3)Check-out Guests.\n4)Log out" << endl;
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
                        manager.viewApprovedRequests();
                    else if (choice == 3)
                    {
                        int gh;
                        cout << "Kurunji/Mardham(1/2):";
                        cin >> gh;
                        Guest guest;
                        if (gh == 1)
                            guest = kurunji.checkout();

                        else
                            guest = marutham.checkout();
                        if (guest.guestname != "NIL")
                            listofusers[guest.bookername].notification("Your guest has checked out. Kindly report to the guest house for payment.");
                    }

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
                        int log;
                        cout << "1)Room availability.\n2)View booking requests.\n3)Log out:";
                        cin >> log;
                        if (log == 1)
                        {
                            kurunji.displayAvailability();
                            marutham.displayAvailability();
                        }
                        else if (log == 2)
                        {
                            if (bookings.empty())
                            {
                                cout << "No requests pending." << endl;
                            }
                            else
                                authorizer.viewBookings();
                        }
                        else
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

                    while (1)
                    {
                        int choice;
                        cout << "---------------" << endl;
                        cout << "1)Room availability.\n2)Book Room\n3)Cancel Booking\n4)View inbox\n5)Log out: ";
                        cin >> choice;
                        if (choice == 1)
                        {
                            kurunji.displayAvailability();
                            marutham.displayAvailability();
                        }
                        else if (choice == 2)
                        {
                            user.bookRoom();
                        }
                        else if (choice == 3)
                        {
                            int c;
                            if (bookings.find(username) == bookings.end() && approvedRequests.find(username) == approvedRequests.end())
                                cout << "No active bookings made.";
                            else if (bookings.find(username) == bookings.end())
                            {
                                cout << "Your booking was approved for your guest " << approvedRequests[username].guestname << endl;
                                cout << "Do you still wish to cancel the booking?(enter 1 to cancel):";
                                cin >> c;
                                if (c == 1)
                                {
                                    approvedRequests.erase(username);
                                    cout << "Cancellation Successful" << endl;
                                    string s="No Bookings.";
                                    listofusers[username].notification(s);
                                }
                            }
                            else
                            {
                                cout << "Your booking is yet to be approved for your guest " << bookings[username].guestname << endl;
                                cout << "Do you still wish to cancel the booking?(enter 1 to cancel):";
                                cin >> c;
                                if (c == 1)
                                {
                                    bookings.erase(username);
                                    string s="No Bookings.";
                                    listofusers[username].notification(s);
                                }
                            }
                        }
                        else if (choice == 4)
                        {
                            user.viewInbox();
                            cout << endl;
                        }
                        else if (choice == 5)
                        {
                            cout << "Logging out.." << endl;
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Wrong password" << endl;
                }
            }
            else
            {
                cout << "Incorrect Username or Password ." << endl;
            }
        }
        else
        {
            cout << "Quitting program..";
            break;
        }
    }
}
