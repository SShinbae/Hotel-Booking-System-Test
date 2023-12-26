#include "Room.h"
#include <vector> 
using namespace std;

roomVariety::roomVariety() {
	roomID = 0;
	name = "";
	rType = 0;
	price = 0;
	availability = "";
	pax = 0;
}

roomVariety::roomVariety(sql::ResultSet* data) {
	roomID = data->getInt("roomID");
	name = data->getString("name");
	rType = data->getInt("rType");
	price = data->getDouble("price");
	availability = data->getString("availability");
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

roomVariety::~roomVariety() {

}