#ifndef DB_MAN_H
#define DB_MAN_H

#include <mysql.h>

class DB_MANAGER {
public:
	MYSQL* conn;
	DB_MANAGER();
	~DB_MANAGER();
};

#endif DB_MAN_H