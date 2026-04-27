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
const int CUSTSIZE = 500;

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
    string Review_content = "###";
    int Review_id;
    int Room_number;
    bool Seen = false;
};

struct stRoom
{
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
    int roomNumber = -1;
};

//----------------------------------------------------------------------------------------------
//----------------------------------- | DECLARING ARRAYS & VARIABLES | -------------------------
//----------------------------------------------------------------------------------------------
stRoom roomsArr[FLOORS][ROOMS];
Customer customersArr[CUSTSIZE];
Admin adminsArr[ADMINCOUNT];
Review reviewsArr[MAXREVIEWS];
int loggedInIndex = -1;
int counter_of_review_number = 6;

//----------------------------------------------------------------------------------------------
//------------------------------ | Checking Choice Validition | --------------------------------
//----------------------------------------------------------------------------------------------
void Check_Choice_Validity(int &choice, int start, int end);

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
void View_room_reviews(int &resCount, int &custCount);
void Admin_logout(int &resCount, int &custCount);
bool Admin_login(int &resCount, int &custCount);
void initDate(int &day, int &month, int &year);
void showLastMonth();

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

int findCust(string &username)
{
    for (int i = 0; i < CUSTSIZE; i++)
    {
        if (customersArr[i].UserName == username)
        {
            return i;
        }
    }
    return -1;
}

