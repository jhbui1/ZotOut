// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <stdlib.h>
#include <mysql.h>


#include "helpers.h"
#include "member.h"

using namespace	std;

int main(int argc, char** argv) {
	Member_DB mem_db;
	for (;;) {
		cout << "Welcome to Zotout!" << endl;
		cout << "\t1:Check-In:" << endl;
		cout << "\t2:Add Member" << endl;
		cout << "\t3:Update/View Member file" << endl;
		cout << "\t4:Show All Members" << endl;
		cout << "\t5:Update Equipment Status" << endl;
		//cout<<"\t4:"<<endl;

		cout << "Enter the number for your option: " << endl;
		int n;
		cin >> n;

		switch (n) {
		case 1:
			break;
		case 2:
			mem_db.insertMember();
			break;
		case 3:
			mem_db.updateMember();
			break;
		case 4:
			mem_db.showMembers();
			break;

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
