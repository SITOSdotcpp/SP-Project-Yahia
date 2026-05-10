#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

//----------------------------------------------------------------------------------------------
//-----------------------------------| SIZES & CONSTANTS | -------------------------------------
//----------------------------------------------------------------------------------------------
const int FLOORS = 5;
const int ROOMS = 10;
const int ADMINCOUNT = 10;
const int MAXREVIEWS = 1000;
const int CUSTSIZE = 50;

//----------------------------------------------------------------------------------------------
//----------------------------------- | STRUCTS | ----------------------------------------------
//----------------------------------------------------------------------------------------------
struct Date
{
    int day, month, year;
};

struct Admin
{

    string Admin_user_name;
    string Admin_password;
    int Admin_id;
};

struct Review
{

    Date Date_valid;
    string Review_content;
    int Review_id;
    int Room_number;
    bool Seen = false;
};

// struct RoomNumber
// {
//     int FloorNumber, FlatNumber;
// };

struct stRoom
{
    // RoomNumber RoomNumber;
    int roomNumber;
    string RoomID; // is Equal to CustomerID
    bool isAvailable = true;
};

struct Customer
{
    string CustomerID;
    string Name;
    string Email;
    string UserName;
    string Password;
    string CreditCardNumber;
    Date StartDate;
    Date EndDate;
    int roomNumber;
};

//----------------------------------------------------------------------------------------------
//----------------------------------- | DECLARING ARRAYS | -------------------------------------
//----------------------------------------------------------------------------------------------
stRoom roomsArr[FLOORS][ROOMS];
Customer customersArr[CUSTSIZE];
Admin adminsArr[ADMINCOUNT];
Review reviewsArr[MAXREVIEWS];

//----------------------------------------------------------------------------------------------
//------------------------------------- | DELIVERABLES | ---------------------------------------
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//----------------------------------- | ADMIN FUNCTIONS | --------------------------------------
//----------------------------------------------------------------------------------------------
void start(int &resCount, int &custCount);
void AdminMenu(int &resCount, int &custCount);
void adminAddReservation(int &resCount, int &custCount);
void editReservation(int &resCount, int &custCount);
void View_room_reviews(int &resCount, int &countCount);
void Admin_logout(int &resCount, int &custCount);
bool Admin_login(int &resCount, int &custCount);
void initDate(int &day, int &month, int &year);
void showLastMonth(Review review[]);

void AdminMenu(int &resCount, int &custCount)
{
    int choice;
    cout << "[1] View Room Reviews\n";
    cout << "[2] Add Reservation\n";
    cout << "[3] Edit Reservation\n";
    cout << "[4] Log out\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        View_room_reviews(resCount, custCount);
        break;
    case 2:
        adminAddReservation(resCount, custCount);
        break;
    case 3:
        editReservation(resCount, custCount);
        break;
    case 4:
        Admin_logout(resCount, custCount);
    default:
        cout << "Please enter a valid choice from the ones given.\n\n";
        AdminMenu(resCount, custCount);
        break;
    }
}

void adminAddReservation(int &resCount, int &custCount)
{
    int rNum;
    cout << "\n    Admin: Add New Reservation    \n";
    cout << "Enter Room Number to reserve: ";
    cin >> rNum;

    bool roomFound = false;
    for (int i = 0; i < FLOORS; i++)
    {
        for (int j = 0; j < ROOMS; j++)
        {
            if (roomsArr[i][j].roomNumber == rNum)
            {
                roomFound = true;
                if (roomsArr[i][j].isAvailable)
                {

                    roomsArr[i][j].isAvailable = false;

                    customersArr[resCount].roomNumber = rNum;
                    cout << "Enter Customer Name: ";
                    cin >> customersArr[resCount].Name;
                    cout << "Enter Start Date";
                    cin >> customersArr[resCount].StartDate.day;
                    cin >> customersArr[resCount].StartDate.month;
                    cin >> customersArr[resCount].StartDate.year;
                    cout << "Enter End Date";
                    cin >> customersArr[resCount].EndDate.day;
                    cin >> customersArr[resCount].EndDate.month;
                    cin >> customersArr[resCount].EndDate.year;

                    resCount++;
                    cout << "Reservation completed successfully by Admin.\n";
                }
                else
                {
                    cout << "Error: This room is already reserved!\n";
                }
                break;
            }
        }
    }
    if (!roomFound)
    {
        cout << "Room not found!\n";
    }

    AdminMenu(resCount, custCount);
}

