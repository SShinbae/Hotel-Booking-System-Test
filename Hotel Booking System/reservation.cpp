#include "reservation.h"
#include "AddRoom.h"
#include <string> 
#include<vector>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

Reservation::Reservation() {
	dateTime = "";
	reservationId = 0;
	user = 0;
}



void Reservation::insert() {
	DBConnection db;
	db.prepareStatement("INSERT INTO reservation(user) VALUES (?)");
	db.stmt->setInt(1, user);
	db.QueryStatement();
	reservationId = db.getGeneratedId();
	// get back the generated id to be used during insertion of booking

    // Ensure the number of placeholders matches the number of columns
    string query = "INSERT INTO `booking`(`reservationId`, `rId`, `quantity`,  `checkInDate`, `checkOutDate`, `user`, `price`, `roomNum`) VALUES ";
    for (int i = 0; i < items.size(); i++) {
        query += "(?,?,?,?,?,?,?,?),"; // 9 placeholders for 9 columns
    }
    query.erase(query.size() - 1); // Remove the extra comma at the end

    try {
        db.prepareStatement(query);
        for (int i = 0; i < items.size(); i++) {
            int base = i * 8;
            db.stmt->setInt(base + 1, reservationId);
            db.stmt->setInt(base + 2, items[i].first.roomId);
            db.stmt->setInt(base + 3, items[i].second); // Quantity
            db.stmt->setString(base + 4, items[i].first.checkInDate);
            db.stmt->setString(base + 5, items[i].first.checkOutDate);
            db.stmt->setInt(base + 6, user);
            db.stmt->setDouble(base + 7, items[i].first.price * items[i].second);
            db.stmt->setString(base + 8, items[i].first.roomNum);
        }
        db.QueryStatement();

        // Now, update the room availability for each room booked.
        for (const auto& item : items) {
            string updateQuery = "UPDATE room SET availability = 'Occupied' WHERE roomId = ?";
            db.prepareStatement(updateQuery);
            db.stmt->setInt(1, item.first.roomId); // Bind the room ID parameter
            db.QueryStatement();

        }

        for (const auto& item : items)
        {
            // Decrement the capacity
            string updateCapacityQuery = "UPDATE roomtypes SET capacity = capacity - ? WHERE roomtypeID = ?";
            db.prepareStatement(updateCapacityQuery);
            db.stmt->setInt(1, item.second); // Assuming 'item.second' is the number of rooms booked
            db.stmt->setInt(2, item.first.rType);
            db.QueryStatement();
        }




    }
    catch (const std::exception& e) {
        cout << "SQL Error: " << e.what() << endl;
        return;
    }
	
}


// Function to calculate the number of days between two dates
int calculateDaysBetween(const std::string& start_date, const std::string& end_date) {
    std::tm tm_start = {};
    std::tm tm_end = {};
    std::istringstream ss_start(start_date);
    std::istringstream ss_end(end_date);

    ss_start >> std::get_time(&tm_start, "%Y-%m-%d");
    ss_end >> std::get_time(&tm_end, "%Y-%m-%d");

    std::chrono::system_clock::time_point tp_start = std::chrono::system_clock::from_time_t(std::mktime(&tm_start));
    std::chrono::system_clock::time_point tp_end = std::chrono::system_clock::from_time_t(std::mktime(&tm_end));

    auto duration = tp_end - tp_start;
    return std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
}


// Example usage in your existing function:
void Reservation::addQuantity(roomVariety room, int quantity, std::string checkInDate, std::string checkOutDate) {
    room.checkInDate = checkInDate;
    room.checkOutDate = checkOutDate;

    // Calculate the number of days between check-in and check-out
    int days = calculateDaysBetween(checkInDate, checkOutDate);

    // You can now use 'days' to calculate the price if needed
    room.price *= days; // For example, if price is per day

    items.push_back({room, 1}); // Add room and quantity
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


