#include <string>
#include <mysql.h>
#include <iostream>
#include <stdio.h>

#include "helpers.h"
#include "employee.h"
#include "login.h" //getpwd

using namespace std;

Employee_DB::Employee_DB(MYSQL* conn,Login login):conn(conn),login_mgr(login) {
	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employees( \
							emp_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,\
							first_name VARCHAR(30) NOT NULL,\
							last_name VARCHAR(30) NOT NULL,\
							salary DOUBLE NOT NULL,\
							user_name VARCHAR(30) NOT NULL UNIQUE,\
							pwd VARCHAR(100) NOT NULL,\
							lvl ENUM('associate','manager'),\
							plain VARCHAR(60) NOT NULL);");

	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employee_member(\
							emp_id INT UNSIGNED NOT NULL,\
							member_id INT UNSIGNED UNIQUE NOT NULL,\
							FOREIGN KEY(emp_id) REFERENCES employees(emp_id),\
							FOREIGN KEY(member_id) REFERENCES gym_member(member_id),\
							PRIMARY KEY(emp_id, member_id));");

}

void printMVP(vector<string> result) {
	cout << "Most valuable employees" << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i]<<endl;
	}
}

bool Employee_DB::mgrCheck() {
	if (this->login_mgr.getUserLevel() != "manager") {
		cout << "Access denied. Manager permissions required." << endl;
		return false;
	}
	else {
		return true;
	}
}

void Employee_DB::showOps() {
	int n;
	cout << "\t1: Add Employee" << endl;
	cout << "\t2: Show Employees" << endl;
	cout << "\t3: Delete Employees" << endl;
	cout << "\t4: Show Emp of the Month" << endl;
	CIN(n); 
	switch (n) {
		case 1:
			//if(this->mgrCheck())
				this->addEmployee();
			break;
		case 2:
			this->showEmployees();
			break;
		case 3:
			//if (this->mgrCheck())
				this->deleteEmp();
			break; 
		case 4:
			this->mostValuableEmp();
			break;
			
	}


}

void Employee_DB::showEmployees() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL_FIELD* fields;
	string query = "SELECT emp_id,first_name,last_name,FORMAT(salary,2) FROM employees";
	
	res = MYSQL_QUERY(this->conn, query);
	int num_fields = mysql_num_fields(res);
	fields = mysql_fetch_fields(res);
	printFields(num_fields, fields, this->field_widths);

	while (row = mysql_fetch_row(res))
	{
		
		cout << "---------------------------------------------------------------------------------------------------\n";
		printf("%*s | %*s | %*s | %*s\n",10,row[0],30,row[1],30,row[2],15,row[3]);
	}

	printSep(4);
	

}



void Employee_DB::addEmployee() {
	MYSQL_STMT* stmt=NULL;
	MYSQL_BIND  bind[7];
	string fn, ln, uname, pwd, lvl, salt;
	double salary;
	
	//Prompt for employee info
	fn = fieldLen(30, "first name");
	ln = fieldLen(30, "last name");
	cout << "Enter salary: " << endl;
	CIN(salary);
	uname = fieldLen(30, "username");

	string plain_pwd=this->login_mgr.getPWD(true);
	pwd = this->login_mgr.hashSalt(plain_pwd);

	lvl = fieldLen(10, "level (associate or manager)");//TODO: verify that user has priveelege to enter elevated level

	string insert_query = "INSERT INTO employees(first_name, last_name, salary, user_name, pwd, lvl,plain) VALUE(?, ?, ?, ?, ?, ?, ?)";
	
	MYSQL_STMT_INIT(this->conn, stmt, insert_query, insert_query.length());

	memset(bind, 0, sizeof(bind));
	bind_var(&bind[0], MYSQL_TYPE_STRING, (char*)fn.c_str(), 0, fn.length(), 0);
	bind_var(&bind[1], MYSQL_TYPE_STRING, (char*)ln.c_str(), 0, ln.length(), 0);
	bind_var(&bind[2], MYSQL_TYPE_DOUBLE, (char*)&salary, 0, 0, 1);
	bind_var(&bind[3], MYSQL_TYPE_STRING, (char*)uname.c_str(), 0, uname.length(), 0);
	bind_var(&bind[4], MYSQL_TYPE_STRING, (char*)pwd.c_str(), 0, pwd.length(), 0);
	bind_var(&bind[5], MYSQL_TYPE_STRING, (char*)lvl.c_str(), 0, lvl.length(), 0);
	bind_var(&bind[6], MYSQL_TYPE_STRING, (char*)plain_pwd.c_str(), 0, plain_pwd.length(), 0);


	MYSQL_STMT_BIND_EXEC(stmt, bind);
	
	

}



void Employee_DB::addMemEmp(int mem_id) {
	MYSQL_RES* res;
	int e_id;
	char buff[300];
	
	e_id = this->login_mgr.getID();
	sprintf_s(buff, "INSERT INTO employee_member (emp_id,member_id) VALUE('%d', '%d'); ",e_id, mem_id);

	res= MYSQL_QUERY(this->conn, buff);
	
}


void Employee_DB::deleteEmp() {
	int id;
	char buff[400];
	cout << "Enter the id to delete\n" << endl;
	CIN(id);
	sprintf_s(buff, "DELETE FROM employees WHERE emp_id =%d;", id);
	MYSQL_QUERY(this->conn, buff);
}


void Employee_DB::mostValuableEmp() {
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
	printMVP(r);
}