void editReservation(int &resCount, int &custCount)
{
    int rNum;
    bool found = false;
    cout << "\n    Edit Existing Reservation    \n";
    cout << "Enter the Reserved Room Number to edit: ";
    cin >> rNum;

    for (int i = 0; i < resCount; i++)
    {
        if (customersArr[i].roomNumber == rNum)
        {
            found = true;
            cout << "Reservation found. Current Customer: "
                 << customersArr[i].Name << endl;

            cout << "Enter New Customer Name: ";
            cin >> customersArr[i].Name;
            cout << "Enter New Start Date";
            cin >> customersArr[resCount].StartDate.day;
            cin >> customersArr[resCount].StartDate.month;
            cin >> customersArr[resCount].StartDate.year;
            cout << "Enter New End Date";
            cin >> customersArr[resCount].EndDate.day;
            cin >> customersArr[resCount].EndDate.month;
            cin >> customersArr[resCount].EndDate.year;

            cout << "Reservation updated successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "No active reservation found for this room number.\n";
    }
    AdminMenu(resCount, custCount);
}

void initDate(int &day, int &month, int &year)
{
    time_t now = time(0);

    tm *localTime = localtime(&now);
    year = 1899 + localTime->tm_year + 1;
    month = 1 + localTime->tm_mon;
    day = localTime->tm_mday;
}

void showLastMonth(Review review[])
{
    int day, month, year;
    initDate(day, month, year);

    for (int i = 0; i < MAXREVIEWS; i++)
    {
        if (review[i].Date_valid.year == year && review[i].Date_valid.month - month == 0)
        {
            cout << "Room: " << reviewsArr[i].Room_number << endl;
            cout << "Review: " << reviewsArr[i].Review_content << endl;
        }
        else if (review[i].Date_valid.year == year && month - review[i].Date_valid.month == 1 && review[i].Date_valid.day >= day)
        {
            cout << "Room: " << reviewsArr[i].Room_number << endl;
            cout << "Review: " << reviewsArr[i].Review_content << endl;
        }
    }
}

void View_room_reviews(int &resCount, int &custCount)
{
    int choice;
    cout << "1 for All reviews" << endl;
    cout << "2 for Unseen reviews" << endl;
    cout << "3 for Last 30 days reviews" << endl;
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < MAXREVIEWS; i++)
        {
            cout << "Room: " << reviewsArr[i].Room_number << endl;
            cout << "Review: " << reviewsArr[i].Review_content << endl;
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < MAXREVIEWS; i++)
        {
            if (reviewsArr[i].Seen == false)
            {
                cout << "Room: " << reviewsArr[i].Room_number << endl;
                cout << "Review: " << reviewsArr[i].Review_content << endl;
                reviewsArr[i].Seen = true;
            }
        }
    }
    else if (choice == 3)
    {
        showLastMonth(reviewsArr);
    }

    AdminMenu(resCount, custCount);
}

void Admin_logout(int &resCount, int &custCount)
{
    cout << "Logged out successfully!" << endl;
    start(resCount, custCount);
}

bool Admin_login(int &resCount, int &custCount)
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << endl;
    cout << "Enter password: ";
    cin >> password;
    cout << endl;

    for (int i = 0; i < ADMINCOUNT; i++)
    {
        if (username == adminsArr[i].Admin_user_name && password == adminsArr[i].Admin_password)
        {
            cout << "welcome" << endl;
            AdminMenu(resCount, custCount);
            return true;
        }
    }
    cout << "Invalid!" << endl;
    return false;
}

