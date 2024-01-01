// Hotel Booking System.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>  
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <regex>

// advanced
// include our custom class
#include "Account.h" 
#include "feedback.h"
#include "menu.h"
#include "Room.h";
#include "reservation.h"
#include "booking.h"
#include "AddRoom.h"
#include "Arrowmenu.h"

using namespace std;


void registerAccount(); //register user
void loginMenu(); // login menu

//admin
void homeAdmin(Account user);
Feedback feedbackAdmin(Account user, Feedback view);
void bookingAdmin(Account user);
void roomsAdmin(Account user);
void addRoomTypeAdmin(Account user);
void addRoomAdmin(Account user);
roomVariety viewRoomAdmin(Account user, roomVariety newBedroom);
void searchRoomAdmin(Account user);

//user
void addFeedBack(Account user);
void homeUser(Account user);
Booking bookingUser(Account user, Booking view);
Bedroom roomsUser(Account user, Reservation trolley);
Reservation roomsUser2(Account user, int roomID, Reservation trolley);
void feedbackUser(Account user);
Account profile(Account user);
Feedback viewFeedback(Account user,  Feedback view);
Reservation roomType(Account user, int rType, Reservation trolley);
Reservation roomDetails(Account user, int roomID, Reservation trolley);
Reservation trolleyMenu(Account user, Reservation trolley);


int productCategorySelection();


//utility functions
bool isNumeric(string input);

// extras
bool toInteger(string* input, int* valueholder);

bool isValidDate(const std::string& dateStr);
 
string hiddenInput(string = "");
string valIC(string="");
string hideString(string);
string hideString(int);

int main() {  
	   
	ArrowMenu mainmenu;
	mainmenu.header = "Welcome to Hotel WMA";
	mainmenu.addOption("Register");
	mainmenu.addOption("Login"); 

	while (1) {
		switch (mainmenu.prompt())
		{
		case -1: // prompt returns -1 when esc is pressed
			return 0;
			break;
		case 0:
			registerAccount();
			break;
		case 1:
			loginMenu();
			break;  
		
		}
	} 
} 

