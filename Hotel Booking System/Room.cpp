#include "Room.h"
#include <vector> 
using namespace std;

roomVariety::roomVariety() {
	roomId = 0;
	roomNum = "";
	rType = 0;
	price = 0;
	availability = "";
	quantity = 0;
	description = "";
}

roomVariety::roomVariety(sql::ResultSet* data) {
	roomId = data->getInt("roomId");
	roomNum = data->getString("roomNum");
	rType = data->getInt("rType");
	price = data->getDouble("price");
	availability = data->getString("availability");
	description = data->getString("description");
}

vector<roomVariety> roomVariety::findRoom(int rType,string keyword, double minPrice,
	double maxPrice, string sortColumn, bool ascending) {

	string query = "SELECT * FROM `room` WHERE "
		"(description LIKE ? AND availability = 'YES') AND price >= ? AND price <= ? AND rType = ? "
		"ORDER BY " + sortColumn + (ascending ? " ASC" : " DESC");
	// 
	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + keyword + "%");
	db.stmt->setDouble(2, minPrice);
	db.stmt->setDouble(3, maxPrice);
	db.stmt->setInt(4, rType);

	vector<roomVariety> rooms;

	// Execute the query and handle results
	try {
		db.QueryResult();
		if (db.res->rowsCount() > 0) {
			while (db.res->next()) {
				roomVariety tmpRoom(db.res);
				rooms.push_back(tmpRoom);
			}
		}
	}
	catch (const sql::SQLException& e) {
		// Handle SQL exceptions here
		// For example, log the exception details:
		std::cerr << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
			<< ", SQLState: " << e.getSQLState() << ")" << std::endl;
	}

	
	return rooms;
}

void roomVariety::insertR()
{
	DBConnection db;//instantiate
	try {
		db.prepareStatement("INSERT INTO room (rType, roomNum, price, description, availability) VALUES (?,?,?,?,?)");
		db.stmt->setInt(1, rType);
		db.stmt->setString(2, roomNum);
		db.stmt->setDouble(3, price);
		db.stmt->setString(4, description);
		db.stmt->setString(5, availability);
		db.QueryStatement();

	}
	catch (std::exception& e) {
		std::cerr << "Error inserting into the database: " << e.what() << std::endl;
		// Handle the error as needed (e.g., log, display an error message)
	}
}

std::string roomVariety::getAvailability()
{
	return std::string();
}

void roomVariety::setAvailability(const std::string& type){
	availability = type;
}


roomVariety roomVariety::findRoom(int roomId) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM room WHERE roomId=?");
	db.stmt->setInt(1, roomId);
	db.QueryResult();

	roomVariety result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			roomVariety found(db.res);
			result = found;
		}
	}
	db.~DBConnection();
	return result;
}

std::vector<roomVariety> roomVariety::findRooms(){

	string querys = "SELECT * FROM `room`";

	DBConnection db;

	db.prepareStatement(querys);

	vector<roomVariety> roomDisp;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			roomVariety tempRoom(db.res);
			roomDisp.push_back(tempRoom);

		}
	}

	db.~DBConnection();
	return roomDisp;


}

roomVariety::~roomVariety() {

}