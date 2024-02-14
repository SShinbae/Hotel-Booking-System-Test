#pragma once
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "DBConnect.h"
#include "Room.h"

class Booking
{
public:
	int reservationId, rId, quantity,  user;
	std::string checkInDate, checkOutDate, roomNum;
	double price;
	Booking();

	Booking(sql::ResultSet* data);

	Booking(int reservationId, int rId, int quantity, int user, double price, std::string checkInDate, std::string checkOutDate, std::string roomNum);
	static std::vector<Booking> bookingConfirmation(int reservationId, int rId, int quantity, 
		int user,int price, std::string checkInDate, std::string checkOutDate,std::string roomNum);
	
	void insert();

	static std::vector<Booking> findBooking(int user);
	static std::vector<Booking> findBookingAdmin();
	static void updateRoomTypeCapacity(int roomTypeId, int increment);

	~Booking() {

	};
};

#endif // !BOOKING_H

