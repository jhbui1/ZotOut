#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <mysql.h>

using namespace std;


/**
 * Prints separator of empty lines between records,views etc.
 *
 * @param n number of new lines to print
 */
void printSep(int n);
/*
	Removes spaces from str
	@param str, string to remove spaces from
*/
string removeSpaces(string str);

/*
	Provides error checking for a query
	@param s,query string 
*/

MYSQL_RES* MYSQL_QUERY(MYSQL* conn, string s);

void printFields(int num_fields, MYSQL_FIELD* fields,int* field_widths);

string fieldLen(int len, string field);
#endif
