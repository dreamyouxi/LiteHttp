#include "Defs.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>



void LOG(const char *str, ...)
{

	char log_buffer[102400];// 1kb   buffer size


	va_list l;
	va_start(l, str);

	vsprintf(log_buffer, str, l);

	va_end(l);
	strcat(log_buffer, "\n\0");

	//OutputDebugString(log_buffer);
	time_t rawtime;
	struct tm * t;
	time(&rawtime);
	t = localtime(&rawtime);
	printf("LOG [%d-%d-%d] [%d:%d:%d] : ", t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	printf(log_buffer);


}
