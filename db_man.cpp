#include "db_man.h"

DB_MANAGER::DB_MANAGER() {
	this->conn = mysql_init(0);
	this->conn = mysql_real_connect(this->conn, "localhost", "root", "35122jhb", "zotout", 3306, NULL, 0);
}

DB_MANAGER::~DB_MANAGER() {
	mysql_close(this->conn);
}