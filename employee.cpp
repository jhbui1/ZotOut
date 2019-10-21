#include <mysql.h>
#include <string>

#include "employee.h"

Employee_DB::Employee_DB(MYSQL* conn) {
	this->conn = conn;
	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employees( \
							emp_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,\
							first_name VARCHAR(30) NOT NULL,\
							last_name VARCHAR(30) NOT NULL,\
							salary DECIMAL(13,2) NOT NULL);");

	mysql_query(this->conn, "CREATE TABLE IF NOT EXISTS employee_member( \
							emp_id INT UNSIGNED NOT NULL,\
							member_id INT UNSIGNED NOT NULL);");

}


