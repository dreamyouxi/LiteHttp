
 

 

local t={};

local suc_str= "<html lang='en'><head><meta charset='utf-8'><meta http-equiv='refresh'content='1;url=list.html'> </head><body><p>留言成功，自动跳转中......</p></body></html>";



local function makeMsg(name,txt,time)
	local ret="<p>";

	ret = ret ..  os.date("%Y-%m-%d %H:%M",time   ) .."   "   ;

	ret = ret  .. name  .. " 说:" ;
	ret = ret .. txt;


	ret =ret .. "</p>"

return ret;

end



function t:doRequest(p)
	local name = p["name"];
	local msg= p["msg"];
	if p["list"]~=nil then
		local ret="";
	--	ret =ret .. makeMsg("7:20","张3532532535三","哈啊哈");





		local ins = sql:create();
		sql:connect(ins);


		local t= sql:execute(ins, "UTF8" ,"select name,msg,time from msg  order by time DESC" ,3);
 
			local vv;

 
			
		local len = table.getn(t);
		for i=1 , len,3 do
			ret = ret ..  makeMsg(t[i],t[i+1],t[i+2])
		end




 		sql:release(ins);









		return  packCustomHtmlData(ret) 
	end

 

	if name == nil or name == "" then
		return packCustomHtmlData("昵称不能为空");
	end

	if msg == nil or msg == "" then
		return packCustomHtmlData("内容不能为空")
	end

	name= skipWhite(name);
	msg=skipWhite(msg)
	print(   "msg ".. name .. "  "  ..  msg  );



	

		local ins = sql:create();
		sql:connect(ins);




	local t= sql:execute(ins,"GB2312","INSERT INTO msg VALUES(\"" ..  name  .. "\",\"".. msg .."\",".. (os.time()) ..")" ,0);
    --local t= sql:execute(ins,"INSERT INTO msg VALUES(\"1\",\"2\",\"3\") " ,0);

 		sql:release(ins);

	
	if  t ~= nil  then

		return suc_str;

	end
	return packCustomHtmlData( "留言失败"   );















--	return   " welcome  MsgBoard "

end



return t;