//----------------------------------------------------------------------------------------------
//----------------------------------- | CUSTOMER FUNCTIONS | -----------------------------------
//----------------------------------------------------------------------------------------------
int ReadNumInRange(string message, int From, int To);
stRoom ReadReserveRoomInfo(int &custCount);
bool CheckRoomIsBooked(stRoom Room);
bool Ask(string TheAsk);
void ReserveRoom(int &resCount, int &custCount);
void CancelRoomScreen(int &custCount);
stRoom ReadCancelRoomInfo(int &custCount);
void checkAvailability(int &resCount, int &custCount);
void login_or_signup(int &custCount);
void signUp(int &custCount);
void login(int &resCount, int &custCount);
void menu(int &resCount, int &custCount);
void review(int &resCount, int &custCount);
void customerLogOut(int &resCount, int &custCount);

void customerLogOut(int &resCount, int &custCount)
{
    cout << "Logged out successfully.\n";
    start(resCount, custCount);
}

int ReadNumInRange(string message, int From, int To)
{
    int Num;
    cout << message << " From " << From << " To " << To << " ? ";
    cin >> Num;
    while (Num > To || Num < From)
    {
        cout << "\nInvalid Number," << message << " From " << From << " To " << To << " ? ";
        cin >> Num;
    }
    return Num;
}
stRoom ReadReserveRoomInfo(int &custCount)
{
    stRoom Room;

    Room.roomNumber = ReadNumInRange("\nPlease Enter Flat Number ? ", 1, 50);

    cout << "\nPLease Enter Start Date ? (DD/MM/YYYY)?";
    cin >> customersArr[custCount].StartDate.day >> customersArr[custCount].StartDate.month >> customersArr[custCount].StartDate.year;
    cout << "\nPLease Enter End Date ? (DD/MM/YYYY)?";
    cin >> customersArr[custCount].EndDate.day >> customersArr[custCount].EndDate.month >> customersArr[custCount].EndDate.year;
    cout << "\nPlease Enter Credit Card Number ? ";
    cin >> customersArr[custCount].CreditCardNumber;

    return Room;
}

bool CheckRoomIsBooked(stRoom Room)
{
    for (int i = 0; i < FLOORS; i++)
    {
        for (int j = 0; j < ROOMS; j++)
        {
            if (roomsArr[i][j].roomNumber == Room.roomNumber) // if room status = true will return true otherwise false
            {
                cout << roomsArr[i][j].isAvailable << '\n';
                return roomsArr[i][j].isAvailable;
            }
        }
    }
    return false;
}

void ReserveRoomScreen(int &custCount)
{
    // system("cls");
    cout << "\n\n";
    cout << "--------------------------------------------------\n";
    cout << "                Reserve Room Screen                \n";
    cout << "--------------------------------------------------\n\n";
}

bool Ask(string TheAsk)
{
    char IsYes = 'y';
    cout << TheAsk;
    cin >> IsYes;
    if (IsYes == 'y' || IsYes == 'Y')
        return true;
    else
        return false;
}