void registerAccount() {
	Account newacc;

	newacc.setUsertype("user");

	ArrowMenu rgMenu;
	rgMenu.header = "Registration";
	rgMenu.addOption("Name");
	rgMenu.addOption("Number IC");
	rgMenu.addOption("Phone Number ");
	rgMenu.addOption("Email");
	rgMenu.addOption("Address");
	rgMenu.addOption("Username");
	rgMenu.addOption("Password");
	rgMenu.addOption("Password Visibility");
	rgMenu.addOption("Register");


	string tmpinput;
	string tmpinputP;
	bool valid = true;
	bool showPassword = false;
	int option = 0;
	string tmpPassword = "";// we use temporary string for password since we will only encrypt when finishing process
	string inputIC = "";
	while (1) {
		if (showPassword) {

			rgMenu.setValue(7, "SHOW");
			rgMenu.setValue(6, tmpPassword);
		}
		else {
			rgMenu.setValue(7, "HIDE");
			rgMenu.setValue(6, hideString(tmpPassword));
		}
		option = rgMenu.prompt(option);
		switch (option) {
		case -1:
			return;

		case 0:
			cout << "Insert Name:";
			getline(cin, newacc.name);
			rgMenu.setValue(0, newacc.name);
			break;
		case 1:
			cout << "Insert Number IC (991012110212):";
			cin >> newacc.numIc;
			if (newacc.numIc.length() > 12 || newacc.numIc.length() < 12) {
				cout << "Number IC must be 12 character";
				_getch();
			}
			else {
				rgMenu.setValue(1, newacc.numIc);;
			}
			break;
		case 2:
			cout << "Insert Phone Number (0131234560):";
			cin >> newacc.phoneNum;
			if (newacc.phoneNum.length() > 11 || newacc.phoneNum.length() < 10) {
				cout << "Phone Number must be at least 10 or 11 number";
				_getch();
			}
			else {
				rgMenu.setValue(2, newacc.phoneNum);;
			}
			break;
		case 3:
			cout << "Insert email (utem@gmail.com):";
			getline(cin,newacc.email);
			rgMenu.setValue(3, newacc.email);
			break;
		case 4:
			cout << "Insert Address:";
			getline(cin,newacc.address);
			rgMenu.setValue(4, newacc.address);
			break;
		case 5:
			cout << "Insert Username:";
			cin >> newacc.username;
			rgMenu.setValue(5, newacc.username);
			break;
		case 6:
			cout << "Insert password:";
			tmpinput = hiddenInput(tmpinput);
			if (tmpinput.length() < 6) {
				cout << "Password must be at least 6 character long";
				_getch();
			}
			else {
				tmpPassword = tmpinput;
			}
			break;
		case 7:
			showPassword = !showPassword;
			break;
		case 8:
			valid = true;

			if (valid) {

				newacc.setPassword(tmpPassword); // now only we set the temporary string into password to be encrypted
				newacc.insert();
				cout << "Registered";
				_getch();
				return;
			}
			else {
				cout << "Please re-check your informations";
				_getch();
			}
			break;
		}
	}
}
void loginMenu() {
	ArrowMenu loginMenu;
	loginMenu.header = "LOGIN";
	loginMenu.addOption("username");
	loginMenu.addOption("password");
	loginMenu.addOption("Login"); 

	Account user;
	int option = 0;
	string tmpinput = "";
	string tmpPassword = "";// we use temporary string for password since we will only encrypt when finishing process
	while(1) {
		option = loginMenu.prompt(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "Insert Username:";
			cin >> user.username;
			loginMenu.setValue(0, user.username);
			break;
		case 1:
			cout << "Insert Password:";
			tmpPassword = hiddenInput(tmpPassword);
			loginMenu.setValue(1,hideString(tmpPassword));
			break;
		case 2:
			user.setPassword(tmpPassword);
			if (user.login()) {

				if (user.getRole() == "admin")
				{
					homeAdmin(user);
				}
				else if(user.getRole() == "user") {
					homeUser(user);
				}
			
				else {
					cout << "Unknown role for user.";
					_getch();
			}
			}
			else {
				cout << "Invalid Login";
				_getch();
			}
			break;
		}
	}
}
void homeUser(Account user) {

	Booking vBack;
	Bedroom vRoom;
	Reservation vRoom2;

	Menu homeMenus;
	ArrowMenu homeMenu;
	homeMenu.addOption("Profile");
	homeMenu.addOption("Room");
	homeMenu.addOption("Reservation");
	homeMenu.addOption("Feedback");
	//homeMenu.addOption("Logout");
	while (1) {
		homeMenu.header = "Welcome " + user.name;
		switch (homeMenu.prompt())
		{
		case -1:
			return;
			break;
		case 0:
			user = profile(user);
			break;
		case 1:
			vRoom = roomsUser(user, vRoom2);
			break;
		case 2:
			vBack = bookingUser(user, vBack);
			break;
		case 3:
			feedbackUser(user);
			break;
		}
	}
}

Feedback viewFeedback(Account user, Feedback view){
	Feedback pengguna;
	pengguna.user = user.userId;

	vector<Feedback> displayFeedback;
	displayFeedback = Feedback::findFeedback(pengguna.user);
	ArrowMenu cartM;
	cartM.addOption("Back");
	stringstream tmpString;

	tmpString << fixed << setprecision(2) << setw(5) << "ID" << "|" << setw(40) << "Messages"
		<< "|" << setw(20) << "Date & Time" << endl;

	for (int i = 0; i < displayFeedback.size(); i++) {
		tmpString << setw(5) << displayFeedback[i].feedBackId << "|" << setw(40) << displayFeedback[i].messages
			<< "|" << setw(10) << displayFeedback[i].date << endl;
	}
	cartM.header = "Your Feedback " +user.name +"\n" + tmpString.str() ;

	int option = 0;
	while (1) {
		
		option = cartM.prompt(option);
		switch (option)
		{
		case 0:
			return view ;
			break;
		}
	}
}

