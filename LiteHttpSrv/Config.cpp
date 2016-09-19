
#include "Config.h"

int Config::MAX_CONNECTION_COUNT = DEFAULT_MAX_CONNECTION_COUNT;
int Config::MAX_THREAD_COUNT = DEFAULT_MAX_THREAD_COUNT;
int Config::SRV_PORT = DEFAULT_SRV_PORT;

#ifdef  __DEBUG__
char * Config::SRV_HOST = DEFAULT_SRV_HOST;
#else
char * Config::SRV_HOST = DEFAULT_SRV_HOST2;
#endif //  Release

const char * Config::DefaultIndexFile = DEFAULT_INDEXFILE;