void ReserveRoom(int &resCount, int &custCount) // this is the main function
{

    ReserveRoomScreen(custCount); // clear screen and show header
    stRoom Room;
    Room = ReadReserveRoomInfo(custCount);

    if (Ask("\n\nAre you sure you want reserve this room ? (y/n)? "))
    {
        if (!CheckRoomIsBooked(Room)) // if booked
            cout << "\nSorry,This Room is already booked.\n";
        else
        {
            // roomsArr[Room.roomNumber - 1][Room.RoomNumber.FlatNumber - 1].BookingStatus = true;
            // roomsArr[Room.roomNumber - 1][Room.RoomNumber.FlatNumber - 1].RoomID = GlobalCustomer.CustomerID;

            for (int i = 0; i < FLOORS; i++)
            {
                for (int j = 0; j < ROOMS; j++)
                {
                    if (roomsArr[i][j].roomNumber == Room.roomNumber)
                    {
                        roomsArr[i][j].isAvailable = false;
                        roomsArr[i][j].RoomID = customersArr[custCount].CustomerID;
                    }
                }
            }

            cout << "\n\nDone successfully, The Room has been successfully booked.\n";
        }
    }
    // cout << "\n\n\nPress any key to go Back to main menu...";
    // system("pause>0");
    cout << "\n\n\n";
    menu(resCount, custCount);
}
void CancelRoomScreen(int &custCount)
{
    system("cls");
    cout << "--------------------------------------------------\n";
    cout << "                Cancel Room Screen                \n";
    cout << "--------------------------------------------------\n\n";
}
stRoom ReadCancelRoomInfo(int &custCount)
{
    stRoom Room;

    Room.roomNumber = ReadNumInRange("\nPlease Enter Flat Number ? ", 1, 50);
    Room.RoomID = customersArr[custCount].CustomerID;
    return Room;
}
bool CheckCustomerIsBookedThisRoomByCustomer(stRoom Room)
{
    // return (Room.RoomID == roomsArr[Room.roomNumber - 1][Room.RoomNumber.FlatNumber - 1].RoomID && roomsArr[Room.roomNumber - 1][Room.RoomNumber.FlatNumber - 1].BookingStatus);
    for (int i = 0; i < FLOORS; i++)
    {
        for (int j = 0; j < ROOMS; j++)
        {
            if (Room.RoomID == roomsArr[i][j].RoomID && !roomsArr[i][j].isAvailable)
            {
                return true;
                break;
            }
        }
    }
    return false;
}
void CancelRoom(int &custCount) // this is the main function
{

    CancelRoomScreen(custCount); // clear screen and show header

    stRoom Room;
    Room = ReadCancelRoomInfo(custCount);

    if (Ask("\n\nAre you sure you want Cancel this room ? (y/n)? "))
    {
        if (CheckCustomerIsBookedThisRoomByCustomer(Room)) // if was booked
        {
            for (int i = 0; i < FLOORS; i++)
            {
                for (int j = 0; j < ROOMS; j++)
                {
                    if (roomsArr[i][j].RoomID == Room.RoomID)
                    {
                        roomsArr[i][j].isAvailable = true;
                        roomsArr[i][j].RoomID = "";
                        break;
                    }
                }
            }

            cout << "\n\nDone successfully, The Room has been successfully Cancelled.\n";
        }
        else
            cout << "\nErorr!\n This Room is NOT booked.\n";
    }

    cout << "\n\n\nPress any key to go Back to main menu...";
    system("pause>0");
}

void checkAvailability(int &resCount, int &custCount)
{

    int rNum;
    bool found = false;
    cout << "\n    Check Room Availability   \n";
    cout << "Enter Room Number: ";
    cin >> rNum;

    for (int i = 0; i < FLOORS; i++)
    {
        for (int j = 0; j < ROOMS; j++)
        {
            if (roomsArr[i][j].roomNumber == rNum)
            {
                found = true;
                if (roomsArr[i][j].isAvailable)
                {
                    cout << "Good news! Room " << rNum << " is Available.\n";
                }
                else
                {
                    cout << "Sorry, Room " << rNum << " is already Reserved.\n";
                }
                break;
            }
        }
    }

    if (!found)
    {
        cout << "Room number not found in our system.\n";
    }
    cout << "\n\n";
    menu(resCount, custCount);
}

