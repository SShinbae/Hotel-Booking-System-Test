#include "feedback.h"
#include "DBConnect.h"
#include <vector>
#include <iomanip>

using namespace std;

Feedback::Feedback() {
	//initialize
	feedBackId = 0;
	user = 0;
	messages = "";
	date = "";
}



Feedback::Feedback(int feedBackId, int user, std::string messages, std::string date) {
	this->feedBackId = feedBackId;
	this->user = user;
	this->messages = messages;
	this->date = date;
	
}

Feedback::Feedback(sql::ResultSet* data) {
	feedBackId = data->getInt("feedBackId");
	user = data->getInt("user");
	messages = data->getString("messages");
	date = data->getString("date");
	
}



/*vector<Feedback> Feedback::displayFeedback(int user)
{
	
	string sql = "SELECT * from feedback WHERE user = ?";

	DBConnection db;
	db.prepareStatement(sql);
	

	vector<Feedback> result;
	
	db.QueryResult();

	if (db.res->rowsCount() >0 ) {

		while (db.res->next()) {
			feedBackId = db.res->getInt("feedBackId");
			user = db.res->getInt("user");
			messages = db.res->getString("messages");

		}
	}
	db.~DBConnection();
	return result;
}
*/
void Feedback::insert() {
	
	DBConnection db;//instantiate
	db.prepareStatement("Insert into feedback (user,messages) VALUES (?,?)");
	db.stmt->setInt(1, user);
	db.stmt->setString(2, messages);
	db.QueryStatement();
	db.~DBConnection();
}


Feedback::~Feedback()
{
}

std::vector<Feedback> Feedback::findFeedback(int user)
{
	string query = "SELECT * FROM `feedback` WHERE user = ?";

	// 
	DBConnection db;
	
	db.prepareStatement(query);
	
	db.stmt->setInt(1, user);

	vector<Feedback> products;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Feedback tmpProduct(db.res);
			products.push_back(tmpProduct);

		}
	}

	//db.~DBConnection();
	return products;
	
}

std::vector<Feedback> Feedback::findFeedbackAdmin()
{
	string query = "SELECT * FROM `feedback`";

	// 
	DBConnection db;

	db.prepareStatement(query);
	vector<Feedback> products;
	db.QueryResult();

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Feedback tmpProduct(db.res);
			products.push_back(tmpProduct);

		}
	}

	//db.~DBConnection();
	return products;
}

	