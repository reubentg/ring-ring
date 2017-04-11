/**Test*/
#include "helper.h"

void sayHello();

int main ()
{
	sayHello();


	if ( wiringPiSetup() == -1 ){
		printf("WiringPi installation is missing or not setup correctly!\n");
		exit( 1 );
	}

	pinMode(MOTION_PIN, INPUT);

	while(1)
	{

		if(1 == digitalRead(MOTION_PIN)){
			printf("Motion\n");
		}
		else
		{
			printf("No Motion\n");
		}

		delay(500);


	}

	return 0;

}

void sayHello()
{

	printf("Hello\n");
}
