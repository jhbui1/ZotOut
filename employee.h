#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <mysql.h>

#include "login.h"

/*
	Maintins tables for employee information and 
	has functions to evaluate employee performance. 
*/

using namespace std;

class Employee_DB{

private:
	MYSQL* conn;
	Login login_mgr;
	/*  names of all columns in employee table in printable format   */
	int field_widths[6] = { 10,30,30,15,30,30 };
	
	
public:
	/*
	@param conn, a mysql connection maintained by a DB manager object
	*/
	Employee_DB(MYSQL* conn);

	/*
		displays employee db related options
	*/

	void showOps();

	/*
	shows all employees
	*/

	void showEmployees();

	/*
	Prompts user to add employee
	*/
	void addEmployee();

	/*
		Adds a relation between member and employee
		@param mem_id member to be related to
	*/
	void addMemEmp(int mem_id);
	
	/*
		Searches the employee-member database for the employee with
		the most occurences, i.e the one who has registered the most 
		members.
	
	*/
	
	void  mostValuableEmp();

	/*
		Deletes emp with given id
	*/
	void deleteEmp();
};

#endif