/*
 * member.h
 *
 *  Created on: Oct 18, 2019
 *      Author: jbui4
 *
 */
#ifndef MEMBER_H
#define MEMBER_H
/*
 * Member DB controller maintains connection to mySQL server and has functions for
 * updating/inserting member records.
 *
 */


#include <mysql.h>
#include <array>
#include <string>

#include "db_man.h"

using namespace std;

class Member_DB :public DB_MANAGER {

private:
	array<string,5> column_names{"First name", "Last name", "E-mail","Renewal date", "Gender"};
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
	*/
	Member_DB();
	
	/*
	 * Inserts entered data into database
	 */
	void insertMember();
	
	/*
		Searches for corresponding record file based on selected parameters 
	*/
	void updateMember();
	
	/*
		Shows all members in database
	*/

	void showMembers();

};


#endif




