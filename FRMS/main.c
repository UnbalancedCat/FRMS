#define _CRT_SECURE_NO_WARNINGS  
#include "global.h"

int main()
{
	atexit(push_flight_info);
	init();
	menu();
	//play_music();
	return 0;
}

