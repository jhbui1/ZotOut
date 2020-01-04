#include <iostream>
#include <iomanip>
#include <string>

#include "helpers.h"
#include "equipment.h"


using namespace std;



Equipment_DB::Equipment_DB(MYSQL* conn):conn(conn) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL_QUERY(this->conn, "CREATE TABLE IF NOT EXISTS equipment( \
							eq_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,\
							info VARCHAR(30) NOT NULL,\
							avail ENUM('Y','N') NOT NULL DEFAULT 'Y',\
							eq_type ENUM ('cardio','counter','weight'));");
	//If table is empty, initialize equipment
	res=MYSQL_QUERY(this->conn,"SELECT COUNT(*) FROM equipment");
	row = mysql_fetch_row(res);
	if (row&&atoi(row[0]) == 0) {
		this->initializeEquip();
	}
}


/*
	Show available operations and execute corresponding method
*/

void Equipment_DB::showOps() {
	int n;
	cout << "\t1: Show Equipment" << endl;
	cout << "\t2: Add Equipment" << endl;
	cout << "\t3: Referesh Availability" << endl;
	cout << "\t4: Update Availability" << endl;
	CIN(n);
	switch (n) {
	case 1:
		this->showEq();
		break;
	case 2:
		this->insertEquip();
		break;
	case 3:
		this->clearAvailability();
		break;
	case 4:
		this->checkOut();
		break;

	}

}



void Equipment_DB::initializeEquip() {
	string desc[3] = { "band", "bike","barbell" };
	string type[3] = { "counter","cardio","weight" };
	string query = "INSERT INTO equipment (info,eq_type) VALUES ";
	for (int i = 0; i < 10; i++) {
		char buff[200];
		sprintf_s(buff, "('%s','%s'),",desc[i%2],type[i%2]);
		query += buff;
	}
	query.pop_back();
	query += ";";
	MYSQL_QUERY(this->conn, query);

}




void Equipment_DB::showEq() {

	string query = "SELECT * FROM equipment;";
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL_FIELD* fields;

	//Determine if category is desired
	string category;
	cout << "Enter category (cardio,weight,counter) or enter to continue..." << endl;
	getline(cin, category);//consumes any leftover \n's

	do{//do while because assume cin contains \n (must have been entered to get to this menu)
		getline(cin, category);
		if (!category.empty())break;
	} while (category != "");
	lower(category);

	for (int i = 0; i < this->num_cats; i++) { //Check if entered category is valid
		if (categories[i] == category) {
			char buff[200];
			query.pop_back();
			sprintf_s(buff, " WHERE eq_type = '%s';", category);
			query += buff;
			break;

		}
	}

	//Fetching and printing fields
	res = MYSQL_QUERY(this->conn, query);
	int num_fields = mysql_num_fields(res);
	fields = mysql_fetch_fields(res);
	printFields(num_fields, fields,this->field_widths);

	while (row = mysql_fetch_row(res)) {

		for (int i = 0; i < num_fields; i++) {
			cout <<setw(this->field_widths[i])<< row[i] << " | ";
		}
		cout << endl;
	}
}

void Equipment_DB::insertEquip() {
	
	string query = "INSERT INTO equipment (info,eq_type) VALUE ";
	string type,desc;
	type=fieldLen(30, "type");
	desc=fieldLen(10, "desc");

	if (type.length() && desc.length()) {
		char buff[200];
		sprintf_s(buff, "('%s','%s');", desc, type);
		query += buff;
		MYSQL_QUERY(this->conn, query);
	}
}

void Equipment_DB::clearAvailability() {
	string query = "UPDATE equipment SET avail = 'Y'";
	MYSQL_QUERY(this->conn, query);
}

void Equipment_DB::checkOut() {
	int id;
	cout << "Enter id to checkout... " << endl;
	CIN(id);
	string query = "UPDATE equipment SET avail = 'N' WHERE eq_id = ";
	query += to_string(id);
	query += ";";
	cout << query;
	MYSQL_QUERY(this->conn,query);
	
}
