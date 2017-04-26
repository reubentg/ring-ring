#include "helper.h"




void *captureVideo(void *vargp)
{
	videoStatus = 1;
	printf("capturing video...\n");
	unsigned long x;
	for(x=0;x<1000000000;x++);

	printf("Video saved\n");
	for(x=0;x<100000000;x++);
	videoStatus = 0;
	return NULL;
}
