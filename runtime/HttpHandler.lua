


function LUALOG(...)

	print("LUA " .. ...);
end

require("httplib");
sql=require("sql")
local services_files=require("server_config")

local services={};


for key ,value in pairs(services_files) do
 
	local r= require(value);

 --	services[value]={};
	services[key]=r;
	if(r==nil) then 
 	 	LUALOG("Load Service ".. key .." File " .. value .. ".lua Error");
	 	return;
	end
 	LUALOG("Load Service ".. key .." File " .. value .. ".lua");
end



function HttpHandler(name,...)
	local params ={};

	for k ,v in ipairs({...}) do
		--parse real param
		local s= v;
		local i = string.find(s,"=");
		if i ~= nil then

				local key= string.sub(s,0,i-1);
				local value = string.sub(s,i+1,-1);

				params[key]=value
			else
				params[s]=s
		end


	end


	local service= services[name];
	if service ~= nil then
		return service:doRequest(params);

	end
	return "Error(404): could not find service " .. name; 
 
end
