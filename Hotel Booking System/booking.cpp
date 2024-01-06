#include "booking.h"
#include "Room.h"
using namespace std;
using namespace sql;

Booking::Booking()
{
}

Booking::Booking(ResultSet* data) {
	reservationID = data->getInt("reservationID");
	rID = data->getInt("rID");
	user = data->getInt("user");
	quantity = data->getInt("quantity");
	checkInDate = data->getString("checkInDate");
	checkOutDate = data->getString("checkOutDate");
	roomName = data->getString("roomName");
	pax = data->getInt("pax");
	price = data->getInt("price");
}

Booking::Booking(int reservationID, int rID, int quantity, int pax, int user, int price, 
	std::string checkInDate, std::string checkOutDate,std::string roomName)
{
	
	this->reservationID = reservationID;
	this->rID = rID;
	this->user = user;
	this->quantity = quantity;
	this->checkInDate = checkInDate;
	this->checkOutDate = checkOutDate;
	this->roomName = roomName;
	this->pax = pax;
	this->price = price;
}

std::vector<Booking> Booking::bookingConfirmation(int reservationID, int rID, int quantity, int pax, int user, int price, std::string checkInDate, std::string checkOutDate, std::string roomName)
{
	return std::vector<Booking>();
}

void Booking::insert() {

	DBConnection db;//instantiate
	try {
		db.prepareStatement("INSERT INTO booking (rID, user, quantity,pax, checkInDate, checkOutDate, roomName, price) VALUES (?,?,?,?,?,?,?,?)");
		
		db.stmt->setInt(1, rID);
		db.stmt->setInt(2, user);
		db.stmt->setInt(3, quantity);
		db.stmt->setInt(4, pax);
		db.stmt->setString(5, checkInDate);
		db.stmt->setString(6, checkOutDate);
		db.stmt->setString(7, roomName);
		db.stmt->setDouble(8, price);
		db.QueryStatement();

	}
	catch (std::exception& e) {
		std::cerr << "Error inserting into the database: " << e.what() << std::endl;
		// Handle the error as needed (e.g., log, display an error message)
	}

}

//std::vector<int> paxValues;

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
			std::string query = "UPDATE roomtypes SET capacity = capacity + ? WHERE roomtypeID = ?";
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