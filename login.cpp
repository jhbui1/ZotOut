#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
  
#include "login.h"
#include "helpers.h"
#include "libbcrypt/include/bcrypt/BCrypt.hpp"

#define BKSP 8
#define TAB 9
#define ENTER 13
#define LF 10

using namespace std;

Login::Login(MYSQL* conn) :conn(conn) {
	this->takeCredentials();
}

Login::Login() {
	;
}

string Login::getUserName() {
	return this->user_name;
}
string Login::getPWD() {
	return this->pwd;
}
string Login::getUserLevel() {
	return this->user_level;
}
int Login::getID() {
	return this->emp_id;
}

string Login::hashSalt(string pwd) {
	string hash = BCrypt::generateHash(pwd);
	return hash;

}


bool Login::validate() {
	MYSQL_RES* res;
	MYSQL_ROW row;

	//Verify that username exists
	string query = "SELECT * FROM employees WHERE user_name = '";
	query += this->user_name;
	query += "';";
	res = MYSQL_QUERY(this->conn, query);
	if (mysql_num_rows(res)==0) {
		cout << "Username does not exist" << endl;
		return false;
	}
	else if (mysql_num_rows(res) > 1) {
		cout << "Error: Duplicate user names contact sysadmin" << endl;
	}
	

	//Validate pwd and set 
	row = mysql_fetch_row(res);
	string hash = row[5];
	if (BCrypt::validatePassword(this->pwd,hash)) {
		
		this->emp_id = atoi(row[0]);
		this->user_level = row[6];
		return true;
	}
	else {
		cout << "Incorrect password." << endl;
	}
	

	return false;


	
}

string Login::getPWD(bool registration) {
	char ch;
	int i = 0;
	char pwd[100];

	cout << "Password: ";

	while (true) {
		ch = _getch(); //non standard function which immediately retrieves char without blocking untill enter
		if (ch == ENTER || ch == TAB || ch == LF ) {
			pwd[i] = '\0';
			break;
		}
		else if (ch == BKSP) {
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		}
		else {
			pwd[i++] = ch;
			cout << "* \b";
		}
	}
	if (registration) {
		cout << "\nPlease confirm password." << endl;
		string confirm = this->getPWD(false);
		if (confirm != pwd) {
			cout << "Passwords do not match." << endl;
			this->getPWD(true);
		}
	}
	cout << endl;
	string result(pwd);
	return result;

}

string Login::takeCredentials() {
	string level;
	while (true) {//While the entered credentials are invalid
		cout << "Enter username: ";
		CIN(this->user_name);
		//Separate function since input consumption is unique and must prevent over the shoulder attack.
		this->pwd = getPWD(false);
		if (this->validate()) {
			break;
		}

	}
	return level;
}