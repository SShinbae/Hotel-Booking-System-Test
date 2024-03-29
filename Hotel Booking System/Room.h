#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "DBConnect.h"

class roomVariety
{
public:
	int roomId, rType, quantity, user, days;
	std::string roomNum, availability, checkInDate, checkOutDate, description;
	double price;

	roomVariety();
	roomVariety(sql::ResultSet* data);

	~roomVariety();

	static roomVariety findRoom(int roomId);

	static std::vector<roomVariety> findRooms();

	static std::vector<roomVariety> findRoom(int rType, std::string keyword, double minPrice,
		double maxPrice, std::string sortColumn, bool ascending);
	void insertR();

	std::string getAvailability();

	void setAvailability(const std::string& type);
};


#endif