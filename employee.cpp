#include <string>
#include <mysql.h>
#include <iostream>
#include <stdio.h>

#include "helpers.h"
#include "employee.h"

using namespace std;

Employee_DB::Employee_DB(MYSQL* conn) {
	this->conn = conn;
	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employees( \
							emp_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,\
							first_name VARCHAR(30) NOT NULL,\
							last_name VARCHAR(30) NOT NULL,\
							salary DECIMAL(13,2) NOT NULL);");

	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employee_member( \
							emp_id INT UNSIGNED NOT NULL,\
							member_id INT UNSIGNED NOT NULL);");

}

void Employee_DB::show_ops() {
	int n;
	cout << "\t1: Add Employee" << endl;
	cin >> n;
	switch (n) {
	case 1://add emp
		this->addEmployee();
		break;
	}

}

void Employee_DB::showEmployees() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	string query = "SELECT * FROM employees";
	res = MYSQL_QUERY(this->conn, query);


	while (row = mysql_fetch_row(res))
	{
		printf("ID: %s, FN: %s, LN: %s\n", row[0], row[1], row[2]);
	}

	
	printSep(4);
	

}


void addEmployeePrompt(string* fn,string* ln, float* salary) {
	cout << "Enter first name:" << endl;
	cin >> *fn;
	cout << "Enter last name:" << endl;
	cin >> *ln;
	cout << "Enter salary: " << endl;
	cin >> *salary;

}

void Employee_DB::addEmployee() {
	string fn, ln;
	float salary;
	char buff[200];
	addEmployeePrompt(&fn, &ln, &salary);
	sprintf_s(buff, "INSERT INTO employees(first_name, last_name, salary) VALUE('%s', '%s', '%f');",fn,ln,salary );
	MYSQL_QUERY(this->conn, buff);

}



void Employee_DB::addMemEmp(int mem_id) {
	MYSQL_RES* res;
	int e_id;
	char buff[100];
	
	cout << "Enter your employee id:" << endl;
	cin >> e_id;
	sprintf_s(buff, "SELECT * FROM employees where emp_id = %d", e_id);
	while (mysql_num_rows(MYSQL_QUERY(this->conn, buff)) == 0) {
		cout << "Enter your employee id:" << endl;
		cin >> e_id;
		sprintf_s(buff, "SELECT * FROM employees where emp_id = %d", e_id);
	}
	sprintf_s(buff, "INSERT INTO employee_member VALUE('%d', '%d');",e_id,mem_id);
	res= MYSQL_QUERY(this->conn, buff);
	
}

string Employee_DB::mostValuableEmp() {

}

