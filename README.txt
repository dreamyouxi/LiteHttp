一个简单的Http网页服务器实现

示例网站 www.dreamyouxi.com

简介：
	1.支持GET请求

	2.基于winsock开发

	3.支持文件缓存

	4.支持线程池

	5.支持lua来编写动态网页或提供http服务

	6.本站的留言板块基于litehttp用lua编写实现

	6.支持lua访问mysql，可轻易扩展其他数据库






用lua编写http服务简易教程:
	1.
		在server_config.lua 添加 服务 和模块文件映射如
		t["login"]="script/login"; --添加服务login 映射到"script/login.lua"
 
	2.
		输入代码：（doRequest函数就是处理请求的函数，内部自动调用，p为参数 是table）
		返回字符串为返回客户端的消息

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

	3. 
		添加数据库 支持 见源文件示例 留言板(MsgBoard.lua)
