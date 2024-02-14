#include "AddRoom.h"
#include <vector>
#include <iomanip>
using namespace std;

Bedroom::Bedroom() {
	//initialize
	roomTypeId = 0;
	capacity = 0;
	type = "";
	description = "";
	
}


Bedroom::Bedroom(int roomTypeId, int capacity, std::string type, std::string description)
{
	//roomType
	this->roomTypeId = roomTypeId;
	this->capacity = capacity;
	this->type = type;
	this->description = description;
	
}
//display room types
Bedroom::Bedroom(sql::ResultSet* data) {
	roomTypeId = data->getInt("roomTypeId");
	capacity = data->getInt("capacity");
	type = data->getString("type");
	description = data->getString("description");
	

}

//roomType insert
void Bedroom::insertRT() {

	DBConnection db;//instantiate
	try {
		db.prepareStatement("INSERT INTO roomtypes (type, capacity, description) VALUES (?,?,?)");
		db.stmt->setString(1, type);
		db.stmt->setInt(2, capacity);
		db.stmt->setString(3, description);
		db.QueryStatement();
		
	}catch(std::exception& e) {
		std::cerr << "Error inserting into the database: " << e.what() << std::endl;
		// Handle the error as needed (e.g., log, display an error message)
	}
	
}

Bedroom::~Bedroom()
{

}




std::vector<Bedroom> Bedroom::findBedroom()
{
	string query = "SELECT * FROM `roomtypes` ";
	DBConnection db;

	db.prepareStatement(query);
	vector<Bedroom> roomA;
	db.QueryResult();
	

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Bedroom tmpRoom(db.res);
			roomA.push_back(tmpRoom);

		}
	}

	db.~DBConnection();
	return roomA;

	
}