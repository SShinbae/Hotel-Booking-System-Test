#pragma once
#ifndef ADDROOM_H
#define ADDROOM_H

#include <string>
#include <vector>
#include "DBConnect.h"

class Bedroom{

public:

    //roomtypes
    int roomtypeID, capacity;
    std::string type, description;
    //room
    int roomID, rType;
    std::string name, availability;
    bool price;


    Bedroom();

    Bedroom(int roomtypeID, int capacity, std::string type, 
        std::string description, int roomID, int rType, 
        std::string name, std::string availbility, bool price);

    Bedroom(sql::ResultSet* data);


    void insertRT();
    void insertR();
    void update();


    ~Bedroom();

    static std::vector<Bedroom> findBedroom();

};
#endif