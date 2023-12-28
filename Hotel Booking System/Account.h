#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
class Account {
public:
    int userId;
    std::string username, numIc, phoneNum, email, name, address, usertype;
    bool isAdmin;
    

    Account();
    
    Account(int userId, std::string username, std::string password, std::string email, std::string numIc, std::string phoneNum, std::string name, std::string address, std::string usertype);
            
    bool login();
    void insert();
    void update();
    void remove();

    std::string getRole();

    ~Account();

    void setPassword(std::string pass);
    std::string getPassword();
    bool MatchPasswordWith(std::string plainText);

private:
    std::string password;

    std::string encrypt(std::string input);
    char toChar(int asciiDecimal);
    bool isMatch(std::string encrypted, std::string testText);
    //std::string usertype;
    
};

#endif
