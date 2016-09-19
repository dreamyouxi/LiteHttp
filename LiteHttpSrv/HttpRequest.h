#ifndef __HTTPREQUEST__
#define  __HTTPREQUEST__

#include <string>
class HttpRequest
{
public:
	char * header;
	int sock;

	//动态网页支持
	std::string params;//请求的服务参数
	std::string  name;//请求的服务name
	void parserFromString(char *str);
};






#endif