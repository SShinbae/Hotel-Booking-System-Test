#pragma once
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>
#include "Room.h"

class Reservation
{
public:

	std::string dateTime, checkInDate, checkOutDate;
	int reservationID, user, pax;
	

	std::vector<std::pair<roomVariety,int>> items; // pair of product and its quantity, represents the transaction_item table

	Reservation();
	void addPax(roomVariety room,int pax);
	void addRoom(roomVariety room, int quantity);
	void insert();
	double total();
	int count();
};


#endif
