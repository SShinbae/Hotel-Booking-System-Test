#include "reservation.h"
#include <string> 
#include<vector>
using namespace std;

Reservation::Reservation() {
	dateTime = "";
	reservationID = 0;
	user = 0;
	pax = 0;
}



void Reservation::insert() {

	DBConnection db;
	/*db.prepareStatement("INSERT INTO reservation(user) VALUES (?)");
	db.stmt->setInt(1, user);
	db.QueryStatement();
	reservationID = db.getGeneratedId();*/
	// get back the generated id to be used during insertion of transaction items

	string query = "INSERT INTO `booking`(`reservationID`, `roomID`, `quantity`, `pax`, `checkInDate`, `checkOutDate`, `user`, `price`)  VALUES "; // (),()
	for (int i = 0; i < items.size(); i++) {
		query += "(?,?,?,?,?,?,?,?),";
		// 3 place holder per item/row/record
		//P  1,             2,        3
		// transactionId,productId,quantity 
	}
	query.erase(query.size() - 1); // remove the extra comma at the end
	db.prepareStatement(query);

	/*for (int i = 0; i < items.size(); i++) {
		// formula for inserting the value into the right index 
		// i * N + P
		// i is the index of item being loop through
		// N is number of place holder you have per row/item in your prepared statement; N = 3
		// P is the position of the value in each row
		// 
		// Example:
		// i=0, 0 * 3 + 1 = 1 || 0 * 3 + 2 = 2 || 0 * 3 + 3 = 3
		// i=1, 1 * 3 + 1 = 4 || 1 * 3 + 2 = 5 || 1 * 3 + 3 = 6
		// i=2, 2 * 3 + 1 = 7 || 2 * 3 + 2 = 8 || 2 * 3 + 3 = 9 

		db.stmt->setInt(i * 5 + 1, reservationID);
		db.stmt->setInt(i * 5 + 2, items[i].first.roomID);
		db.stmt->setInt(i * 5 + 3, items[i].second);
		//db.stmt->setInt(i * 6 + 4, items[i].first.pax);
	}*/
	for (int i = 0; i < items.size(); i++) {
		// Use i * 5 + 1, i * 5 + 2, and i * 5 + 3 consistently
		db.stmt->setInt(i * 8 + 1, reservationID);
		db.stmt->setInt(i * 8 + 2, items[i].first.roomID);
		db.stmt->setInt(i * 8 + 3, items[i].second);
		//Uncomment this line if you want to set the pax value
		db.stmt->setInt(i * 8 + 4, items[i].first.pax);
		// Set dateTime value
		db.stmt->setString(i * 8 + 5, dateTime);
	}

	db.QueryStatement();
	db.~DBConnection();



}
void Reservation::addPax(roomVariety room, int pax) {
	items.push_back({ room, pax }); // Adding an empty check-in date
}

void Reservation::addRoom(roomVariety room, int quantity) {
	items.push_back({ room, quantity }); 
	
}

double Reservation::total() {
	double total = 0;
	for (int i = 0; i < items.size(); i++) {
		total += items[i].first.price * items[i].second;
	}
	return total;
}

int Reservation::count() {
	double count = 0;
	for (int i = 0; i < items.size(); i++) {
		count += items[i].second;
	}
	return count;
}
