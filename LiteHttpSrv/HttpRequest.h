#ifndef __HTTPREQUEST__
#define  __HTTPREQUEST__

#include <string>
class HttpRequest
{
public:
	char * header;
	int sock;

	//��̬��ҳ֧��
	std::string params;//����ķ������
	std::string  name;//����ķ���name
	void parserFromString(char *str);
};






#endif