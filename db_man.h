#ifndef DB_MAN_H
#define DB_MAN_H

#include <mysql.h>

/*
	Maintains connection with mysql database
*/

class DB_MANAGER {
public:
	
	DB_MANAGER();
	~DB_MANAGER();
	MYSQL* conn;
};

#endif 