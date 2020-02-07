#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <mysql.h>
#include <limits>
#include <typeinfo>

using namespace std;


void MYSQL_STMT_INIT(MYSQL* conn, MYSQL_STMT*& stmt, string s, int slen);

/*
	Provides error checking for a query
	@param s,query string
	returns null if failed
*/

MYSQL_RES* MYSQL_QUERY(MYSQL* conn, string s);

/*
	Modular initialization of bind structures.
*/

void bind_var(MYSQL_BIND* bind, enum_field_types type, void* buffer, bool* isnull, unsigned long len, bool num_type);
#endif

/*
	Error check for binding of buffers to parameters and execution
	return bool for success
*/
bool MYSQL_STMT_BIND_EXEC(MYSQL_STMT* stmt, MYSQL_BIND* bind);



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
	Prints the field names of a query result
	@param num_fields, the number of fields in the result
	@param fields sql struct ptr to array of fields 
	@param field_widths user defined char widths designated to max width of the value of each field, i.e not the width of the field name.

*/
void printFields(int num_fields, MYSQL_FIELD* fields,int* field_widths);
/*
	Repeatedly prompts user for string value for field while its length is g.t len
*/
string fieldLen(int len, string field);

/*
	converts target to lower case
*/
void lower(string& target);

/*
	Provide error handling for cin/buffer clearing
*/
template<typename T>
void CIN(T& input) {
	while (true) {
		if (cin >> input) {
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			break;
		}
		else {
			cout << "Entry is of incorrect type. Please enter a " << typeid(input).name() << endl;
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
	}
}

