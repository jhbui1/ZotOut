/*
 * member.cpp
 *
 *  Created on: Oct 19, 2019
 *      Author: jbui4
 */

#include <string>
#include <iostream>
#include <stdio.h>

#include "member.h"

using namespace std;

Member_DB::Member_DB(){
	this->conn = mysql_init(0);
	this->conn = mysql_real_connect(this->conn, "localhost", "root", "35122jhb", "zotout", 3306, NULL, 0);
}

Member_DB::~Member_DB() {
	mysql_close(this->conn);
}

void Member_DB::insertMember() {
	string fn,ln,email,date;
	char gender;
	cout << "Enter first name:" << endl;
	cin >> fn;
	cout << "Enter last name:" << endl;
	cin >> ln;
	cout << "Enter email: " << endl;
	cin >> email;
	cout << "Enter date(YYYY-MM-DD): " << endl;
	cin >> date;
	cout << "Enter gender: " << endl;
	cin >> gender;
	char buff[300];
	sprintf_s(buff, "INSERT INTO gym_member(first_name, last_name, email, rn_date, sex) VALUE('%s', '%s', '%s', '%s', '%c');", fn, ln, email, date, gender);
	mysql_query(this->conn,buff);
}

void Member_DB::showMembers() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	string query ="SELECT * FROM gym_member"; 
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			printf("ID: %s, FN: %s, LN: %s\n", row[0], row[1], row[2]);
		}

	}else{
		cout << "Query failed: " << mysql_error(conn) << endl;
	}


}

