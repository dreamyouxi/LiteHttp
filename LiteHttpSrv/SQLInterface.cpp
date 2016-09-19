
#include "SQLInterface.h"
using namespace std;


SQLInterface::SQLInterface()
{
	this->res = nullptr;
	this->mysql = nullptr;
	cout << __FUNCTION__ << endl;

}
SQLInterface::~SQLInterface()
{
	cout << __FUNCTION__ << endl;
}
bool SQLInterface::connect(string user, string pwd, string host, string db, int port)
{
	mysql = new MYSQL;

	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
	mysql_init(mysql);
	//	if (!mysql)return false;
	if (!mysql_real_connect(mysql, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), port, NULL, 0))
	{
		return false;
	}
	return true;
}

bool SQLInterface::exec(string sql,string encoding)
{
	if (!mysql)return false;

	encoding = "SET NAMES " + encoding;

	mysql_query(this->mysql,encoding.c_str());  

	int res11 = mysql_query(this->mysql, sql.c_str());
	if (!res11)
	{
		MYSQL_RES * result = mysql_store_result(mysql);

		this->res = result;

	}
	else
	{
		return false;
	}

	return true;
}

void SQLInterface::pushParams(std::vector<char*> & params, int count)
{
	if (!mysql)return;
	if (count == 0)
	{
		params.push_back("OK");



		return;
	}

	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		int i = 0;

		while (i < count)
		{
			char *str = row[i++];
			params.push_back(str);
		}
		cout << endl;  //  << "     " << sql_row[2] << endl;
	}

}


void SQLInterface::release()
{
	if (res)mysql_free_result(res);
	if (mysql)mysql_close(mysql);
}



