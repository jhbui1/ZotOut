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


class Member_DB{

private:
	
	/*
	 * Inserts
	 */
	void new_member();
public:
	Member_DB();
};


#endif