Account profile(Account user) {

	Account temp = user; // copy the object

	ArrowMenu profileMenu;
	profileMenu.header = "Your profile";
	profileMenu.addOption("Name");
	profileMenu.addOption("Number IC");
	profileMenu.addOption("Phone Number ");
	profileMenu.addOption("Email");
	profileMenu.addOption("Address");
	profileMenu.addOption("Username");
	profileMenu.addOption("Password");
	profileMenu.addOption("Reset");
	profileMenu.addOption("Save");
	profileMenu.addOption("Back");
	profileMenu.addOption("Delete Account");

	string tmpInput;
	int option = 0;
	while (1) {
		profileMenu.setValue(0, temp.name);
		profileMenu.setValue(1, temp.numIc);
		profileMenu.setValue(2, temp.phoneNum);
		profileMenu.setValue(3, temp.email);
		profileMenu.setValue(4, temp.address);
		profileMenu.setValue(5, temp.username);
		profileMenu.setValue(6, hideString(temp.getPassword()));

		option = profileMenu.prompt(option);
		switch (option)
		{
		case -1:
			return user;
			break;
		case 0:
			cout << "Insert Name:";
			getline(cin,temp.name);
			break;
		case 1:
			cout << "Insert Number IC (991012110212):";
			cin >> temp.numIc;
			if (temp.numIc.length() == 12) {
				profileMenu.setValue(1, temp.numIc);
			}
			else {
				temp.numIc.length() > 12 || temp.numIc.length() < 12;
				cout << "Number IC must be 12 character";
				_getch();
			}
			break;
		case 2:
			cout << "Insert Phone Number (0131234560):";
			cin >> temp.phoneNum;
			if (temp.phoneNum.length() > 11 || temp.phoneNum.length() < 10) {
				cout << "Phone Number must be at least 10 or 11 number";
				_getch;
			}
			else {
				profileMenu.setValue(2, temp.phoneNum);
			}
			break;
		case 3:
			cout << "Insert email (utem@gmail.com):";
			getline(cin,temp.email);
			break;
		case 4:
			cout << "Insert Address:";
			getline(cin,temp.address);
			break;
		case 5:
			cout << "Insert Username:";
			cin >> temp.username;
			//profileMenu.setValue(5, temp.username);
			break;
		case 6:
			cout << "Insert current Password:";
			tmpInput = hiddenInput();
			if (user.MatchPasswordWith(tmpInput)) {
				cout << endl;
				cout << "Insert new Password:";
				tmpInput = hiddenInput();
				if (tmpInput.length() < 6) {
					cout << "Password must be at least 6 character long";
				}
				else {
					temp.setPassword(tmpInput);
				}
			}
			else {
				cout << "Invalid current password";
				_getch();
			}
			break;
		case 7:
			temp = user;
			break;
		case 8:
			user = temp;
			user.update();
			cout << "Updated";
			_getch();
			return user;
			break;
		case 9:
			return user;
			break;
		case 10:
			cout << "Delete your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				user = temp;
				user.remove();
				main();
			}
			break;
		}
	}
}

Bedroom roomsUser(Account user, Reservation trolley) {

	vector<Bedroom> rumah;

	ArrowMenu roomMenu;
	roomMenu.footer = "WMA HOTEL";
	roomMenu.bullet = "";
	roomMenu.header = "Please Select Room Type " + user.name;
	
	ArrowMenu productSelect;
	productSelect.bullet = ""; //we dont want bullet here
	
	int selectedProduct = 0;
	rumah = Bedroom::findBedroom();
	roomMenu.clearOption();
	stringstream tmpString;
	tmpString << fixed << setprecision(2) << setw(5) << "ID" << "|" << setw(10) << "Type" << "|"
		<< setw(10) << "Description"
		<< "|" << setw(5) << "Capacity" << "|" << endl;

	roomMenu.header = tmpString.str();
	tmpString.str("");
	for (int i = 0; i < rumah.size(); i++) {
		tmpString << fixed << setw(10) << rumah[i].roomtypeID << "|" 
			<< setw(10) << rumah[i].type << "|" << setw(20) << rumah[i].description
			<< "|" << setw(5) << rumah[i].capacity << "|" << endl;
		roomMenu.addOption(tmpString.str());
		tmpString.str("");

	}
	
	while (1) {
		
		selectedProduct = roomMenu.prompt(selectedProduct);
		if (selectedProduct != -1) { // if not escape pressed process it
			trolley = roomDetails(user, rumah[selectedProduct].roomtypeID, trolley);
		}
		else {
			return 0;
			break;
		}
	}
	return 0;
}


