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
	int reservationID, user;
	
	

	std::vector<std::pair<roomVariety,int>> items; // pair of product and its quantity, represents the transaction_item table

	Reservation();
	void addQuantity(roomVariety room, int quantity,  std::string checkInDate, std::string checkOutDate);
	void insert();
	double total();
	int count();

	bool isCheckOutAfterCheckIn(const std::string& checkInDate, const std::string& checkOutDate);
};


#endif
