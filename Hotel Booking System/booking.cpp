#include "booking.h"
using namespace std;
using namespace sql;

Booking::Booking(ResultSet* data) {
	checkInDate = data->getString("checkInDate");
	checkOutDate = data->getString("checkOutDate");
	roomType = data->getString("roomType");
	pax = data->getInt(pax);
}

std::vector<Booking> Booking::bookingConfirmation(std::string checkIn, std::string checkOut, std::vector<int> roomTypeId, bool sortByDate, bool ascending)
{
	return std::vector<Booking>();
}

static std::vector<Booking> bookingConfirmation(std::string checkIn, std::string checkOut, std::vector<int> roomTypeId, bool sortByDate, bool ascending) {

	string categoryString = "";
	if (roomTypeId.size() > 0) {
		categoryString = " AND p.category IN (";
		for (int i = 0; i < roomTypeId.size(); i++) {
			categoryString += "?,";
		}
		// since we add , after each placeholder we now have extra comma at the end
		categoryString.erase(categoryString.size() - 1); //remove the character at the end 
		categoryString += ") "; //  close bracket   

	}
	// categoryIds wil also be used as condition but since 


	// construct our query for the table and joins part first
	string sql = " SELECT b.checkInDate as start, rt.type as categoryName, SUM(r.price * r.quantity) as value "
		" FROM reservation r "
		" JOIN booking  ON r.reservationID = b.reservationID "
		" JOIN room r ON r.roomID = b.roomID "
		" JOIN room_type ON  rt.roomtypeID = r.rType "
		+ categoryString; // append category string which will be our join condition if cateogryId vector is not empty 
	// whereby if the categoryIds is empty this will simply be appending empty string that changes nothing

// add the where clause 
	sql += " WHERE  b.checkInDate >= ? AND b.checkInDate <= ? ";
	
	// now construct our grouping
	sql += " GROUP BY ";
	if (!roomTypeId.empty()) {
		// if categoryids is not empty only we group by category
		sql += " r.rType, ";
	}
	// otherwise we skip the p.category to only groups it by its year and month
	sql += " CAST(MONTH(b.checkInDate) AS VARCHAR(2)) + '-' + CAST(YEAR(b.checkInDate) AS VARCHAR(4)) ";
	//    10-2023

	sql += " ORDER BY  ";
	if (sortByDate) {
		// we have bool sortByDate parameter, if this value is true then we use date column for ordering
		sql += " t.dateTime ";
	}
	else {
		// otherwise we use the result column sale for ordering
		sql += " value ";
	}

	// finally the ordering direction determined using boolean ascending
	if (ascending) {
		sql += " ASC ";
	}
	else {
		sql += " DESC ";
	}

	// declare vector > execute query > return result in vector 
	vector <Booking> bookingConfirmation;

	DBConnection db;

	db.prepareStatement(sql);
	// since we have non-fixed number of placeholder ? in our prepared statment we need to use a varaible to keep track of the index

	int index = 1; // start from 1
	// load the value for category ids
	while (index <= roomTypeId.size()) {
		// remember our index starts from 1 to follow prepared statement indexing
		// thus, our exit condition is until the vector size

		db.stmt->setInt(index, roomTypeId[index - 1]); // and we -1 to access the item in the vector since vector index starts from 0
		index++;
	}
	// after the loop we have the latest index value ready to be use for our where condition placehoders (?)
	// if categoryIds is empty, size 0 the previous loop will not occur and index here is still 1 so it will still be correct
	db.stmt->setString(index, checkIn);
	index++;//move index forward
	db.stmt->setString(index, checkOut);
	db.QueryResult();


	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Booking tmpSale(db.res);
			bookingConfirmation.push_back(tmpSale);

		}
	}

	db.~DBConnection();
	return bookingConfirmation;

}