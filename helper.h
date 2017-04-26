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

//wiringPi
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define LOW 0
#define HIGH 1
#define DEBUG 1

#define RING_BUTTON 2	//GPIO27
#define BUZZER_PIN 24	//GPIO19
#define ARDUINO 0x05

//shared global vars
extern uint16_t ringStatus;
extern uint16_t videoStatus;


//function defs
void ringHandler(void);
void *captureVideo(void *vargp);



#endif /* HELPER_H_ */
