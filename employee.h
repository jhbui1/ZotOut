#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <mysql.h>


/*
	Maintins tables for employee information and 
	has functions to evaluate employee performance. 
*/

class Employee_DB{

private:
	MYSQL* conn;

	
	///*  Names of all columns in employee table in printable format   */
	//array<string, 3> column_names {"First Name", "Last Name","Salary"};
	///*  True column names of member table    */
	//array<string, 3> column_names_db {"first_name","last_name","salary" };
	
	
public:
	/*
	@param conn, a mysql connection maintained by a DB manager object
	*/
	Employee_DB(MYSQL* conn);
	/*
	
	*/

	
	/*
		Searches the employee-member database for the employee with
		the most occurences, i.e the one who has registered the most 
		members.
	
	*/
	


};

#endif