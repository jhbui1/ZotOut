#ifndef MEMBER_H
#define MEMBER_H



#include <mysql.h>
#include <array>
#include <string>
#include "employee.h"


using namespace std;

/*
 * Member DB controller has functions for
 * updating/inserting member records.
 *
 */

class Member_DB{

private:
	MYSQL* conn;
	/*  Names of all columns in member table in printable format   */
	int col_widths[5] = { 30,30,30,10,1 };
	array<string,5> column_names{"First name", "Last name", "E-mail","Renewal date", "Gender"};
	/*  True column names of member table    */
	array<string,5> column_names_db{ "first_name","last_name","email","rn_date","sex" };
	
/*
	Asks if user wants to update given attr
	returns query portion of list of attributes to update and values to update with
*/
	string updateMemberPrompt();
	
public:
	/**
		Checks if relevant tables exist.
		Creates otherwise.
		@param conn, a mysql connection maintained by a DB manager object
	*/
	Member_DB(MYSQL* conn);
	
	/*
		Prints available operations
	*/

	void showOps(Employee_DB& emp_db);

	/*
		Used for finding id of most recently inserted member 
	*/

	int lastRow();

	/*
	 * Inserts entered data into database
	 @return, id of the newly inserted mebmber 
	 */
	int insertMember();
	
	
	/*
		Searches for corresponding record file based on selected parameters 
	*/
	void updateMember();
	
	/*
		Shows all members in database
	*/

	void showMembers();

	/*
		prompt for id and delete corresponding member
	*/
	void deleteMem();

	/*
		adds entry to member_checkin table for member
	*/
	void checkIn();

	/*
		Finds member with most checkins 
	*/
	void mostFrequentMember();
};


#endif




