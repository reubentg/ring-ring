#include "helper.h"



//execute as a separate thread
void *captureVideo(void *vargp)
{
	videoStatus = 1;
	printf("capturing video...\n");
	//delete existing image file after check
	if(-1 != access("/home/pi/doorvid/vid1.h264", F_OK)){
		int16_t delStat = system("rm -f /home/pi/doorvid/vid1.h264");

		assert(0 == delStat);

	}
	if(-1 != access("/home/pi/doorvid/vid1.mp4", F_OK)){
		int16_t delStat = system("rm -f /home/pi/doorvid/vid1.mp4");

		assert(0 == delStat);

	}

	int16_t vidStat = system("raspivid -n -vf -hf -a 12 -o /home/pi/doorvid/vid1.h264 -t 10000 && MP4Box -add /home/pi/doorvid/vid1.h264 /home/pi/doorvid/vid1.mp4");

	assert(0 == vidStat);

	printf("Video saved\n");


	//emailing
	//echo "Temp, Humidity.. video email!" | mail -s "Door sensor tripped" reubentg@gmail.com
	//mpack -s "Door video" /home/pi/doorvid/vid1.mp4 reubentg@gmail.com

	videoStatus = 0;
	return NULL;
}
