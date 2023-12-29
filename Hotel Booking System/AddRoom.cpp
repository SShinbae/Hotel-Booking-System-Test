#include "AddRoom.h"
#include "DBConnect.h" 
using namespace std;

Bedroom::Bedroom() {
	//initialize
	roomtypeID = 0;
	capacity = 0;
	type = "";
	description = "";
	//room
	rType = 0;
	roomID = 0;
	name = "";
	price = "";
	availability = "";
}


Bedroom::Bedroom(int roomtypeID, int capacity, std::string type, std::string description, int roomID, int rType, std::string name, std::string availbility, bool price)
{
	//roomType
	this->roomtypeID = roomtypeID;
	this->capacity = capacity;
	this->type = type;
	this->description = description;
	//room
	this->rType = rType;
	this->roomID = roomID;
	this->name = name;
	this->price = price;
	this->availability = availability;
}
//display room types
Bedroom::Bedroom(sql::ResultSet* data) {
	roomtypeID = data->getInt("roomtypeID");
	capacity = data->getInt("capacity");
	type = data->getString("type");
	description = data->getString("description");

}

//roomType insert
void Bedroom::insertRT() {

	DBConnection db;//instantiate
	try {
		db.prepareStatement("INSERT INTO roomTypes (type, capacity, description) VALUES (?,?,?)");
		db.stmt->setString(1, type);
		db.stmt->setInt(2, capacity);
		db.stmt->setString(3, description);
		db.QueryStatement();
		
	}catch(std::exception& e) {
		std::cerr << "Error inserting into the database: " << e.what() << std::endl;
		// Handle the error as needed (e.g., log, display an error message)
	}
	
}

void Bedroom::insertR() {
	DBConnection db;//instantiate
	try {
		db.prepareStatement("INSERT INTO room (rType, name, availability, price) VALUES (?,?,?,?)");
		
		db.stmt->setInt(1, rType);
		db.stmt->setString(2, name);
		db.stmt->setString(3, availability);
		db.stmt->setInt(4, price);
		db.QueryStatement();

	}
	catch (std::exception& e) {
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

	// 
	DBConnection db;

	db.prepareStatement(query);
	db.QueryResult();
	

	vector<Bedroom> roomA;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Bedroom tmpRoom(db.res);
			roomA.push_back(tmpRoom);

		}
	}

	//db.~DBConnection();
	return roomA;

	
}
