#include <iostream>

using namespace std;

struct stDate
{
	int Day, Month, Year;

};
struct stRoomNumber
{
	int FloorNumber, FlatNumber;
};
struct stRoom
{
	stRoomNumber RoomNumber;
	string RoomID;  // is Equal to CustomerID
	bool BookingStatus = false;
	stDate StartDate;
	stDate EndDate;
};
struct stCustomer
{
	string CustomerID;
	string Name;
	string Email;
	string UserName;
	string Password;
	string CreditCardNumber;
};

stRoom GlobalRooms[5][10];  // should download from file
stCustomer GlobalCustomer = { "1234","Mohamed","","","","123456789" }; //should Equal to customer that will login

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
stRoom ReadReserveRoomInfo()
{
	stRoom  Room;

	Room.RoomNumber.FloorNumber = ReadNumInRange("Please Enter Floor Number ? ", 1, 5);
	Room.RoomNumber.FlatNumber = ReadNumInRange("\nPlease Enter Flat Number ? ", 1, 10);

	cout << "\nPLease Enter Start Date ? (DD/MM/YYYY)?";
	cin >> Room.StartDate.Day >> Room.StartDate.Month >> Room.StartDate.Year;
	cout << "\nPLease Enter End Date ? (DD/MM/YYYY)?";
	cin >> Room.EndDate.Day >> Room.EndDate.Month >> Room.EndDate.Year;
	cout << "\nPlease Enter Credit Card Number ? ";
	cin >> GlobalCustomer.CreditCardNumber;

	return  Room;
}
bool CheckRoomIsBooked(stRoom Room)
{
	return (GlobalRooms[Room.RoomNumber.FloorNumber - 1][Room.RoomNumber.FlatNumber - 1].BookingStatus);  //if room status = true will return true otherwise false
}
void ReserveRoomScreen()
{
	system("cls");
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
void ReserveRoom()      // this is the main function
{

	ReserveRoomScreen(); // clear screen and show header
	stRoom Room;
	Room = ReadReserveRoomInfo();

	if (Ask("\n\nAre you sure you want reserve this room ? (y/n)? "))
	{
		if (CheckRoomIsBooked(Room))         //if booked
			cout << "\nSorry,This Room is already booked.\n";
		else
		{
			GlobalRooms[Room.RoomNumber.FloorNumber - 1][Room.RoomNumber.FlatNumber - 1].BookingStatus = true;
			GlobalRooms[Room.RoomNumber.FloorNumber - 1][Room.RoomNumber.FlatNumber - 1].RoomID = GlobalCustomer.CustomerID;
			cout << "\n\nDone successfully, The Room has been successfully booked.\n";
		}
	}
	cout << "\n\n\nPress any key to go Back to main menu...";
	system("pause>0");
}
void CansleRoomScreen()
{
	system("cls");
	cout << "--------------------------------------------------\n";
	cout << "                Cansle Room Screen                \n";
	cout << "--------------------------------------------------\n\n";
}
stRoom ReadCansleRoomInfo()
{
	stRoom Room;

	Room.RoomNumber.FloorNumber = ReadNumInRange("Please Enter Floor Number ? ", 1, 5);
	Room.RoomNumber.FlatNumber = ReadNumInRange("\nPlease Enter Flat Number ? ", 1, 10);
	Room.RoomID = GlobalCustomer.CustomerID;
	return  Room;
}
bool CheckCustomerIsBookedThisRoomByCustomer(stRoom Room)
{
	return (Room.RoomID == GlobalRooms[Room.RoomNumber.FloorNumber - 1][Room.RoomNumber.FlatNumber - 1].RoomID
		&& GlobalRooms[Room.RoomNumber.FloorNumber - 1][Room.RoomNumber.FlatNumber - 1].BookingStatus);

}
void CansleRoom()  // this is the main function
{

	CansleRoomScreen(); // clear screen and show header

	stRoom Room;
	Room = ReadCansleRoomInfo();

	if (Ask("\n\nAre you sure you want Cansle this room ? (y/n)? "))
	{
		if (CheckCustomerIsBookedThisRoomByCustomer(Room)) // if was booked
		{
			GlobalRooms[Room.RoomNumber.FloorNumber - 1][Room.RoomNumber.FlatNumber - 1].BookingStatus = false;
			GlobalRooms[Room.RoomNumber.FloorNumber - 1][Room.RoomNumber.FlatNumber - 1].RoomID = "";

			cout << "\n\nDone successfully, The Room has been successfully Cansled.\n";
		}
		else
			cout << "\nErorr!\n This Room is NOT booked.\n";
	}

	cout << "\n\n\nPress any key to go Back to main menu...";
	system("pause>0");
}

