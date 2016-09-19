#ifndef __SQLINTERFACE__
#define  __SQLINTERFACE__



#include <iostream>

#include "windows.h"

extern "C"{
 

#include "mysql/mysql.h"
}
#pragma comment(lib,"mysql/libmysql.lib")
#include <vector>

class SQLInterface
{


public:
	SQLInterface( );
	~SQLInterface();
	bool connect(std::string user, std::string pwd, std::string host, std::string db, int port);

	bool exec(std::string sql, std::string encoding);

	void pushParams(  std::vector<char*> & params, int count);
	void release();
private:
	MYSQL *mysql  ;
	MYSQL_RES *res ;
 
};





#endif