/**Test*/
#include "helper.h"

uint16_t ringStatus = 0;
uint16_t videoStatus = 0;
uint16_t callStatus = 0;

void sayHello();

int main (int argc, char * argv[])
{

	printf ("argc is %d\n", argc);
	if (argc != 2)
	{
		printf("Requires IP address of indoor unit as argument! Exiting...\n");
		exit(1);
	}

	printf("Arg1 is %s\n", argv[1]);

	sayHello();
	pthread_t tid0, tid1, tid2, tid3;

	//wiringPi initialization
	if ( wiringPiSetup() == -1 )
	{
		printf("WiringPi installation is missing or not setup correctly!\n");
		exit( 1 );
	}

	int i2cHandle = wiringPiI2CSetup(ARDUINO);

	//I2C initialization
	if( -1 == i2cHandle)
	{
		printf("I2C setup failed!\n");
		exit(1);
	}

	unsigned char dataBuf[4] = {0,0,0,0}; //3 x 8 bits

	pinMode(RING_BUTTON, INPUT);
	wiringPiISR(RING_BUTTON, INT_EDGE_RISING, &ringHandler);
	signal(SIGINT, sigint_handler);


	struct email_data notify;
	struct email_data *nPtr;
	nPtr = &notify;

	//pthread_create(&tid1,NULL,intercomCall,NULL);	//DEBUG purposes
	while(1)
	{



		read(i2cHandle, dataBuf, 4);
		delay(1000);
		if(DEBUG)
		{
			printf("Data read: %d:-:%d:-:%d:-:%d\n", dataBuf[0], dataBuf[1], dataBuf[2], dataBuf[3]);
		}

		notify.temp = dataBuf[2];
		notify.humid = dataBuf[3];
		notify.ip_addr = argv[1];

		//printf("now is %s\n", notify.ip_addr);

		if (1 == dataBuf[0] && 0 == videoStatus)
		{
			puts("starting video recording...");
			pthread_create(&tid0,NULL,captureVideo,NULL);

		}

		if(0 == callStatus && 1 == ringStatus)
		{
			puts("Starting intercom...");
			pthread_create(&tid1,NULL,intercomCall,(void*) nPtr);
		}


	}

	return 0;

}

void sayHello()
{

	printf("Hello\n");
}

void sigint_handler(int sig)
{
	printf("\n\n\nSIGINT in main!!!\n\n\n");
	exit(0);
}
