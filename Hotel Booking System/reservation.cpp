#include "reservation.h"
#include <string> 
#include<vector>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

Reservation::Reservation() {
	dateTime = "";
	reservationID = 0;
	user = 0;
	pax = 0;
}



void Reservation::insert() {
	DBConnection db;
	db.prepareStatement("INSERT INTO reservation(user) VALUES (?)");
	db.stmt->setInt(1, user);
	db.QueryStatement();
	reservationID = db.getGeneratedId();
	// get back the generated id to be used during insertion of booking

    // Ensure the number of placeholders matches the number of columns
    string query = "INSERT INTO `booking`(`reservationID`, `rID`, `quantity`, `pax`, `checkInDate`, `checkOutDate`, `user`, `price`, `roomName`) VALUES ";
    for (int i = 0; i < items.size(); i++) {
        query += "(?,?,?,?,?,?,?,?,?),"; // 9 placeholders for 9 columns
    }
    query.erase(query.size() - 1); // Remove the extra comma at the end

    try {
        db.prepareStatement(query);
        for (int i = 0; i < items.size(); i++) {
            int base = i * 9;
            db.stmt->setInt(base + 1, reservationID);
            db.stmt->setInt(base + 2, items[i].first.roomID);
            db.stmt->setInt(base + 3, items[i].second); // Quantity
            db.stmt->setInt(base + 4, items[i].first.pax); // Pax
            db.stmt->setString(base + 5, items[i].first.checkInDate);
            db.stmt->setString(base + 6, items[i].first.checkOutDate);
            db.stmt->setInt(base + 7, user);
            db.stmt->setDouble(base + 8, items[i].first.price * items[i].second);
            db.stmt->setString(base + 9, items[i].first.name);
        }
        db.QueryStatement();
    }
    catch (const std::exception& e) {
        cout << "SQL Error: " << e.what() << endl;
        return;
    }
	
}

void Reservation::addQuantity(roomVariety room, int quantity, int pax, std::string checkInDate, std::string checkOutDate) {
	room.checkInDate = checkInDate;
	room.checkOutDate = checkOutDate;
	room.pax = pax;
	//room.user = this->user;
	
	items.push_back({ room, quantity }); // Add room and quantity

	// Set the user value of the Reservation object
	//this->user = room.user;
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