void login_or_signup(int &custCount)
{
    int choice;
    cout << "welcome to our hotel \n"
         << "please enter your choice \n";
    cout << "login[1]       sign up[2]:  ";
    cin >> choice;
    if (choice == 1)
    {
        login(custCount);
    }
    else if (choice == 2)
    {
        signUp(custCount);
    }
    else
    {
        cout << "invalid choice \n"
             << "please re-enter choice \n";
        login_or_signup(custCount);
    }
}
void signUp(int &custCount)
{
    bool check;
    cout << "enter your email:";
    cin >> customersArr[custCount].Email;
    cout << "enter your name:";
    cin.ignore();
    cin.clear();
    getline(cin >> ws, customersArr[custCount].Name);
    cout << "enter your creidt card number: ";
    cin.ignore();
    cin.clear();
    cin >> customersArr[custCount].CreditCardNumber;
    do
    {
        check = true;
        cout << "enter a new username: ";
        cin >> customersArr[custCount].UserName;
        for (int k = 0; k < custCount; k++)
        {
            if (customersArr[custCount].UserName == customersArr[k].UserName)
            {
                cout << "invalid username \n"
                     << "please re-enter username \n";
                check = false;
            }
        }

    } while (!check);
    cout << "enter your password: ";
    cin >> customersArr[custCount].Password;
    cout << "please enter your id number: ";
    cin >> customersArr[custCount].CustomerID;
    custCount++;
    cout << "account is activated successfully \n";
    char choice;
    do
    {
        cout << "do you want to log in now?(y/n): ";
        cin >> choice;
        if (choice == 'y' or choice == 'Y')
        {
            login(custCount);
            break;
        }
        else if (choice == 'n' or choice == 'N')
        {
            cout << "thank you for your visit \n";
            break;
        }
        else
        {
            cout << "invalid choice \n"
                 << "please re-enter choice \n";
            continue;
        }
    } while (true);
}
void login(int &resCount, int &custCount)
{

    cout << "welcome to our site \n";
    cout << "please enter your username and password \n";

    bool check = false;
    do
    {

        cout << "username: ";
        cin >> customersArr[custCount].UserName;
        cout << "password:  ";
        cin >> customersArr[custCount].Password;
        for (int j = 0; j < custCount; j++)
        {
            if (customersArr[custCount].UserName == customersArr[j].UserName &&
                customersArr[custCount].Password == customersArr[j].Password)
            {
                cout << "login sucess \n";
                check = true;
                menu(resCount, custCount);
                break;
            }
        }
        if (!check)
        {
            cout << "invalid username or password \n"
                 << "please re-enter \n";
        }
    } while (!check);
}
void menu(int &resCount, int &custCount)
{
    cout << "Check room availability [1]\n";
    cout << "Reserve a room [2]\n";
    cout << "add review [3]\n";
    cout << "log out [4]\n";
    int choice;
    cin >> choice;
    do
    {
        // if (choice == 5)
        // {
        //     cout << "thank you \n";
        //     break;
        // }
        // else if (choice == 2)
        // {
        //     review(custCount);
        //     break;
        // }
        // else
        // {
        //     cout << "invalid choice \n"
        //          << "please re-enter your choice \n";
        //     menu(custCount);
        //     break;
        // }

        switch (choice)
        {
        case 1:
            checkAvailability(custCount);
            break;
        case 2:
            ReserveRoom(custCount);
            break;
        case 3:
            review(custCount);
            break;
        case 4:
            customerLogOut(resCount, custCount);
            break;
        default:
            cout << "invalid choice \n"
                 << "please re-enter your choice \n";
            menu(resCount, custCount);
            break;
        }

    } while (true);
}
int counter_of_review_number = 0;
void review(int &resCount, int &custCount)
{
    reviewsArr[custCount].Review_id = 1 + counter_of_review_number;
    cout << "please enter your room number: ";
    cin >> reviewsArr[custCount].Room_number;
    cout << "enter your review: ";
    cin.ignore();
    getline(cin, reviewsArr[custCount].Review_content);
    counter_of_review_number++;
    cout << "****thank you for your review**** \n";
    menu(resCount, custCount);
}

//----------------------------------------------------------------------------------------------
//------------------------------------- | START FUNCTION | -------------------------------------
//----------------------------------------------------------------------------------------------
void start(int &resCount, int &custCount)
{
    int accountChoice;
    cout << "\t\t Welcome!\n";
    cout << "\tPlease choose account type\n";
    cout << "[1] Customer\n";
    cout << "[2] Admin\n";
    cin >> accountChoice;
    switch (accountChoice)
    {
    case 1:
        login_or_signup(custCount);
        break;
    case 2:
        Admin_login(resCount, custCount);
        break;
    }
}

//----------------------------------------------------------------------------------------------
//----------------------------------- | MAIN FUNCTION | ----------------------------------------
//----------------------------------------------------------------------------------------------

int main()
{
    //      Initializing Arrays & Variables
    for (int i = 0; i < FLOORS; i++)
    {
        for (int j = 0; j < ROOMS; j++)
        {
            roomsArr[i][j].roomNumber = (i + 1) * ROOMS - (ROOMS - (j + 1));
        }
    }

    int resCount = 0;
    int custCount = 0;

    //      Running Sequence
    start(resCount, custCount);
}