#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <mysql.h>


/*
	Maintins tables for employee information and 
	has functions to evaluate employee performance. 
*/

using namespace std;

class Employee_DB{

private:
	MYSQL* conn;

	/*  names of all columns in employee table in printable format   */
	int columns = 4;
	string column_names[4] = {"ID","First name", "Last name","Salary"};
	/*  true column names of member table    */
	string db_col_names[4] = { "emp_id","first_name","last_name","salary" };
	
	
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
	
	string  mostValuableEmp();

	/*
		
	*/
	void deleteEmp();
};

#endif