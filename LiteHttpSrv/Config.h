#ifndef __CONFIG__H__
#define  __CONFIG__H__


#define  DEFAULT_MAX_THREAD_COUNT 500
#define  DEFAULT_MAX_CONNECTION_COUNT 0xffffff

#define  DEFAULT_SRV_HOST "127.0.0.1"
#define  DEFAULT_SRV_HOST2 "114.215.96.20"

#define  DEFAULT_SRV_PORT 80

#define  DEFAULT_INDEXFILE  "/index.html"

class Config
{
public:
	static char * SRV_HOST;//服务器ip
	static int MAX_THREAD_COUNT; // 最大请求处理线程数
	static int MAX_CONNECTION_COUNT; // 最大连接数
	static int SRV_PORT; // 服务器接受http请求端口
	static const char *DefaultIndexFile;

	static void initConfig();
};



#endif


