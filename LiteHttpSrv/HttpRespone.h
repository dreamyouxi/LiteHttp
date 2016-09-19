#ifndef __HTTPRESPONE__
#define  __HTTPRESPONE__

#include <string>
class HttpRespone
{
public:
	char * header;
	int header_size;
	unsigned char *buffer;
	int size;
	int sock;
};






#endif