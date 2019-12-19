/*
 * member.cpp
 *
 *  Created on: Oct 19, 2019
 *      Author: jbui4
 */


#include <iostream>
#include <stdio.h>
#include <array>
#include <ctype.h>
#include "member.h"
#include "helpers.h"

using namespace std;

Member_DB::Member_DB(MYSQL* conn){
	this->conn = conn;
	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS gym_member( \
							member_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,\
							first_name VARCHAR(30) NOT NULL,\
							last_name VARCHAR(30) NOT NULL,\
							email VARCHAR(40) NULL,\
							rn_date DATE NOT NULL,\
							sex ENUM('M','F') NOT NULL);");
}

void Member_DB::showOps(Employee_DB& emp_db) {
	cout << "\t1:Add Member" << endl;
	cout << "\t2:Update/View Member file" << endl;
	cout << "\t3:Show All Members" << endl;
	cout << "\t4:Delete Member" << endl;
	cout << "Enter the number for your option: " << endl;

	int n,new_id = -1;
	cin >> n;
	switch (n) {
		case 1:	
			new_id = this->insertMember();
			if (new_id == -1) break;
			emp_db.addMemEmp(new_id);
			break;
		case 2:
			this->updateMember();
			break;
		case 3:
			this->showMembers();
			break;
		case 4:
			this->deleteMem();
			break;

	}
}

/*
	Takes pointers to strings that store values to be inserted into member db
*/

void insertMemberPrompt(string* fn,string *ln,string * email, string* date, char* gender) {
	cout << "Enter first name:" << endl;
	cin >> *fn;
	cout << "Enter last name:" << endl;
	cin >> *ln;
	cout << "Enter email: " << endl;
	cin >> *email;
	cout << "Enter date(YYYY-MM-DD): " << endl;
	cin >> *date;
	cout << "Enter gender: " << endl;
	cin >> *gender;

}

/*
	returns max id

*/
int Member_DB::lastRow() {
	MYSQL_RES* res;
	MYSQL_ROW row;

	string query = "SELECT MAX(member_id) FROM gym_member;";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
			return atoi(row[0]);

	}
	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}
}

int Member_DB::insertMember() {
	string fn,ln,email,date;
	char gender;
	char buff[300];

	insertMemberPrompt(&fn, &ln, &email, &date, &gender);
	
	sprintf_s(buff, "INSERT INTO gym_member(first_name, last_name, email, rn_date, sex) VALUE('%s', '%s', '%s', '%s', '%c');", fn, ln, email, date, gender);
	mysql_query(this->conn,buff);
	this->showMembers();
	return this->lastRow();
}


string Member_DB::updateMemberPrompt() {
	string result = "";
	int len = this->column_names.size();
	for (int i = 0; i < len;i++) {
		string new_val,upper;
		cout << "Update " + column_names[i] + " ? (Enter new value or n to continue or q to quit)" << endl;
		cin >> new_val;
		removeSpaces(new_val);
		for (string::iterator it = new_val.begin(); it != new_val.end(); it++) {
			upper += toupper(*it);
		}
		if (upper == "Q") {
			if(result.length()>0) return result;
			else break;
		}
		if (upper!="N") {
			if (result.length() > 0) {
				result += ",";
			}
			result+=column_names_db[i] + " = '" + new_val+"'";
		}
	}

	return result;
}

void Member_DB::updateMember() {
	MYSQL_RES* res;

	int qstate, qid;

	cout << "Enter member ID:" << endl;

	cin >> qid; if(cin.fail());
	string s[4];
	char gender;
	
	string update_attrs = updateMemberPrompt();
	char buff[1000];
	const char* attrs_cstr = update_attrs.c_str();
	sprintf_s(buff, "UPDATE gym_member SET %s WHERE MEMBER_ID =  %d", attrs_cstr, qid);
	qstate = mysql_query(conn, buff);
	if (!qstate) {
		res = mysql_store_result(conn);
	}
	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}
	printSep(5);

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
	printSep(4);

}

void Member_DB::deleteMem() {
	int id;
	char buff[400];
	cout << "Enter the id to delete\n" << endl;
	cin >> id;
	sprintf_s(buff, "DELETE FROM gym_member WHERE member_id =%d;", id);
	MYSQL_QUERY(this->conn, buff);
}

