#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
class Account {
public:
    int customerID;
    std::string username, numIC, phoneNum, email, name, address;

    

    Account();
    
    Account(int customerID, std::string username, std::string password, std::string email, std::string numIC, std::string phoneNum, std::string name, std::string address);
            
    bool login();
    void insert();
    void update();
    void remove();


    ~Account();

    //static Account findFeedback(int  customerID);

    static Account older(Account a, Account b);
    //void setNumIC(std::string numIC);

    void setPassword(std::string pass);
    std::string getPassword();
    bool MatchPasswordWith(std::string plainText);

private:
    std::string password;

    std::string encrypt(std::string input);
    char toChar(int asciiDecimal);
    bool isMatch(std::string encrypted, std::string testText);

    
};

#endif
