#include "Room.h"
#include <vector> 
using namespace std;

roomVariety::roomVariety() {
	roomID = 0;
	name = "";
	rType = 0;
	price = 0;
	availability = "";
	quantity = 0;
	//pax = 0;
	//user = 0;
}

roomVariety::roomVariety(sql::ResultSet* data) {
	roomID = data->getInt("roomID");
	name = data->getString("name");
	rType = data->getInt("rType");
	price = data->getDouble("price");
	availability = data->getString("availability");
	//user = data->getInt("user");
	//category = data->getInt("category");
}

vector<roomVariety> roomVariety::findRoom(int rType,string keyword, double minPrice,
	double maxPrice, string sortColumn, bool ascending) {

	string query = "SELECT * FROM `room` WHERE "
		" (name LIKE ? OR availability LIKE ?) AND price >= ? AND price <= ? AND rType = ? "
		" ORDER BY " + sortColumn;
	if (ascending) {
		query += " ASC";
	}
	else {
		query += " DESC";
	}
	// 
	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + keyword + "%");
	db.stmt->setString(2, "%" + keyword + "%");
	db.stmt->setDouble(3, minPrice);
	db.stmt->setDouble(4, maxPrice);
	db.stmt->setInt(5, rType);
	//db.stmt->setInt(6, category);
	

	vector<roomVariety> rooms;

	db.QueryResult();
	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			roomVariety tmpRoom(db.res);
			rooms.push_back(tmpRoom);

		}
	}

	db.~DBConnection();
	return rooms;
}

void roomVariety::insertR()
{
	DBConnection db;//instantiate
	try {
		db.prepareStatement("INSERT INTO room (rType, name, price, availability) VALUES (?,?,?,?)");
		db.stmt->setInt(1, rType);
		db.stmt->setString(2, name);
		db.stmt->setDouble(3, price);
		db.stmt->setString(4, availability);
		db.QueryStatement();

	}
	catch (std::exception& e) {
		std::cerr << "Error inserting into the database: " << e.what() << std::endl;
		// Handle the error as needed (e.g., log, display an error message)
	}
}


roomVariety roomVariety::findRoom(int roomID) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM room WHERE roomID=?");
	db.stmt->setInt(1, roomID);
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

std::vector<roomVariety> roomVariety::findRooms()
{

	string querys = "SELECT * FROM `room` ";

	// 
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