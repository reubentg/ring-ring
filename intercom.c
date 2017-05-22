#include "helper.h"


void *intercomCall(void *vargp)
{
	printf("Inside intercom..\n");

	callStatus = 1;
	struct email_data *emPtr;

	//converting argument pointer type to email_data*
	emPtr = (struct email_data *) vargp;

	char final[100];
	char first[] = "/home/pi/atDoor/atDoor sip:";
	strncat(final, first, 100);
	strncat(final,emPtr->ip_addr,100);

	if(DEBUG){
		printf(" Final command string is %s\n",final);
	}


	system(final);
	//system("/home/pi/atDoor/atDoor");	//for DEBUG
	callStatus = 0;
	ringStatus = 0;
	printf("stopping intercom\n");
	return NULL;

}
