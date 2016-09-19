#ifndef __SCRIPTCORE__
#define  __SCRIPTCORE__

#include <iostream>
#include <string>


#define  LUA_VERSION "5.1"




extern "C"{
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "lua/lua.h"

}
#include <vector>

class ScriptCore
{
public:
	std::string exec(std::string file, std::string param);

	static ScriptCore*getInstance();
	~ScriptCore();
private:
	lua_State *l;
	void initLua();
	void releaseLua();
	ScriptCore();



};



class SQLScriptInterface
{
public:
	static int _cdecl SQL_Script_Bridge(lua_State *l);
	static int _cdecl SQL_Script_create(lua_State*l);
	static int _cdecl SQL_Script_connect(lua_State*l);
	static int  _cdecl SQL_Script_execute(lua_State*l);
	static int  _cdecl SQL_Script_release(lua_State*l);

private:
	static void pushParams(lua_State *l, std::vector<char *> &params);
};




#endif