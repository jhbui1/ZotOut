#include <iostream>
#include <algorithm> 
#include <mysql.h>
#include <iomanip>
#include <locale>

#include "helpers.h"

using namespace std;

void printSep(int n){
	cout << "\n\n\n\n\n";

}

string removeSpaces(string str){
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

void MYSQL_STMT_INIT(MYSQL* conn, MYSQL_STMT* stmt, string s, int slen) {
	stmt = mysql_stmt_init(conn);
	if (!stmt)
	{
		fprintf(stderr, " mysql_stmt_init(), out of memory\n");
		exit(0);
	}
	if (mysql_stmt_prepare(stmt, s.c_str(), slen))
	{
		fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
		exit(0);
	}
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

void printFields(int num_fields, MYSQL_FIELD* fields,int* field_widths) {
	for (int i = 0; i < num_fields; i++) {
		cout <<setw(field_widths[i])<< fields[i].name << " | ";
	}
	cout << endl;
}

string fieldLen(int len, string field) {
	string s;
	while (1) {
		cout << "Enter " << field << endl;
		getline(cin, s);
		cin.clear();
		cin.ignore(1000000, '\n');
		if (s.length() <= len) {
			return s;
		}
		else {
			cout << "Entry should be less than " << len << " characters. Please try again." << endl;
		}
	}
}

void lower(string& target){
	transform(target.begin(),target.end(), target.begin(),
		[](unsigned char c) { return tolower(c); });

}

void bind_var(MYSQL_BIND* bind, enum_field_types type, void* buffer, bool* isnull, unsigned long len, bool num_type) {
	bind->buffer_type = type;
	bind->buffer = buffer;
	bind->is_null = isnull;
	if (!num_type) {
		bind->buffer_length = len;
	}

}

