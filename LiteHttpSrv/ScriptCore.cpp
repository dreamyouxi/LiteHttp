
#include "ScriptCore.h"
#include <string>
#include <iostream>
#include <vector>
#include "Defs.h"
#include <mutex>
#include "SQLInterface.h"
using namespace  std;

static std::mutex _script_mutex;


//dis able cache for lua script
#define DISABLE_LUA_CACHE


std::string  ScriptCore::exec(std::string file, std::string param)
{
	std::lock_guard<std::mutex> locker(_script_mutex);
#ifdef DISABLE_LUA_CACHE
	initLua();
#endif
	//	luaL_dostring(l, "print(\" hello lua\")");
	if (param == "")
	{
		LOG("LUA: unknow request :%s", file.c_str());

		return html404;
	}
	//	return  "HttpHandler";


	int top = lua_gettop(l);


	lua_getglobal(l, "HttpHandler"); // get   Interface in lua


	//parse param ,  as "name=5" will be push
	int p, len = 0;

	vector<string> params;

	do
	{

		p = param.find("&");
		if (p == string::npos)
		{
			params.push_back(param);
			break;
		}
		else
		{
			string sub = param.substr(len, p);
			param = param.substr(p + 1, -1);
			params.push_back(sub);
		}
	} while (true);


	//push param to stack
	lua_pushstring(l, file.c_str());

	for (auto &s : params)
	{
		lua_pushstring(l, s.c_str());
	}


	lua_call(l, params.size() + 1, 1);
	std::string ret = lua_tostring(l, lua_gettop(l));
	//	lua_pop(l, 1);
	lua_settop(l, top);


#ifdef DISABLE_LUA_CACHE
	releaseLua();
#endif
	return ret;

	return  "ScriptCore.h";
}
ScriptCore::ScriptCore()
{
#ifndef DISABLE_LUA_CACHE
	initLua();
#endif
}

ScriptCore::~ScriptCore()
{
#ifndef DISABLE_LUA_CACHE
	releaseLua();
#endif
}




ScriptCore* ScriptCore::getInstance()
{
	static ScriptCore*ins = nullptr;
	if (ins == nullptr)
	{
		ins = new ScriptCore;
	}
	return ins;
}


void ScriptCore::releaseLua()
{
	lua_close(l);

}

void ScriptCore::initLua()
{
	l = lua_open();
	luaL_openlibs(l);


	lua_register(l, "SQL_Script_create", SQLScriptInterface::SQL_Script_create);
	lua_register(l, "SQL_Script_connect", SQLScriptInterface::SQL_Script_connect);
	lua_register(l, "SQL_Script_execute", SQLScriptInterface::SQL_Script_execute);
	lua_register(l, "SQL_Script_release", SQLScriptInterface::SQL_Script_release);


	luaL_dofile(l, "HttpHandler.lua");

}







void  SQLScriptInterface::pushParams(lua_State *l, vector<char *> &params)
{
	for (auto & str : params)
	{
		lua_pushstring(l, str);
	}

}







int _cdecl SQLScriptInterface::SQL_Script_create(lua_State*l)
{

	void * user = lua_newuserdata(l, sizeof SQLInterface);

	SQLInterface* ins = (SQLInterface*)user;
	ins->SQLInterface::SQLInterface();

	return 1;
}



int _cdecl SQLScriptInterface::SQL_Script_connect(lua_State*l)
{

	int top = lua_gettop(l);

	void *  instance = lua_touserdata(l, top - 5);
	const char * host = lua_tostring(l, top - 4);
	int port = lua_tonumber(l, top - 3);
	const char * user = lua_tostring(l, top - 2);
	const char * pswd = lua_tostring(l, top - 1);
	const char * table = lua_tostring(l, top);


	SQLInterface* ins = (SQLInterface*)instance;
	bool ret = ins->connect(user, pswd, host, table, port);

	lua_pushboolean(l, ret);

	return 1;
}



int _cdecl SQLScriptInterface::SQL_Script_execute(lua_State*l)
{

	int top = lua_gettop(l);

	void *  instance = lua_touserdata(l, top - 3);
	const char *encoding = lua_tostring(l, top - 2);
	const char * sql = lua_tostring(l, top - 1);
	int  row_count = lua_tonumber(l, top);

	SQLInterface* ins = (SQLInterface*)instance;

	bool status = ins->exec(sql, encoding);
	//	int n = ins->pushParams(l, row_count);
	cout << sql << endl;

	if (status)//OK
	{
		vector<char*> params;
		ins->pushParams(params, row_count);
		SQLScriptInterface::pushParams(l, params);//push ok
		return params.size();
	}

	// do error
	lua_pushstring(l, "Err");
	return 1;


}

int _cdecl SQLScriptInterface::SQL_Script_release(lua_State*l)
{

	int top = lua_gettop(l);

	void *  instance = lua_touserdata(l, top);

	SQLInterface* ins = (SQLInterface*)instance;
	ins->release();


	return 0;
}
