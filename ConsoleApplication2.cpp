

#include <iostream>
#include <stdlib.h>
#include <mysql.h>
#include <string>

#include "db_man.h"
//#include "db_man.cpp"
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
		cout << "\t1:Check-In:" << endl;
		cout << "\t2:Add Member" << endl;
		cout << "\t3:Update/View Member file" << endl;
		cout << "\t4:Show All Members" << endl;
		cout << "\t5:Update Equipment Status" << endl;
		cout << "\t6:Employee Options" << endl;
		

		cout << "Enter the number for your option: " << endl;
		int n,new_id=-1;
		cin >> n;
		
		switch (n) {
		case 1:
			break;
		case 2: //Add member
			 new_id = mem_db.insertMember();
			 if (new_id == -1) break;
			 emp_db.addMemEmp(new_id);
			//ask for employee id determine added member (last row) add to emp-mem relation
			break;
		case 3:
			mem_db.updateMember();
			break;
		case 4:
			mem_db.showMembers();
			break;
		case 5: //equipment
			break;
		case 6: //show employee menu
			printSep(5);
			emp_db.show_ops();
		}


	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
