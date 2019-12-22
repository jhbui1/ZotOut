#include <string>
#include <mysql.h>
#include <iostream>
#include <stdio.h>

#include "helpers.h"
#include "employee.h"

using namespace std;

Employee_DB::Employee_DB(MYSQL* conn):conn(conn) {
	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employees( \
							emp_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,\
							first_name VARCHAR(30) NOT NULL,\
							last_name VARCHAR(30) NOT NULL,\
							salary DECIMAL(13,2) NOT NULL);");

	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employee_member(\
							emp_id INT UNSIGNED NOT NULL,\
							member_id INT UNSIGNED UNIQUE NOT NULL,\
							FOREIGN KEY(emp_id) REFERENCES employees(emp_id),\
							FOREIGN KEY(member_id) REFERENCES gym_member(member_id),\
							PRIMARY KEY(emp_id, member_id));");
	cout << "mem constructed" << endl;

}

void printMVP(vector<string> result) {
	cout << "Most valuable employees" << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i]<<endl;
	}
}

void Employee_DB::showOps() {
	int n;
	cout << "\t1: Add Employee" << endl;
	cout << "\t2: Show Employees" << endl;
	cout << "\t3: Delete Employees" << endl;
	cout << "\t4: Show Emp of the Month" << endl;
	cin >> n;
	switch (n) {
		case 1:
			this->addEmployee();
			break;
		case 2:
			this->showEmployees();
			break;
		case 3:
			this->deleteEmp();
			break; 
		case 4:
			vector<string> result = this->mostValuableEmp();
			printMVP(result);
			break;
			
	}


}

void Employee_DB::showEmployees() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	string query = "SELECT emp_id,first_name,last_name,FORMAT(salary,2) FROM employees";
	res = MYSQL_QUERY(this->conn, query);

	
	printf("%*s | %*s | %*s | %*s\n", 10, column_names[0], 30, column_names[1], 30, column_names[2], 15, column_names[3]);

	while (row = mysql_fetch_row(res))
	{
		
		cout << "---------------------------------------------------------------------------------------------------\n";
		printf("%*s | %*s | %*s | %*s\n",10,row[0],30,row[1],30,row[2],15,row[3]);
	}

	printSep(4);
	

}


void addEmployeePrompt(string* fn,string* ln, double* salary) {
	cout << "Enter first name:" << endl;
	cin >> *fn;
	cout << "Enter last name:" << endl;
	cin >> *ln;
	cout << "Enter salary: " << endl;
	cin >> *salary;

}

void Employee_DB::addEmployee() {
	string fn, ln;
	double salary;
	char buff[200];
	addEmployeePrompt(&fn, &ln, &salary);
	sprintf_s(buff, "INSERT INTO employees(first_name, last_name, salary) VALUE('%s', '%s', '%.2f');",fn,ln,salary);
	MYSQL_QUERY(this->conn, buff);

}



void Employee_DB::addMemEmp(int mem_id) {
	MYSQL_RES* res;
	int e_id;
	char buff[300];
	
	cout << "Enter your employee id:" << endl;
	cin >> e_id;
	sprintf_s(buff, "INSERT INTO employee_member (emp_id,member_id) VALUE('%d', '%d'); ",e_id, mem_id);

	res= MYSQL_QUERY(this->conn, buff);
	
}


void Employee_DB::deleteEmp() {
	int id;
	char buff[400];
	cout << "Enter the id to delete\n" << endl;
	cin >> id;
	sprintf_s(buff, "DELETE FROM employees WHERE emp_id =%d;", id);
	MYSQL_QUERY(this->conn, buff);
}


vector<string> Employee_DB::mostValuableEmp() {
	string query = "SELECT first_name, last_name, count(*)\
					FROM employee_member NATURAL JOIN employees \
					GROUP BY emp_id\
					ORDER BY 3\
					";
	MYSQL_RES* res;
	MYSQL_ROW row;
	vector<string> r;
	string result ="";
	res = MYSQL_QUERY(this->conn, query);
	int mvp_count=-1;
	//Handle tie in amount of members registered 
	while (row = mysql_fetch_row(res)) {
		int registered = stoi(row[2]);
		cout << registered << " " << row[0] << endl;
		if (registered < mvp_count) {
			break;
		}else {
			//Add name to result
			result += row[0];
			result += " ";
			result += row[1];
			r.push_back(result);
			result = "";

			if (registered > mvp_count ) {
				//Update mvp count to compare next counts to
				mvp_count = registered;
			}
		}
	}
	return r;
}

