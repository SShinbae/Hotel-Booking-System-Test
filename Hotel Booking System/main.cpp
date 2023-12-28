// Hotel Booking System.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>  
#include <conio.h>
#include <iomanip>
#include <sstream>

// advanced
// include our custom class
#include "Account.h" 
#include "feedback.h"
#include "menu.h"
#include "Room.h";
#include "reservation.h"
#include "booking.h"
#include "Arrowmenu.h"

using namespace std;


void registerAccount();
void loginMenu();
void addFeedBack(Account user);


void home(Account user);
Account profile(Account user);
Feedback viewFeedback(Account user,  Feedback view);
void rooms(Account user);
void feedback(Account user);
Reservation roomType(Account user, int rType, Reservation trolley);
Reservation roomDetails(Account user, int roomID, Reservation trolley);
Reservation trolleyMenu(Account user, Reservation trolley);


void booking(Account user);

int productCategorySelection();


//utility functions
bool isNumeric(string input);

// extras
bool toInteger(string* input, int* valueholder);
 
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
					home(user);
				}
				else if(user.getRole() == "user") {
					home(user);
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
void home(Account user) {

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
			rooms(user);
			break;
		case 2:
			booking(user);
			break;
		case 3:
			feedback(user);
			break;
		}
	}
}
void feedback(Account user)
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
	newFeed.user = user.userId; //get current custID to insert to feedback table.

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

void rooms(Account user) {
	Reservation trolley;
	trolley.user = user.userId;

	ArrowMenu roomMenu;
	roomMenu.footer = "Select Room Type";
	roomMenu.addOption("Master Bedroom");
	roomMenu.addOption("Queen Bedroom");
	roomMenu.addOption("Single Bedroom");
	roomMenu.addOption("View Cart");
	//roomMenu.addOption("Back");
	while (1)
	{
		roomMenu.header = "Room \nItems in trolley:" +to_string(trolley.count()) + "\nTotal Price: " + to_string(trolley.total());
		switch (roomMenu.prompt())
		{
		case -1:
			return;
			break;
		case 0:
			trolley = roomType(user, 1,trolley);
			break;
		case 1:
			trolley = roomType(user, 2, trolley);
			break;
		case 2:
			trolley = roomType(user, 3, trolley);
			break;
		case 3:
			trolley = trolleyMenu(user, trolley);
			break;

		}
	}
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
		case 1:
			cout << "Insert Pax :";
			int pax;
			cin >> pax;
			if (pax > 0) {
				trolley.addPax(rooms, pax);
			}
			_getch();
			break;
		/*case 2:
			cout << "Check-in Date :";
			string date;
			cin >> date;
			int numericDate = std::stoi(date);

			if (numericDate > 0) {
				trolley.addRoom(rooms, numericDate);
			}
			_getch();
			break;*/
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





void booking(Account user) {

	string checkOut, checkIn;
	bool sortByDate = true, ascending = true;
	vector<int> roomTypeId;

	ArrowMenu bookingMenu;
	bookingMenu.addOption("Start");
	bookingMenu.addOption("End");
	bookingMenu.addOption("Start");
	bookingMenu.addOption("Start");
	bookingMenu.setValue(3, "Date");
	bookingMenu.addOption("Order");
	bookingMenu.setValue(4, "Ascending");
	bookingMenu.addOption("Generate");

	vector<Booking> result;

	string roomName[] = { "None","Master Bedroom", "Queen Bedroom", "Single Bedroom" };

	string selectedCategoryName;
	int tmpSelectedCategory;

	vector<int>::iterator iterator; //iterator is declare using what we are iterating, in this case it is vector of integer
	int option = 0;
	while (1)
	{

		selectedCategoryName = "";
		if (roomTypeId.empty()) {
			selectedCategoryName = "NONE";
		}
		else {
			for (int i = 0; i < roomTypeId.size(); i++) {
				selectedCategoryName += roomName[roomTypeId[i]] + ", ";
			}
		}
		bookingMenu.setValue(2, selectedCategoryName);



		// report display
		stringstream ss;
		// construct our report header
		ss << endl << "--- Booking Details ---" << endl << "|" << setw(20) << "Date Check In" << "|";
		if (!roomTypeId.empty()) {
			// if category id not empty we add category column
			ss << setw(20) << "Room Type" << "|";
		}
		ss << setw(20) << "Quantity" << "|";

		double totalSale = 0;
		// repeat same structure for content of the report
		for (int i = 0; i < result.size(); i++) {
			ss << endl << "|" << setw(20) << result[i].checkInDate.substr(0, 7) << "|";
			if (!roomTypeId.empty()) {
				// if category id not empty we add category column
				ss << setw(20) << result[i].roomType << "|";
			}
			//ss << setw(20) << result[i].value << "|";
			//totalSale += result[i].value;

		}

		ss << endl << "|" << setw(20) << "Total Sale" << "|";
		if (!roomTypeId.empty()) {
			// if category id not empty we add category column
			ss << setw(20) << "" << " ";
		}
		ss << setw(20) << totalSale << "|";

		ss << endl << "--- END OF Booking ---" << endl;
		bookingMenu.header = ss.str();

		option = bookingMenu.prompt(option);
		switch (option)
		{
		case -1:
			return;
			break;
		case 0:
			cout << "Insert start date (yyyy-mm-dd): ";
			cin >> checkIn;
			bookingMenu.setValue(0, checkIn);
			break;
		case 1:
			cout << "Insert end date (yyyy-mm-dd): ";
			cin >> checkOut;
			bookingMenu.setValue(1, checkOut);
			break;
		case 2: //toggle category
			tmpSelectedCategory = productCategorySelection();

			//find the selcted category id inside our categoryIds vector
			iterator = find(roomTypeId.begin(), roomTypeId.end(), tmpSelectedCategory);

			if (iterator == roomTypeId.end()) {//if the iterator reaches the end means not found
				roomTypeId.push_back(tmpSelectedCategory);
			}
			else {
				roomTypeId.erase(iterator); //if it exist erase it
			}

			break;
		case 3:// sort by
			sortByDate = !sortByDate;
			if (sortByDate)
				bookingMenu.setValue(3, "Date");
			else
				bookingMenu.setValue(3, "Price");
			break;
		case 4:
			ascending = !ascending;
			if (ascending)
				bookingMenu.setValue(4, "Ascending");
			else
				bookingMenu.setValue(4, "Descending");
			break;
		case 5:
			result.clear();
			result = Booking::bookingConfirmation(checkIn, checkOut,roomTypeId, sortByDate, ascending);
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
