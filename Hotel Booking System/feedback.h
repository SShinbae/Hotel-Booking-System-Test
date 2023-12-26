#pragma once
#ifndef FEEDBACK_H
#define FEEDBACK_H
#include <vector>
#include <string>
#include "DBConnect.h"


class Feedback {

public:
    int feedBackId, user;
    std::string messages, date;
    
    
    Feedback();
    Feedback(sql::ResultSet* data);
    Feedback(int feedBackId, int user, std::string messages, std::string date);
    // Feedback(int feedBackId, int user, std::string messages, std::string feedBackTypes);
    
    //std::vector<Feedback> displayFeedback(int user);
    

    void insert();
    ~Feedback();

    static std::vector<Feedback> findFeedback(int user);

    
    
};

#endif