void adminAddReservation(int &resCount, int &custCount)
{
    int rNum;
    string username;
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

                    cout << "Enter Customer Username: ";
                    cin >> username;
                    int idx = findCust(username);
                    if (idx == -1)
                    {
                        cout << "Customer username not found.\n";
                        roomsArr[i][j].isAvailable = true;
                        break;
                    }

                    customersArr[idx].roomNumber = rNum;
                    roomsArr[i][j].RoomID = customersArr[idx].CustomerID;
                    cout << "Enter Start Date:\n";
                    cin >> customersArr[idx].StartDate.day;
                    cin >> customersArr[idx].StartDate.month;
                    cin >> customersArr[idx].StartDate.year;
                    cout << "Enter End Date:\n";
                    cin >> customersArr[idx].EndDate.day;
                    cin >> customersArr[idx].EndDate.month;
                    cin >> customersArr[idx].EndDate.year;

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
            cin >> customersArr[i].StartDate.day;
            cin >> customersArr[i].StartDate.month;
            cin >> customersArr[i].StartDate.year;
            cout << "Enter New End Date";
            cin >> customersArr[i].EndDate.day;
            cin >> customersArr[i].EndDate.month;
            cin >> customersArr[i].EndDate.year;

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

void showLastMonth()
{
    int day, month, year;
    initDate(day, month, year);

    for (int i = 0; i < MAXREVIEWS; i++)
    {
        if (reviewsArr[i].Date_valid.year == year && reviewsArr[i].Date_valid.month - month == 0)
        {
            cout << "Review for Room: " << reviewsArr[i].Room_number << endl;
            cout << "Time of Review: " << reviewsArr[i].Date_valid.day << "/" << reviewsArr[i].Date_valid.month << "/" << reviewsArr[i].Date_valid.year << " .\n";
            cout << "Review: " << reviewsArr[i].Review_content << endl;
            reviewsArr[i].Seen = true;
        }
        else if (reviewsArr[i].Date_valid.year == year && month - reviewsArr[i].Date_valid.month == 1 && reviewsArr[i].Date_valid.day <= day)
        {
            cout << "Review for Room: " << reviewsArr[i].Room_number << endl;
            cout << "Time of Review: " << reviewsArr[i].Date_valid.day << "/" << reviewsArr[i].Date_valid.month << "/" << reviewsArr[i].Date_valid.year << " .\n";
            cout << "Review: " << reviewsArr[i].Review_content << endl;
            reviewsArr[i].Seen = true;
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

            if (reviewsArr[i].Review_content != "###")
            {
                cout << "Review for Room: " << reviewsArr[i].Room_number << endl;
                cout << "Time of Review: " << reviewsArr[i].Date_valid.day << "/" << reviewsArr[i].Date_valid.month << "/" << reviewsArr[i].Date_valid.year << " .\n";
                cout << "Review: " << reviewsArr[i].Review_content << endl;
                reviewsArr[i].Seen = true;
            }
            cout<<"\n";
        }
    }
    else if (choice == 2)
    {
        int count = 0;
        for (int i = 0; i < MAXREVIEWS; i++)
        {
            if (reviewsArr[i].Seen == false && reviewsArr[i].Review_content != "###")
            {
                cout << "Review for Room: " << reviewsArr[i].Room_number << endl;
                cout << "Time of Review: " << reviewsArr[i].Date_valid.day << "/" << reviewsArr[i].Date_valid.month << "/" << reviewsArr[i].Date_valid.year << " .\n";
                cout << "Review: " << reviewsArr[i].Review_content << endl;
                reviewsArr[i].Seen = true;
                count++;
            }

            if (count == 0)
            {
                cout << "\n\nNo unseen reviews currently.\n\n";
            }
        }
    }
    else if (choice == 3)
    {
        showLastMonth();
    }

    AdminMenu(resCount, custCount);
}

void Admin_logout(int &resCount, int &custCount)
{
    cout << "Logged out successfully!\n\n";
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
    start(resCount, custCount);
    return false;
}

//----------------------------------------------------------------------------------------------
//----------------------------------- | CUSTOMER FUNCTIONS | -----------------------------------
//----------------------------------------------------------------------------------------------
stRoom ReadReserveRoomInfo(int &resCount, int &custCount);
bool CheckRoomIsBooked(stRoom Room);
bool Ask(string TheAsk);
void ReserveRoom(int &resCount, int &custCount);
void CancelRoomScreen(int &custCount);
stRoom ReadCancelRoomInfo(int &resCount, int &custCount);
void checkAvailability(int &resCount, int &custCount);
void login_or_signup(int &resCount, int &custCount);
void signUp(int &resCount, int &custCount);
void login(int &resCount, int &custCount);
void menu(int &resCount, int &custCount);
void review(int &resCount, int &custCount);
void customerLogOut(int &resCount, int &custCount);
void CancelRoom(int &resCount, int &custCount);

void customerLogOut(int &resCount, int &custCount)
{
    cout << "Logged out successfully.\n\n";
    start(resCount, custCount);
}

stRoom ReadReserveRoomInfo(int &resCount, int &custCount)
{
    cout<<"Enter The Room You want to reserve: \n";
    stRoom Room;
    cin>>Room.roomNumber;

    Check_Choice_Validity(Room.roomNumber, 1, 50);

    cout << "\nPLease Enter Start Date ? (DD/MM/YYYY)?";
    cin >> customersArr[loggedInIndex].StartDate.day >> customersArr[loggedInIndex].StartDate.month >> customersArr[loggedInIndex].StartDate.year;
    cout << "\nPLease Enter End Date ? (DD/MM/YYYY)?";
    cin >> customersArr[loggedInIndex].EndDate.day >> customersArr[loggedInIndex].EndDate.month >> customersArr[loggedInIndex].EndDate.year;
    cout << "\nPlease Enter Credit Card Number ? ";
    cin >> customersArr[loggedInIndex].CreditCardNumber;

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
    Room = ReadReserveRoomInfo(resCount, custCount);

    if (Ask("\n\nAre you sure you want reserve this room ? (y/n)? "))
    {
        if (!CheckRoomIsBooked(Room)) // if booked
            cout << "\nSorry,This Room is already booked.\n";
        else
        {
            for (int i = 0; i < FLOORS; i++)
            {
                for (int j = 0; j < ROOMS; j++)
                {
                    if (roomsArr[i][j].roomNumber == Room.roomNumber)
                    {
                        roomsArr[i][j].isAvailable = false;
                        roomsArr[i][j].RoomID = customersArr[loggedInIndex].CustomerID;

                        // customersArr[resCount].roomNumber = Room.roomNumber;
                        customersArr[loggedInIndex].roomNumber = Room.roomNumber;
                        resCount++;
                    }
                }
            }

            cout << "\n\nDone successfully, The Room has been successfully booked.\n";
        }
    }
    cout << "\n\n\n";
    menu(resCount, custCount);
}

void CancelRoomScreen(int &custCount)
{
    // system("cls");
    cout << "--------------------------------------------------\n";
    cout << "                Cancel Room Screen                \n";
    cout << "--------------------------------------------------\n\n";
}
stRoom ReadCancelRoomInfo(int &resCount, int &custCount)
{
    cout<<"Enter The Room number you want to cancle:\n";
    stRoom Room;
    cin >> Room.roomNumber;

    Check_Choice_Validity(Room.roomNumber, 1, 50);
    Room.RoomID = customersArr[loggedInIndex].CustomerID;
    return Room;
}
bool CheckCustomerIsBookedThisRoomByCustomer(stRoom Room)
{
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
void CancelRoom(int &resCount, int &custCount) // this is the main function
{

    CancelRoomScreen(custCount); // clear screen and show header

    stRoom Room;
    Room = ReadCancelRoomInfo(resCount, custCount);

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

            cout << "\n\nDone successfully, The Room has been successfully Cancelled.\n\n";
        }
        else
            cout << "\nErorr!\n This Room is NOT booked.\n";
    }

    // cout << "\n\n\nPress any key to go Back to main menu...";
    menu(resCount, custCount);
}

