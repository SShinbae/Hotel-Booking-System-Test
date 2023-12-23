#include <iostream>
#include <ctime>
#include <vector>
#include "feedback.h"
#include "DBConnect.h"
#include <iomanip>
#include "Account.h"

using namespace std;

Feedback::Feedback() {
	//initialize
	feedBackId = 0;
	user = 0;
	messages = "";
	feedBackTypes = "";
}



Feedback::Feedback(int feedBackId, int user, std::string messages, std::string feedBackTypes) {
	this->feedBackId = feedBackId;
	this->user = user;
	this->messages = messages;
	this->feedBackTypes = feedBackTypes;
	
}

Feedback::Feedback(sql::ResultSet* data) {
	feedBackId = data->getInt("feedBackId");
	user = data->getInt("user");
	messages = data->getString("messages");
	feedBackTypes = data->getString("feedBackTypes");
	
}

Feedback::~Feedback()
{
}
/*
Feedback Feedback::findFeedback(int user) {

	//DBConnection db;
	/*db.prepareStatement("SELECT * FROM feedback WHERE custId=?");
	db.stmt->setInt(1, custId);
	
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			custId = db.res->getInt("custId");
			feedBackId = db.res->getInt("feedBackId");
			messages = db.res->getString("messages");
			phoneNum = db.res->getString("phoneNum");
			username = db.res->getString("username");
			password = db.res->getString("password");
			email = db.res->getString("email");
			address = db.res->getString("address");
		}
		db.~DBConnection();
		return true;
	}

	vector<Feedback> items;
	DBConnection db;
	db.prepareStatement("SELECT * FROM feedback WHERE custId= ?");
	db.stmt->setInt(1, custId);

	
	db.QueryResult();
	Feedback dispF;

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Feedback found(db.res);
			dispF = found;

		}
	}

	db.~DBConnection();
	return dispF;
	
}*/

void Feedback::insert() {
	
	DBConnection db;//instantiate

	/*std::string query = "SELECT custId FROM feedback WHERE custId = ?";
	db.prepareStatement(query);
	db.stmt->setInt(1, custId);


	db.QueryResult();*/

	db.prepareStatement("Insert into feedback (user, messages,feedBackTypes) VALUES (?,?,?)");
	db.stmt->setInt(1, user);
	db.stmt->setString(2, messages);
	db.stmt->setString(3, feedBackTypes);
	db.QueryStatement();
	db.~DBConnection();
}


