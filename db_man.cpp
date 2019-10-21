#include <mysql.h>

#include "db_man.h"


DB_MANAGER::DB_MANAGER(void) {
	this->conn = mysql_init(0);
	this->conn = mysql_real_connect(this->conn, "localhost", "root", "35122jhb", "zotout", 3306, NULL, 0);
}

DB_MANAGER::~DB_MANAGER(void) {
	mysql_close(this->conn);
}