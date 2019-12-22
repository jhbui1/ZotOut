

#include <iostream>
#include <stdlib.h>
#include <mysql.h>
#include <string>

#include "db_man.h"
#include "helpers.h"
#include "member.h"
#include "employee.h"

using namespace	std;

int main(int argc, char** argv) {
	DB_MANAGER db_man;
	Member_DB mem_db(db_man.conn);
	Employee_DB emp_db(db_man.conn);
	for (;;) {
		cout << "Welcome to Zotout!" << endl;
		cout << "\t1:Member Options:" << endl;
		cout << "\t2:Employee Options" << endl;
		cout << "Enter the number for your option: " << endl;

		
		int n,new_id=-1;
		cin >> n;
		
		switch (n) {
		case 1:
			mem_db.showOps(emp_db);
			break;
		case 2: //Add member
			emp_db.showOps();
			break;
		}
	}

}

