#include "booking.h"
#include "Room.h"
using namespace std;
using namespace sql;

Booking::Booking()
{
}

Booking::Booking(ResultSet* data) {
	reservationId = data->getInt("reservationId");
	rId = data->getInt("rId");
	user = data->getInt("user");
	quantity = data->getInt("quantity");
	checkInDate = data->getString("checkInDate");
	checkOutDate = data->getString("checkOutDate");
	roomNum = data->getString("roomNum");
	price = data->getDouble("price");
}

Booking::Booking(int reservationId, int rId, int quantity, int user, double price, 
	std::string checkInDate, std::string checkOutDate,std::string roomNum)
{
	
	this->reservationId = reservationId;
	this->rId = rId;
	this->user = user;
	this->quantity = quantity;
	this->checkInDate = checkInDate;
	this->checkOutDate = checkOutDate;
	this->roomNum = roomNum;
	this->price = price;
}

std::vector<Booking> Booking::bookingConfirmation(int reservationID, int rID, int quantity, int user, int price, std::string checkInDate, std::string checkOutDate, std::string roomName)
{
	return std::vector<Booking>();
}

void Booking::insert() {

	DBConnection db;//instantiate
	try {
		db.prepareStatement("INSERT INTO booking (rId, user, quantity, checkInDate, checkOutDate, roomNum, price) VALUES (?,?,?,?,?,?,?,?)");
		
		db.stmt->setInt(1, rId);
		db.stmt->setInt(2, user);
		db.stmt->setInt(3, quantity);
		db.stmt->setString(4, checkInDate);
		db.stmt->setString(5, checkOutDate);
		db.stmt->setString(6, roomNum);
		db.stmt->setDouble(7, price);
		db.QueryStatement();

	}
	catch (std::exception& e) {
		std::cerr << "Error inserting into the database: " << e.what() << std::endl;
		// Handle the error as needed (e.g., log, display an error message)
	}

}


std::vector<Booking> Booking::findBookingAdmin()
{
	string query = "SELECT * FROM `booking` ";
	DBConnection db;

	db.prepareStatement(query);
	//db.stmt->setInt(1, user);
	vector<Booking> roomA;
	db.QueryResult();


	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Booking tmpRoom(db.res);
			roomA.push_back(tmpRoom);

		}
	}

	db.~DBConnection();
	return roomA;


}

void Booking::updateRoomTypeCapacity(int roomTypeId, int increment)
{
		DBConnection db;

		try {
			std::string query = "UPDATE roomtypes SET capacity = capacity + ? WHERE roomTypeId = ?";
			db.prepareStatement(query);
			db.stmt->setInt(1, increment); // Increment value
			db.stmt->setInt(2, roomTypeId); // Room Type ID

			db.QueryStatement(); // Execute the update query

			std::cout << "Room type capacity updated successfully." << std::endl;
		}
		catch (std::exception& e) {
			std::cerr << "Error updating room type capacity: " << e.what() << std::endl;
			// Handle the error appropriately
		}
	
}




std::vector<Booking> Booking::findBooking(int user)
{
	string query = "SELECT * FROM `booking` WHERE user = ? ";
	DBConnection db;

	db.prepareStatement(query);
	db.stmt->setInt(1, user);
	vector<Booking> roomA;
	db.QueryResult();


	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Booking tmpRoom(db.res);
			roomA.push_back(tmpRoom);

		}
	}

	db.~DBConnection();
	return roomA;


}