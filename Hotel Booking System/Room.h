#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "DBConnect.h"

class roomVariety
{
public:
	int roomID, rType, pax;
	std::string name, availability;
	double price;

	roomVariety();
	roomVariety(sql::ResultSet* data);

	~roomVariety();

	static roomVariety findRoom(int roomID);

	static std::vector<roomVariety> findRoom(int rType, std::string keyword, double minPrice,
		double maxPrice, std::string sortColumn, bool ascending);

};


#endif