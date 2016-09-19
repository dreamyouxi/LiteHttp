

local t={};

function t:doRequest(p)
	
 
	local name = p["name"];
	if name ==nil then

		return "参数错误"
	end
	if p["name"]=="我" then
		return   "用户:"..name .." 登陆 成功 "   ;


	end
	return   "用户:"..name .." 登陆 失败 "   ;


 

end

return t;