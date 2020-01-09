#pragma once

#include <mysql.h>
#include <string>

using namespace std;

/*
	Handles credential prompting,validation and encryption for storage
*/
class Login {
private:
	MYSQL* conn;
	string user_name;
	string pwd;
	string user_level;
	int emp_id;

	/*
		Prompts for pwd while preventing over the shoulder attack
		Returns plain text password
		Assumes terminal computer is separate for database server and password entered is to be sent wirelessly to server
	*/
	string takeCredentials();

	/*
		Verifies that username exists and hashed pwd matches	
	*/
	bool validate();
public:

	//Subject to change per session basis
	string getUserName();
	string getPWD();
	string getUserLevel();
	int getID();

	Login(MYSQL* conn);

	/*
		Default constructor, used to access login methods by employee
	*/
	Login();


	/*
		Prompts user for password and replaces with
		@param registration bool determining if method is being used for verification or registration
			if latter, need to prompt for reentry until pwd's match
	*/
	string getPWD(bool resgistration);

	/*
		Returns hashed password (already salted by bcrypt) to be inserted into database
	*/
	string hashSalt(string pwd);

};