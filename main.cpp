/*
 * main.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: jbui4
 */
#include <iostream>
#include <stdlib.h>
#include <mysql.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
//#include <jdbc/cppconn/*.h/*>

#include "helpers.h"
#include "member.h"

using namespace	std;

int main(int argc, char** argv){
	Member_DB mem_db();
	for(;;){
		cout<<"Welcome to Zotout!"<<endl;
		cout<<"\t1:Check-In:"<<endl;
		cout<<"\t2:Add Member"<<endl;
		cout<<"\t3:Update/View Member file"<<endl;
		cout<<"\t4:Update Equipment Status:"<<endl;
		//cout<<"\t4:"<<endl;

		cout<<"Enter the number for your option: "<<endl;
		int n;
		cin>>n;

		switch(n){
			case 1:
				break;
			case 2:
				break;

		}


	}

}



