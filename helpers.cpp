#include <iostream>
#include <algorithm> 
#include <mysql.h>

#include "helpers.h"

using namespace std;

void printSep(int n){
	cout << "\n\n\n\n\n";

}

string removeSpaces(string str){
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

MYSQL_RES* MYSQL_QUERY(MYSQL* conn,string s) {
	MYSQL_RES* res;
	MYSQL_ROW row;

	const char* q = s.c_str();
	int qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		return res;

	}
	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}
}



