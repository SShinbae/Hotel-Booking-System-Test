#pragma once
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include "DBConnect.h"

class Booking
{
public:
	int reservationID, rID, quantity, pax, user;
	std::string checkInDate, checkOutDate, roomName;
	double price;
	Booking();

	Booking(sql::ResultSet* data);

	Booking(int reservationID, int rID, int quantity, int pax, int user, int price, std::string checkInDate, std::string checkOutDate, std::string roomName);

	static std::vector<Booking> bookingConfirmation(int reservationID, int rID, int quantity, int pax,
		int user,int price, std::string checkInDate, std::string checkOutDate,std::string roomName);
	
	void insert();

	static std::vector<Booking> findBooking(int user);
	std::vector<Booking> findBookingAdmin();


	~Booking() {

	};
};

#endif // !BOOKING_H

