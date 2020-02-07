

#include <iostream>
#include <stdlib.h>
#include <mysql.h>
#include <string>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/build_config.h>
#include <jdbc/cppconn/config.h>
#include <jdbc/cppconn/connection.h>

#include "db_man.h"
#include "helpers.h"
#include "member.h"
#include "employee.h"
#include "equipment.h"
#include "login.h"

using namespace	std;

int main(int argc, char** argv) {


	
	
	DB_MANAGER db_man;
	Login login_mgr(db_man.conn);
	Member_DB mem_db(db_man.conn);
	Employee_DB emp_db(db_man.conn,login_mgr);
	Equipment_DB eq_db(db_man.conn);
	
	for (;;) {
		cout << "Welcome to Zotout!" << endl;
		cout << "\t1:Member Options:" << endl;
		cout << "\t2:Employee Options" << endl;
		cout << "\t3:Equipment Options" << endl;
		cout << "Enter the number for your option: " << endl;

		
		int choice;
		CIN(choice);
		
		switch (choice) {
		case 1:
			mem_db.showOps(emp_db);
			break;
		case 2: //Add member
			emp_db.showOps();
			break;
		case 3:
			eq_db.showOps();
			break;
		}

	}

}