Reservation roomType(Account user, int rType, Reservation trolley) {
	vector<roomVariety> roomType;
	string displayString = "";

	string keyWord = "", sortColumn = "price";
	bool ascending = true;
	double minPrice = 0, maxPrice = 999999;


	ArrowMenu roomMenu;
	roomMenu.header = "Search Option";
	roomMenu.addOption("Key Word");
	roomMenu.addOption("Minimum Price");
	roomMenu.addOption("Maximum Price");
	roomMenu.addOption("Sort By");
	roomMenu.addOption("Ordering");
	roomMenu.addOption("Search");

	Menu sortingRoomMenu;
	sortingRoomMenu.header = "Select Sort category";
	sortingRoomMenu.addOption("Price");
	sortingRoomMenu.addOption("Name");

	ArrowMenu roomSelect;
	roomSelect.bullet = ""; //we dont want bullet here
	roomSelect.header = "Search Result:";
	int selectedRoom = 0;

	while (1)
	{
		roomMenu.setValue(3, sortColumn);
		if (ascending) {
			roomMenu.setValue(4, "Ascending");
		}
		else {
			roomMenu.setValue(4, "Descending");
		}


		switch (roomMenu.prompt()) {

		case -1:
			return trolley;
			break;
		case 0:
			cout << "Insert Key Word: ";
			getline(cin, keyWord);
			roomMenu.setValue(0, keyWord);
			break;
		case 1:
			cout << "Insert Min Price: ";
			cin >> minPrice;
			roomMenu.setValue(1, to_string(minPrice));
			break;
		case 2:
			cout << "Insert Max Price: ";
			cin >> maxPrice;
			roomMenu.setValue(2, to_string(maxPrice));
			break;
		case 3:
			switch (roomMenu.prompt())
			{
			case 1:
				sortColumn = "price";
				break;
			case 2:
				sortColumn = "name";
				break;
			}
			break;
		case 4:
			ascending = !ascending;
			break;
		case 5:

			roomType = roomVariety::findRoom(rType, keyWord, minPrice, maxPrice, sortColumn, ascending);
			roomSelect.clearOption();
			stringstream tmpString;
			tmpString << fixed << setprecision(2) << setw(5) << "ID" << "|" << setw(20) << "Name"
				<< "|" << setw(10) << "Price" << "|" << setw(20) << "Description" << "|" << endl;

			roomSelect.header = tmpString.str();
			tmpString.str("");
			for (int i = 0; i < roomType.size(); i++) {
				tmpString << setw(5) << roomType[i].roomID << "|" << setw(20) << roomType[i].name
					<< "|" << setw(10) << roomType[i].price << "|" << setw(20) << roomType[i].availability << "|" << endl;
				roomSelect.addOption(tmpString.str());
				tmpString.str("");

			}
			selectedRoom = 0;
			while (1) {
				selectedRoom = roomSelect.prompt(selectedRoom);
				if (selectedRoom != -1) { // if not escape pressed process it
					trolley = roomDetails(user, roomType[selectedRoom].roomID, trolley);
				}
				else {
					break;
				}
			}
			break;
		}
	};

}

