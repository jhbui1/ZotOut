#include <string>
#include <mysql.h>
#include <iostream>
#include <stdio.h>

#include "helpers.h"
#include "employee.h"
#include "login.h" //getpwd

using namespace std;

Employee_DB::Employee_DB(MYSQL* conn):conn(conn) {
	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employees( \
							emp_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,\
							first_name VARCHAR(30) NOT NULL,\
							last_name VARCHAR(30) NOT NULL,\
							salary DECIMAL(13,2) NOT NULL,\
							user_name VARCHAR(30) NOT NULL,\
							pwd VARCHAR(30) NOT NULL,\
							lvl ENUM('associate','manager'),\
							salt VARCHAR(60) NOT NULL);");

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

void Employee_DB::showOps() {
	int n;
	cout << "\t1: Add Employee" << endl;
	cout << "\t2: Show Employees" << endl;
	cout << "\t3: Delete Employees" << endl;
	cout << "\t4: Show Emp of the Month" << endl;
	CIN(n); 
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

void bind_var(MYSQL_BIND* bind, enum_field_types type, void* buffer, bool* isnull, unsigned long len,bool num_type) {
	bind->buffer_type = type;
	bind->buffer = buffer;
	bind->is_null = isnull;
	if (!num_type) {
		bind->buffer_length = len;
	}
	
}

void Employee_DB::addEmployee() {
	MYSQL_STMT* stmt;
	MYSQL_BIND  bind[7];
	
	//bind[0].buffer_type = MYSQL_TYPE_LONG;
	//bind[0].buffer = (char *)&int_data;
	//bind[0].is_null = 0;
	//bind[0].length = 0;

	///* STRING PARAM */
	//bind[1].buffer_type = MYSQL_TYPE_STRING;
	//bind[1].buffer = (char *)str_data;
	//bind[1].buffer_length = STRING_SIZE;
	//bind[1].is_null = 0;
	//bind[1].length = &str_length;

	///* SMALLINT PARAM */
	//bind[2].buffer_type = MYSQL_TYPE_SHORT;
	//bind[2].buffer = (char *)&small_data;
	//bind[2].is_null = &is_null;
	//bind[2].length = 0;

	//Prompt for employee info
	string fn,ln,uname,pwd,lvl,salt;
	double salary;
	char buff[200];
	fn = fieldLen(30, "first name");
	ln = fieldLen(30, "last name");
	cout << "Enter salary: " << endl;
	CIN(salary);
	uname = fieldLen(30, "username");
	pwd=this->login_mgr.getPWD();
	pwd = this->login_mgr.hashSalt(pwd);
	lvl = fieldLen(10, "level");//TODO: verify that user has priveelege to enter elevated level

	memset(bind,0,sizeof(bind));

	string insert_query = "INSERT INTO employees(first_name, last_name, salary, user_name, pwd, lvl, salt) VALUE(?, ?, ?, ?, ?, ?, ?)";
	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = (char *)fn.c_str();
	bind[0].is_null = 0;

	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer = (char *)ln.c_str();
	bind[1].is_null = 0;

	bind[2].buffer_type = MYSQL_TYPE_DECIMAL;
	bind[2].buffer = (char *)&salary;
	bind[2].is_null = 0;
	
	bind[3].buffer_type = MYSQL_TYPE_STRING;
	bind[3].buffer = (char *)uname.c_str();
	bind[3].is_null = 0;
	
	bind[4].buffer_type = MYSQL_TYPE_STRING;
	bind[4].buffer = (char *)pwd.c_str();
	bind[4].is_null = 0;

	bind[5].buffer_type = MYSQL_TYPE_STRING;
	bind[4].buffer = (char *)lvl.c_str();
	
	bind[6].buffer_type = MYSQL_TYPE_STRING;
	bind[4].buffer = (char *)salt.c_str();
	sprintf_s(buff, "INSERT INTO employees(first_name, last_name, salary,user_name,pwd,lvl,salt) VALUE('%s', '%s', '%.2f');",fn,ln,salary);
	MYSQL_STMT_INIT(this->conn,stmt,insert_query,insert_query.length());
	MYSQL_QUERY(this->conn, buff);

}



void Employee_DB::addMemEmp(int mem_id) {
	MYSQL_RES* res;
	int e_id;
	char buff[300];
	
	cout << "Enter your employee id:" << endl;
	CIN(e_id);
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

