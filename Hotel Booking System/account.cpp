#include "Account.h"
#include <ctime>
#include "DBConnect.h" 
using namespace std;

Account::Account() {
	//initialize
	customerID = 0;
	username = "";
	password = "";
	email = "";
	numIC = "";
	phoneNum = "";
	name = "";
	address = "";
}


Account::Account(int customerID, std::string  numIC, std::string  phoneNum, std::string username, std::string password, std::string email, std::string name, std::string address) {
	this->customerID = customerID;
	this->name = name;
	this->numIC = numIC;
	this->username = username;
	this->password = password;
	this->phoneNum = phoneNum;
	this->email = email;
	this->address = address;
}


bool Account::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM customer WHERE username=? AND password=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			customerID = db.res->getInt("customerID");
			name = db.res->getString("name");
			numIC = db.res->getString("numIC");
			phoneNum = db.res->getString("phoneNum");
			username = db.res->getString("username");
			password = db.res->getString("password");
			email = db.res->getString("email");
			address = db.res->getString("address");
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
	db.prepareStatement("Insert into customer (username,password,name, email, phoneNum, numIC, address) VALUES (?,?,?,?,?,?,?)");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, name);
	db.stmt->setString(4, email);
	db.stmt->setString(5, phoneNum);
	db.stmt->setString(6, numIC);
	db.stmt->setString(7, address);
	db.QueryStatement();
	db.~DBConnection();
}

void Account::update() {

	DBConnection db;
	db.prepareStatement("UPDATE customer SET username=?, password=?, name=?, email=?, phoneNum=?, numIC=?, address=? WHERE customerID=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, name);
	db.stmt->setString(4, email);
	db.stmt->setString(5, phoneNum);
	db.stmt->setString(6, numIC);
	db.stmt->setString(7, address);
	db.stmt->setInt(8, customerID);
	db.QueryStatement();
	db.~DBConnection();

}

void Account::remove() {
	DBConnection db;
	db.prepareStatement("DELETE FROM customer WHERE customerID=?");
	db.stmt->setInt(1, customerID);
	db.QueryStatement();

	db.~DBConnection();
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