Reservation roomDetails(Account user, int roomID, Reservation trolley)
{
	roomVariety rooms = roomVariety::findRoom(roomID);
	if (rooms.roomID == 0) {
		// default id, which mean product doesn't exist since no 0 id in database
		cout << "Product not found";
		_getch();
		return trolley;
	}

	ArrowMenu productMenu;
	productMenu.addOption("Add Quantity");
	productMenu.addOption("Add Pax");
	productMenu.addOption("Check-in Date");
	productMenu.addOption("Add to cart");
	productMenu.header = "Product Details:\n"
		"\nName\t: " + rooms.name
		+ "\nAvailable\t: " + rooms.availability
		+ "\nPrice\t: " + to_string(rooms.price);
	while (1) {
		switch (productMenu.prompt())
		{
			case -1:
				return trolley;
				break;
			case 0:
				cout << "Insert Quantity :";
				int qty;
				cin >> qty;
				if (qty > 0) {
					trolley.addRoom(rooms, qty);
				}
				_getch();
				break;
			/*case 1:
				cout << "Insert Pax :";
				int pax;
				cin >> pax;
				if (pax > 0) {
					trolley.addPax(rooms, pax);
				}
				_getch();
				break;*/
			/*case 2:
				cout << "Insert Check-in Date (DD/MM/YYYY): ";
				std::string checkInDate;
				cin >> checkInDate;

				if (!isValidDate(checkInDate))
				{
				cout << "Invalid date format. Please use DD/MM/YYYY format." << endl;
				_getch();
				}
				else
				{
					trolley.addRoom(rooms, checkInDate);
				}
				break;
				*/
			case 3:
				cout << endl << "Product Added into cart";
				_getch();
				break;
		}
	}
}

Reservation trolleyMenu(Account user, Reservation trolley) {
	ArrowMenu trolleyM;
	trolleyM.addOption("Checkout");
	trolleyM.addOption("Empty Cart");
	stringstream ss;
	ss << fixed << setprecision(2) << setw(20) << "Product|" << setw(20) << "Price|" << setw(20)
		<< "Quantity|" << setw(20) << "Subtotal|" << endl;
	for (int i = 0; i < trolley.items.size(); i++) {
		ss << setw(20) << trolley.items[i].first.name << setw(20) << trolley.items[i].first.price << setw(20)
			<< trolley.items[i].second << setw(20) << (trolley.items[i].first.price * trolley.items[i].second) << endl;
	}
	ss << setw(20) << "SUM" << setw(20) << "" << setw(20) << trolley.count() << setw(20) << trolley.total();
	trolleyM.header = "Trolley Items\n" + ss.str();
	char confirm;
	while (1)
	{
		switch (trolleyM.prompt())
		{
		case -1:
			return trolley;
			break;
		case 0:
			cout << "Check out? (y/n)";
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				trolley.insert();
				cout << "Booking Confirm";
				_getch();
				roomVariety(user); // go back to shop with empty cart
			}
			break;
		case 1:
			cout << "Clear your cart? (y/n)";
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				roomVariety(user); // go back to shop with empty cart
			}
			break;
		case 3:
			return trolley;
		}

	}
}

void feedbackUser(Account user)
{
	Feedback fBack;
	fBack.user = user.userId; //put currently logged in user id into the feedback

	Menu feedBack;
	ArrowMenu feedM;
	feedM.header = "Please Select ";
	feedM.addOption("Add Feedback");
	feedM.addOption("View Feedback");
	feedM.addOption("Back");

	while (1)
	{
		feedM.header = "WMA Hotel Feedback , " + user.name;
		switch (feedM.prompt())
		{
		case -1:
			return;
			break;
		case 0:
			addFeedBack(user);
			break;
		case 1:
			fBack = viewFeedback(user, fBack);
			break;
		case 2:
			return;
			break;
		}
	}
}

void addFeedBack(Account user) {

	Feedback newFeed;
	newFeed.user = user.userId; //get current userId to insert to feedback table.

	ArrowMenu feedM;
	feedM.header = "Feedback Menu , " + user.name;
	feedM.addOption("Messages ");
	feedM.addOption("Submit");

	int option = 0;
	while (1) {

		option = feedM.prompt(option);
		switch (option) {
		case -1:
			return;
			break;
		case 0:
			cout << "Insert Messages ";
			getline(cin, newFeed.messages);
			while (newFeed.messages.empty()) {
				cout << "Messages cannot be empty. Please enter feedback messages: ";
				getline(cin, newFeed.messages);
			}
			feedM.setValue(0, newFeed.messages);
			break;
		case 1:
			newFeed.insert();
			cout << "Submit";
			_getch();
			return;
			break;

		}
	}
}

