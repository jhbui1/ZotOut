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

class Member_DB{

private:
	MYSQL* conn;
	/*
	 * Inserts entered data into database
	 */
	
public:
	Member_DB();
	~Member_DB();
	void insertMember();
	void showMembers();

};


#endif




