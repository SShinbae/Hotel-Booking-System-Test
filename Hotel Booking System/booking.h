#pragma once
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include "DBConnect.h"

class Booking
{
public:
	std::string checkInDate, checkOutDate, roomType, pax;
	double value;

	Booking(sql::ResultSet* data);

	static std::vector<Booking> bookingConfirmation(std::string checkIn, std::string checkOut, std::vector<int> roomTypeId, bool sortByDate, bool ascending);
	
	~Booking() {

	};
};

#endif // !BOOKING_H

