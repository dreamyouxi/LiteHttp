

local t={};

t.config=require("sql_config");
 


--create a sql obj for lua
function t:create()
    return  SQL_Script_create();

end

-- connect the ins to mysql
function t:connect(ins)
    local c=t.config;

    local bool = SQL_Script_connect(ins,c.host , c.port , c.user , c.pwd , c.db);
 
    return bool;
end

--release res
function t:release(ins)
    SQL_Script_release(ins);
end

--exec sql
function t:execute(ins,encoding,sql,col_count)
  local t={ SQL_Script_execute(ins,encoding,sql,col_count)};
 
 if col_count == 0 then
    if t[1] == "OK" then
     return "OK";
     else
     return nil;
    end
 end
 

   return t;
end


return t;