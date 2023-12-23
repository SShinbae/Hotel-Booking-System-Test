#pragma once
#ifndef FEEDBACK_H
#define FEEDBACK_H
#include <vector>
#include <string>
#include "DBConnect.h"


class Feedback {

public:
    int feedBackId, user;
    std::string messages, feedBackTypes;
    

    Feedback();
    Feedback(int feedBackId, int user, std::string messages, std::string feedBackTypes);
    Feedback(sql::ResultSet* data);
    
    

    void insert();
    ~Feedback();
    //static vector<Feedback> findFeedback(int custId);
    //static std::vector<Feedback> findFeedback(int custId);

    static Feedback findFeedback(int user);
    
};

#endif