Booking bookingUser(Account user, Booking view) {

	Booking pengguna;
	pengguna.user = user.userId;

	vector<Booking> displayBooking;
	displayBooking = Booking::findBooking(pengguna.user);
	ArrowMenu cartM;
	cartM.addOption("Back");
	stringstream tmpString;

	tmpString << fixed << setprecision(2) << setw(5) << "BID" << "|" << setw(5) << "Room Name"
		<< "|" << setw(5) << "Quantity"<< "|" << setw(5) << "Pax" << "|" 
		<< setw(15) << "Check In Date" << "|" << setw(15) << "Check Out Date" << "|" 
		<< setw(10) << "Price" << "|" << endl;

	for (int i = 0; i < displayBooking.size(); i++) {
		tmpString << setw(5) << displayBooking[i].reservationID << "|" << setw(5) << displayBooking[i].roomName << "|"
			<< setw(5) << displayBooking[i].quantity<< "|" << setw(5) << displayBooking[i].pax << "|" 
			<< setw(15) << displayBooking[i].checkInDate << "|" 
			<< setw(15) << displayBooking[i].checkOutDate << "|" 
			<< setw(10) << displayBooking[i].price << "|" << endl;
	}
	cartM.header = "Your Booking " + user.name + "\n" + tmpString.str();

	int option = 0;
	while (1) {

		option = cartM.prompt(option);
		switch (option)
		{
		case 0:
			return view;
			break;
		}
	}

}

int productCategorySelection() {
	Menu categoryMnu;
	categoryMnu.header = "TOGGLE CATEGORY";
	categoryMnu.addOption("Master Bedroom");
	categoryMnu.addOption("Queen Bedroom");
	categoryMnu.addOption("SIngle Bedroom");
	while (1)
	{
		//since the selected option starts from 1
		// and our category id also is 1:apparel, 2:Food, 3:Furniture
		// we can just use the value of the prompt
		// if your database id and the prompt result does not match you might need to modify the return value first
		return categoryMnu.prompt();

	}
}

//admin
void homeAdmin(Account user) {

	Feedback fBack;

	Menu homeMenus;
	ArrowMenu homeMenu;
	homeMenu.addOption("Profile");
	homeMenu.addOption("Room");
	homeMenu.addOption("Reservation");
	homeMenu.addOption("Feedback");
	//homeMenu.addOption("Logout");
	while (1) {
		homeMenu.header = "Welcome " + user.name;
		switch (homeMenu.prompt())
		{
		case -1:
			return;
			break;
		case 0:
			user = profile(user);
			break;
		case 1:
			roomsAdmin(user);
			break;
		case 2:
			bookingAdmin(user);
			break;
		case 3:
			fBack = feedbackAdmin(user, fBack);
			break;
		}
	}
}

Feedback feedbackAdmin(Account user, Feedback view) {
	
	Feedback pengguna;

	vector<Feedback> displayFeedback;
	displayFeedback = Feedback::findFeedbackAdmin();
	ArrowMenu cartM;
	cartM.addOption("Back");
	stringstream tmpString;

	tmpString << fixed << setprecision(2) << setw(5) << "FID" << "|" << setw(5) << "CID" 
		<< "|" << setw(40) << "Messages"
		<< "|" << setw(20) << "Date & Time" << "|" << endl;

	for (int i = 0; i < displayFeedback.size(); i++) {
		tmpString << setw(5) << displayFeedback[i].feedBackId << "|" << setw(5) << displayFeedback[i].user << "|"
			<< setw(40) << displayFeedback[i].messages
			<< "|" << setw(20) << displayFeedback[i].date << "|" << endl;
	}
	cartM.header = "Your Feedback " + user.name + "\n" + tmpString.str();

	int option = 0;
	while (1) {

		option = cartM.prompt(option);
		switch (option)
		{
		case 0:
			return view;
			break;
		}
	}
}

void bookingAdmin(Account user) {

}

