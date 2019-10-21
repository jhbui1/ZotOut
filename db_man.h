#ifndef DB_MAN_H
#define DB_MAN_H

/*
	Maintains connection with mysql database
*/

#include <mysql.h>

class DB_MANAGER {
public:
	MYSQL* conn;
	DB_MANAGER();
	~DB_MANAGER();
};

#endif 