void checkAvailability(int &resCount, int &custCount)
{

    int rNum;
    bool found = false;
    cout << "\n-----------------Check Room Availability-----------------\n";
    cout<<"Our Hotel Has a Total Number of 50 Rooms\n";
    cout << "Enter Room Number To Check its Availaility: ";
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

    // if (!found)
    // {
    //     cout << "Room number not found in our system.\n";
    // }
    Check_Choice_Validity(rNum, 1, 50);
    cout << "\n\n";
    menu(resCount, custCount);
}

void login_or_signup(int &resCount, int &custCount)
{
    cout<<"\n-----------------Login/sign up Page-----------------\n";
    int choice;
    cout << "welcome to our hotel \n"
         << "please enter your choice \n";
    cout << "[1] login\n";
    cout << "[2] sign up\n";
    cin >> choice;

    Check_Choice_Validity(choice, 1, 2);

    if (choice == 1)
    {
        login(resCount, custCount);
    }
    else if (choice == 2)
    {
        signUp(resCount, custCount);
    }
    
    
}
void signUp(int &resCount, int &custCount)
{
    cout<<"\n-----------------Sign up Page-----------------\n";
    bool check;
    cout << "Enter your email:";
    cin >> customersArr[custCount].Email;
    cout << "Enter your name:";
    cin.ignore();
    getline(cin >> ws, customersArr[custCount].Name);
    cout << "enter your creidt card number: ";
    cin >> customersArr[custCount].CreditCardNumber;
    do
    {
        check = true;
        cout << "Enter a new username: ";
        cin >> customersArr[custCount].UserName;
        for (int k = 0; k < custCount; k++)
        {
            if (customersArr[custCount].UserName == customersArr[k].UserName)
            {
                cout << "Invalid username \n"
                     << "Please re-enter username \n";
                check = false;
            }
        }

    } while (!check);
    cout << "Enter your password: ";
    cin >> customersArr[custCount].Password;
    cout << "Please enter your id number: ";
    cin >> customersArr[custCount].CustomerID;
    custCount++;
    cout << "Account is activated successfully \n";
    char choice;
    do
    {
        cout << "do you want to log in now?(y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            login(resCount, custCount);
            break;
        }
        else if (choice == 'n' || choice == 'N')
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

    cout << "-----------------To Login Our Website----------------- \n";
    cout << "please enter your username and password \n";

    bool check = false;
    string tempUser, tempPass;
    do
    {
        cout << "username: ";
        cin >> tempUser;
        cout << "password:  ";
        cin >> tempPass;
        for (int j = 0; j < custCount; j++)
        {
            if (tempUser == customersArr[j].UserName && tempPass == customersArr[j].Password)
            {
                cout << "\nLogged In Successfully\n";
                check = true;
                loggedInIndex = j;
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
    cout<<"\n-----------------Menu Page-----------------\n";
    cout << "[1] Check room availability \n";
    cout << "[2] Reserve a room \n";
    cout << "[3] add review \n";
    cout << "[4] Cancel Reservation \n";
    cout << "[5] log out \n";
    int choice;
    cin >> choice;
    // do
    // {
    Check_Choice_Validity(choice, 1, 5);

    switch (choice)
    {
    case 1:
        checkAvailability(resCount, custCount);
        break;
    case 2:
        ReserveRoom(resCount, custCount);
        break;
    case 3:
        review(resCount, custCount);
        break;
    case 4:
        CancelRoom(resCount, custCount);
        break;
    case 5:
        customerLogOut(resCount, custCount);
        break;
    }

    // } while (true);
}
void review(int &resCount, int &custCount)
{
    if (customersArr[loggedInIndex].roomNumber == -1)
    {
        cout << "\n\nYou don't have any reserved rooms to leave a review on.\n\n";
    }
    else
    {
        reviewsArr[counter_of_review_number].Review_id = 1 + counter_of_review_number;
        // cout << "please enter your room number: ";
        // cin >> reviewsArr[counter_of_review_number].Room_number;

        reviewsArr[counter_of_review_number].Room_number = customersArr[loggedInIndex].roomNumber;

        cout << "Please enter the date (dd/MM/yyyy): \n";
        cin >> reviewsArr[counter_of_review_number].Date_valid.day;
        cin >> reviewsArr[counter_of_review_number].Date_valid.month;
        cin >> reviewsArr[counter_of_review_number].Date_valid.year;
        cout << "enter your review: ";
        cin.ignore();
        cin.clear();
        getline(cin, reviewsArr[counter_of_review_number].Review_content);
        counter_of_review_number++;
        cout << "****thank you for your review**** \n";
    }
    menu(resCount, custCount);
}




//----------------------------------------------------------------------------------------------
//------------------------------------- | Frontend | -------------------------------------------
//----------------------------------------------------------------------------------------------
void Check_Choice_Validity(int &choice, int start, int end){
    while (choice < start or choice > end){
        cout << "\nInvalid choice, please Enter a valid Choice from "<<start<<" to "<<end<<":\n";
        cin >> choice;
    }
}

void start(int &resCount, int &custCount)
{
    int accountChoice;
    cout << "\t\t Welcome To Our Hotel Reservation App!\n";
    cout << "\tPlease choose account type\n";
    cout << "[1] Customer\n";
    cout << "[2] Admin\n";
    cout << "[0] Exit\n";
    cin >> accountChoice;

    Check_Choice_Validity(accountChoice, 0, 2);
    
    
    if (accountChoice == 1)
        login_or_signup(resCount, custCount);
        
    else if (accountChoice == 2)
        Admin_login(resCount, custCount);
        
    else if (accountChoice == 0){
        cout << "Goodbye!\n";
        exit(0);
    }
    
}




//----------------------------------------------------------------------------------------------
//----------------------------------- | File Stream | ------------------------------------------
//----------------------------------------------------------------------------------------------
void saveCustomers(Customer customersArr[], int custCount) {
    ofstream outFile("customers.txt"); // Create/overwrite file
    if (outFile.is_open()) {
        for (int i = 0; i <= custCount; i++) {
            outFile << customersArr[i].CustomerID << "\n"
                    << customersArr[i].Name << "\n"
                    << customersArr[i].Email << "\n"
                    << customersArr[i].UserName << "\n"
                    << customersArr[i].Password << "\n"
                    << customersArr[i].CreditCardNumber << "\n";
        }
        outFile.close();
    }
}

void saveAdmins(Admin adminsArr[], int adminCount) {
    ofstream outFile("admins.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < adminCount; i++) {
            // Assuming: username, password, id
            outFile << adminsArr[i].Admin_user_name << "\n"
                    << adminsArr[i].Admin_password << "\n"
                    << adminsArr[i].Admin_id << "\n";
        }
        outFile.close();
    }
}

void saveReviews(Review reviewsArr[], int reviewCount) {
    ofstream outFile("reviews.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < reviewCount; i++) {
            // Assuming: day, month, year, comment, reviewId, roomId
            outFile << reviewsArr[i].Date_valid.day << "\n"
                    << reviewsArr[i].Date_valid.month << "\n"
                    << reviewsArr[i].Date_valid.year << "\n"
                    << reviewsArr[i].Review_content << "\n"
                    << reviewsArr[i].Review_id << "\n"
                    << reviewsArr[i].Room_number << "\n"
                    << reviewsArr[i].Seen << "\n";
        }
        outFile.close();
    }
}

void loadCustomers(Customer customersArr[], int n) {
    ifstream inFile("customers.txt");
    int i = 0;
    if (inFile.is_open()) {
        while (i < n && inFile >> customersArr[i].CustomerID) {
            //inFile.ignore(); // Clear newline after ID
            getline(inFile, customersArr[i].Name);
            getline(inFile, customersArr[i].Email);
            getline(inFile, customersArr[i].UserName);
            getline(inFile, customersArr[i].Password);
            getline(inFile, customersArr[i].CreditCardNumber);
            i++;
        }
        
        inFile.close();
    }
}

void loadAdmins(Admin adminsArr[], int n) {
    ifstream inFile("admins.txt");
    int i = 0;
    if (inFile.is_open()) {
        while (i < n && getline(inFile, adminsArr[i].Admin_user_name)) {
            getline(inFile, adminsArr[i].Admin_password);
            inFile >> adminsArr[i].Admin_id;
            inFile.ignore(); // Clear the newline left by reading the integer
            i++;
        }
       
        inFile.close();
    }
}

void loadReviews(Review reviewsArr[], int n) {
    ifstream inFile("reviews.txt");
    int i = 0;
    if (inFile.is_open()) {
        while (i < n && inFile >> reviewsArr[i].Date_valid.day) {
            inFile >> reviewsArr[i].Date_valid.month;
            inFile >> reviewsArr[i].Date_valid.year;
            inFile.ignore(); // Clear newline before reading the string comment
            
            getline(inFile, reviewsArr[i].Review_content);
            
            inFile >> reviewsArr[i].Review_id;
            inFile >> reviewsArr[i].Room_number;
            inFile >> reviewsArr[i].Seen;
            inFile.ignore(); // Clear newline for the next loop iteration
            i++;
        }
        
        inFile.close();
    }
}
//----------------------------------------------------------------------------------------------
//----------------------------------- | MAIN FUNCTION | ----------------------------------------
//----------------------------------------------------------------------------------------------

int main()
{
    //      Deliverables
    
    // Keep track of how many items are actually in the arrays
    int custCount = *(&custCount + 1) - custCount;
    int adminCount = *(&adminsArr + 1) - adminsArr;
    int reviewCount = *(&reviewsArr + 1) - reviewsArr;
    int resCount = 0;

    // 1. Load all data from files
    loadCustomers(customersArr, custCount);
    loadAdmins(adminsArr, adminCount);
    loadReviews(reviewsArr, reviewCount);

    // 2. Fallback: If files don't exist (e.g., first time running), load hardcoded defaults
    if (custCount == 0 && adminCount == 0) {
        
        //      Pre-defined Admins
        adminsArr[0] = {"yahia", "yahiaadmin123", 1};
        adminsArr[1] = {"omarEmad", "omaremadmin123", 2};
        adminsArr[2] = {"omarOsama", "omarosadmin123", 3};
        adminsArr[3] = {"anas", "anasadmin123", 4};
        adminsArr[4] = {"moaz", "moazadmin123", 5};
        adminsArr[5] = {"m7md", "m7mdadmin123", 6};
    
        adminCount = 6; 
        //      Pre-defined Customers
        customersArr[0] = {"100", "Yahia", "yahiakhaledhelal@gmail.com", "sitos", "yahia123", "1111222233334444"};
        customersArr[1] = {"101", "Mohammed", "Mohammed@gmail.com", "m7md", "m7md123", "4444555566667777"};
        customersArr[2] = {"102", "Omar Osama", "Omar@gmail.com", "omarOS", "omaros123", "7777888899990000"};
        customersArr[3] = {"103", "Anas", "Anas@gmail.com", "drageez", "anas123", "0000111122223333"};
        customersArr[4] = {"104", "Moaz", "Moaz@gmail.com", "moaz", "moaz123", "3333444455556666"};
        customersArr[5] = {"104", "Omar Emad", "Moaz@gmail.com", "omarEM", "omarem123", "6666777788889999"};

        custCount = 6; 

        //      Pre-defined Reviews
        reviewsArr[0] = {2, 2, 2026, "very nice room & service", 1, 1};
        reviewsArr[1] = {14, 2, 2026, "good vacation spot", 2, 2};
        reviewsArr[2] = {27, 1, 2026, "horrible service & staff", 3, 10};
        reviewsArr[3] = {2, 4, 2026, "the rooms were very nice and clean and had a great view!", 4, 19};
        reviewsArr[4] = {13, 1, 2026, "it was okay.", 5, 27};
        reviewsArr[5] = {25, 12, 2025, "the food was great.", 6, 48};
        
        reviewCount = 6; 
    }

    // 3. Room initialization
    for (int i = 0; i < FLOORS; i++)
    {
        for (int j = 0; j < ROOMS; j++)
        {
            roomsArr[i][j].roomNumber = (i + 1) * ROOMS - (ROOMS - (j + 1));
        }
    }
    
    //      Running Sequence
    start(resCount, custCount); 

    // 5. Save all data before the program completely closes
    saveCustomers(customersArr, custCount);
    saveAdmins(adminsArr, adminCount);
    saveReviews(reviewsArr, reviewCount);  
}