void roomsAdmin(Account user) {
	roomVariety newBedroom;

	ArrowMenu bedroomM;
	bedroomM.header = "Please Select One";
	bedroomM.addOption("Add Room Type ");
	bedroomM.addOption("Add Room ");
	bedroomM.addOption("View Room ");
	bedroomM.addOption("Search Room");


	while (1)
	{
		switch (bedroomM.prompt()) {

		case -1:
			return;
			break;
		case 0:
			addRoomTypeAdmin(user);
			break;
		case 1:
			addRoomAdmin(user);
			break;
		case 2:
			newBedroom = viewRoomAdmin(user, newBedroom);
			break;
		/*case 3:
			searchRoom(user);
			break:*/
		}
	}
}


//not yet done//
roomVariety viewRoomAdmin(Account user, roomVariety newBedroom){

	roomVariety newRoom;
	vector<roomVariety> dispRoom;
	dispRoom = roomVariety::findRooms();

	ArrowMenu roomMenu;
	roomMenu.addOption("Back ");

	//Display
	stringstream tmpAdmin;
	roomMenu.display();
	tmpAdmin << fixed << setprecision(2) << setw(5) << "RoomID" << "|" << setw(10) << "Room Type"
		<< "|" << setw(20) << "name" << "|" << setw(20) << "Availability" 
		<< "|" << setw(20) << "Price" << endl;

	for (int i = 0; i < dispRoom.size(); i++) {
		tmpAdmin << setw(5) << dispRoom[i].roomID << "|" << setw(10)
			<< dispRoom[i].rType << "|" << setw(20)
			<< dispRoom[i].name << "|" << setw(20)
			<< dispRoom[i].availability
			<< "|" << setw(20) << dispRoom[i].price << endl;
	}
	roomMenu.header = "List of Room at WMA Hotel "  "\n" + tmpAdmin.str();
	//cartM.header = "Your Feedback " + user.name + "\n" + tmpString.str();

	int option = 0;
	while (1) {

		option = roomMenu.prompt(option);
		switch (option) {
		
		case 0:
			return newRoom;
			break;
		}
	}
}

void addRoomTypeAdmin(Account user)
{
	Bedroom newRoomType;

	ArrowMenu roomAdd;
	roomAdd.header = "Welcome to WMA Hotel , " + user.name;
	roomAdd.addOption("Insert Room Type ");
	roomAdd.addOption("Insert Room Capacity ");
	roomAdd.addOption("Insert Room Description ");
	roomAdd.addOption("Submit");

	int option = 0;
	while (1) {

		option = roomAdd.prompt(option);
		switch (option) {
		case -1:
			return;
			break;
		case 0:
			cout << "Insert Room Type :";
			cin.ignore();
			getline(cin, newRoomType.type);
			roomAdd.setValue(0, newRoomType.type);
			break;
		case 1:
			cout << "Insert Room Capacity :";
			cin.ignore();
			cin >> newRoomType.capacity;
			roomAdd.setValue(1, std::to_string(newRoomType.capacity));
			break;
		case 2:
			cout << "Insert Room Description :";
			cin.ignore();
			getline(cin, newRoomType.description);
			roomAdd.setValue(2, newRoomType.description);
			break;
		case 3:
			newRoomType.insertRT();
			cout << "Submit";
			_getch();
			return;
			break;

		}
	}
}

