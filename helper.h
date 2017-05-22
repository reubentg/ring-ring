/*
 * helper.h
 *
 *  Created on: Apr 10, 2017
 *      Author: rtg
 */

#ifndef HELPER_H_
#define HELPER_H_


//C header files
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <signal.h>

//wiringPi
#include <wiringPi.h>
#include <wiringPiI2C.h>


#define LOW 0
#define HIGH 1
#define DEBUG 1

#define RING_BUTTON 2	//GPIO27
#define BUZZER_PIN 24	//GPIO19
#define ARDUINO 0x05


//macros for paths


//shared global vars
extern uint16_t ringStatus;
extern uint16_t videoStatus;
extern uint16_t callStatus;


//function defs
void ringHandler(void);
void *captureVideo(void *vargp);
void *intercomCall(void *vargp);
void sigint_handler(int sig);


//struct to pass multiple arguments to email thread
struct email_data{
	unsigned char temp;
	unsigned char humid;
	const char * ip_addr;

};

#endif /* HELPER_H_ */
