/**Test*/
#include "helper.h"

uint16_t ringStatus = 0;
uint16_t videoStatus = 0;

void sayHello();

int main ()
{
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

	unsigned char dataBuf[3] = {0,0,0}; //3 x 8 bits

	pinMode(RING_BUTTON, INPUT);
	wiringPiISR(RING_BUTTON, INT_EDGE_RISING, &ringHandler);
	pinMode (BUZZER_PIN, OUTPUT) ;//connect to buzzer

	while(1)
	{
		read(i2cHandle, dataBuf, 3);
		delay(1000);
		if(DEBUG)
		{
			printf("Data read: %d:-:%d:-:%d\n", dataBuf[0], dataBuf[1], dataBuf[2]);
		}

		if (0 == dataBuf[0] && 0 == videoStatus)
		{
			pthread_create(&tid0,NULL,captureVideo,NULL);

		}

		if(ringStatus)
		{
			digitalWrite(BUZZER_PIN, HIGH);
			delay(500);
			digitalWrite(BUZZER_PIN, LOW);
			ringStatus = 0;

		}


	}

	return 0;

}

void sayHello()
{

	printf("Hello\n");
}