void addRoomAdmin(Account user)
{
	roomVariety nRoom;
	Bedroom newRoom;
	vector<Bedroom> displayRoom;
	displayRoom = Bedroom::findBedroom();



	ArrowMenu roomMenu;

	roomMenu.addOption("Enter Room Type ID ");
	roomMenu.addOption("Enter Room Name ");
	roomMenu.addOption("Enter Room Price ");
	roomMenu.addOption("Enter Availability ");
	roomMenu.addOption("Submit ");


	//Display room type Menu
	stringstream tmpAdmin;
	roomMenu.display();
	tmpAdmin << fixed << setprecision(2) << setw(5) << "ID" << "|" << setw(20) << "Type"
		<< "|" << setw(20) << "Capacity" << "|" << setw(20) << "Description" << endl;

	for (int i = 0; i < displayRoom.size(); i++) {
		tmpAdmin << setw(5) << displayRoom[i].roomtypeID << "|" << setw(20)
			<< displayRoom[i].type << "|" << setw(20)
			<< displayRoom[i].capacity << "|" << setw(20) << displayRoom[i].description << endl;
	}
	roomMenu.header = "Please Select ID based on the table"  "\n" + tmpAdmin.str();
	//cartM.header = "Your Feedback " + user.name + "\n" + tmpString.str();

	int option = 0;
	while (1) {

		option = roomMenu.prompt(option);
		switch (option) {
		case -1:
			return;
			break;
		case 0:
			cout << "Insert Room Type ID: ";
			cin >> nRoom.rType;
			roomMenu.setValue(0, std::to_string(nRoom.rType));
			break;
		case 1:
			cout << "Insert Room Name: ";
			cin.ignore(); // Add this line to consume the newline character
			getline(cin, nRoom.name);
			roomMenu.setValue(1, nRoom.name);
			break;
		case 2:
			cout << "Insert Room Price: ";
			cin.ignore();
			cin >> nRoom.price;
			roomMenu.setValue(2, std::to_string(nRoom.price));
			break;
		case 3:
			cout << "Insert Room Availability (YES OR NO): ";
			cin.ignore();
			getline(cin, nRoom.availability);
			roomMenu.setValue(3, nRoom.availability);
			break;
		case 4:
			nRoom.insertR();
			cout << "Submit";
			_getch();
			return;
			break;

		}
	}
}



bool isValidDate(const std::string& dateStr)
{
	std::regex dateRegex
	("^[0,1]?\\d{1}/(([0-2]?\\d{1})|([3][0,1]{1}))/(([1]{1}[9]{1}\\d{1})|([2-9]{1}\\d{3}))$");
	return std::regex_match(dateStr, dateRegex);
}

bool isNumeric(string input) {
	for (int i = 0; i < input.length(); i++) {
		// loop through the string and if the character at index is not digit return false
		if (!isdigit(input.at(i))) {
			return false;
		}
	}
	// if loop finishes means all is digit so return true
	return true;
}


// extra example validating using try catch with pointers
bool toInteger(string * input, int * valueholder) {
	// our parameter here is pointer instead of value,
	// which mean anychanges done to this pointer will applies to whatever variable address we pass into it
	// so when we store stoi result to valueholder pointer we are storing the value into the memory address of variable passed into this function

	try
	{
		*valueholder = stoi(*input); //if the string fails to be converted into integer it will throw error otherwise converted integer is stored into valueholder

		return true;// return true after successful conversion from string to int stored into valuholder
	}
	catch (exception ex) {
		return false; // catch error and return false, error means string failed to be converted to integer
	}
}

bool toDecimal(string* input, double* value) {
	try {
		*value = stod(*input);
		return true;
	}
	catch(exception ex){
		return false;
	}
}



string hiddenInput(string prevValue) {
	string input = "";
	char tmp = '\0';
	while (1) {
		tmp = _getch();
		switch (tmp)
		{ 
		case 13:// ASCII code for enter key
			return input;
			break;
		case 27://ASCII code for escape key
			return prevValue; //return the previous value insteadd to cancel
			break;
		case 8:
			if (input.length() > 0) {
				input.erase(input.size() - 1); // erase last index
				cout << "\b \b";
				//print  this which will move back caret and replace character with space and move back caret 1 more time to imitate backspace
			}
			break;
		default://for any other key press
			if (tmp >= 32 && tmp <= 126) {
				/// 32 until 126 is basically all the printable character in ASCII table,
				// modify this range if you want to limit input, 
				// for example 48~57 will only allow number input, 65~90 only uppercase, 97 ~122 only lowercase etc 
				//when key press is within our acceptable range append the character into string
				input += tmp;
				//display a * instead
				cout << "*";
			}
			//if the key press is outside of our allowed range simply skips it to ignore
			break;
		}
	}
}

// simple hiding string by replacing all character with a specific character *
string hideString(string tohide) {
	string hidden = "";
	for (int i = 0; i < tohide.size(); i++) {
		hidden += '*';
	}
	return hidden;
}

// simple hiding string by replacing all character with a specific character *
string hideString(int tohideLenght) {
	string hidden = "";
	for (int i = 0; i <tohideLenght; i++) {
		hidden += '*';
	}
	return hidden;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
