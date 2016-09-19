
#include "Application.h"


#include  <stdlib.h>
#include "windows.h"
int main()
{
	SetErrorMode(SEM_NOGPFAULTERRORBOX);//main 
	Application app;
	app.startup();

	system("pause");

	return 0;
}




