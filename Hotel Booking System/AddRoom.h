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
   

    Bedroom();

    Bedroom(int roomtypeID, int capacity, std::string type, std::string description);

    Bedroom(sql::ResultSet* data);


    void insertRT();
    
    //void update();


    ~Bedroom();

    static std::vector<Bedroom> findBedroom();


};
#endif