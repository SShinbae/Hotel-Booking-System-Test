#include "Account.h"
#include <ctime>
#include "DBConnect.h" 
using namespace std;

Account::Account() {
	//initialize
	userId = 0;
	username = "";
	password = "";
	email = "";
	numIc = "";
	phoneNum = "";
	name = "";
	address = "";
	usertype = "";
}


Account::Account(int userId, std::string  numIc, std::string  phoneNum, std::string username, std::string password, std::string email, std::string name, std::string address, std::string usertype) {
	this->userId = userId;
	this->name = name;
	this->numIc = numIc;
	this->username = username;
	this->password = password;
	this->phoneNum = phoneNum;
	this->email = email;
	this->address = address;
	this->usertype = usertype;
}


bool Account::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM user WHERE username=? AND password=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			userId = db.res->getInt("userId");
			name = db.res->getString("name");
			numIc = db.res->getString("numIc");
			phoneNum = db.res->getString("phoneNum");
			username = db.res->getString("username");
			password = db.res->getString("password");
			email = db.res->getString("email");
			address = db.res->getString("address");

			// Retrieve the role from the database
			usertype = db.res->getString("usertype");
			//check if user is admin
			if (usertype == "admin") {
				isAdmin = true;  
			}
			else if (usertype == "user") {
				isAdmin = false;  
			}
			
		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}
void Account::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into user (username,password,name, email, phoneNum, numIc, address, usertype) VALUES (?,?,?,?,?,?,?,?)");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, name);
	db.stmt->setString(4, email);
	db.stmt->setString(5, phoneNum);
	db.stmt->setString(6, numIc);
	db.stmt->setString(7, address);
	db.stmt->setString(8, usertype);
	db.QueryStatement();
	db.~DBConnection();
}

void Account::update() {

	DBConnection db;
	db.prepareStatement("UPDATE user SET username=?, password=?, name=?, email=?, phoneNum=?, numIc=?, address=? WHERE userId=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, name);
	db.stmt->setString(4, email);
	db.stmt->setString(5, phoneNum);
	db.stmt->setString(6, numIc);
	db.stmt->setString(7, address);
	db.stmt->setInt(8, userId);
	db.QueryStatement();
	db.~DBConnection();

}

void Account::remove() {
	DBConnection db;
	db.prepareStatement("DELETE FROM user WHERE userId=?");
	db.stmt->setInt(1, userId);
	db.QueryStatement();

	db.~DBConnection();
}

// to check user role
std::string Account::getRole()
{
	return usertype;
}
//to get usertype == user
void Account::setUsertype(const std::string& type) {
	usertype = type;
}

Account::~Account() {

}



// getter setter for password
// since password is private, only way to change value from outside is via this function
// which will encrypt the string 
void Account::setPassword(string pass) {
	password = encrypt(pass);

}
string Account::getPassword() {
	return password;
}

bool Account::MatchPasswordWith(std::string plainText)
{
	return isMatch(password, plainText);
}

// to check if a string matches with the encrypted password



// simple shifting encryption where the character are shifted by its ASCII decimal code depending on its index
string Account::encrypt(string input) {
	string ciphertext = "";
	for (int i = 0; i < input.length(); i++) {
		ciphertext += toChar(input[i] + ((i ^ 2 + 1) * input.length()));
	}
	return ciphertext;
}

// since we are using our own simple encryption, just re ecnrypt the target plain text and compare with the encrypted text
bool Account::isMatch(string encrypted, string testText) {
	return (bool)(encrypt(testText) == encrypted);
}

char Account::toChar(int asciDecimal) {
	// convert int to reeadbale char based on ASCII
	// characters in ASCII decimal are 32 (space) ~ 125 (~)
	while (asciDecimal < 33) {
		asciDecimal = asciDecimal + asciDecimal + 1;
	}
	while (asciDecimal > 125) {
		asciDecimal = (asciDecimal % 125) + 32;
	}
	return (char)asciDecimal;
}
