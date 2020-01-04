#pragma once
#include <mysql.h>

class Equipment_DB {
private:
	MYSQL* conn;
	int field_widths[4] = { 5, 30, 3, 10 };
	string categories[3] = { "counter","cardio","weight" };
	int num_cats=3;
public:
	Equipment_DB(MYSQL* conn);

	void initializeEquip();

	/*
		Show available operations and execute corresponding method
	*/
	void showOps();
	
	void showEq();

	void insertEquip();

	void clearAvailability();

	void checkOut();

	
};